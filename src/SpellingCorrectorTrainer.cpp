#include <unordered_map>
#include <algorithm>

#include "SpellingCorrectorTrainer.h"
#include "SpellingCorrectorInitializer.h"
#include "Ngram.h"
#include "../config/DatabaseConfigReader.h"
#include "util/MD5FileHasher.h"

/**
 * Initialize some member variables and stuff.
 */
SpellingCorrectorTrainer::SpellingCorrectorTrainer () {
    // First, check if everything is initialized, and throw an error if that's not
    // the case.
    SpellingCorrectorInitializer spi;
    if (!(spi.is_initialized())) {
        throw std::runtime_error("Backend is not initialized.");
    }
    
    // Read information from the configuration file.
    DatabaseConfigReader conf_reader("config/training_data_config.json");
    // Connect to the database.
    mysql_interface::db_info db_info = conf_reader.get_db_info();
    this->mysql_conn = std::make_unique<MySQLInterface>("training_data");
}

/**
 * Train on a file.
 */
void SpellingCorrectorTrainer::train (const std::string& _file_name) {
    if (this->already_trained_on(_file_name)) {
        return;
    }

    this->add_to_already_trained_on(_file_name);

    // Create the file reader.
    this->file_reader = std::make_unique<FileReader>(_file_name);

    std::string read_line;
    while (!(this->file_reader->done_reading)) {
        // Read a whole line from the file.
        read_line = this->file_reader->read_up_to('\n');

        // Tokenize the line.
        this->tokenizer.tokenize(read_line, ' ');
        // Insert each token into the database.
        std::for_each(this->tokenizer.get_tokens().begin(), this->tokenizer.get_tokens().end(),
            [&](const Token& _to_insert) {
                this->insert_token_into_db(_to_insert);
            }
        );
        
        // Reset the tokenizer.
        this->tokenizer.reset_tokens();
    }
}

/**
 * Same as the training function above, but allows you to train with a specified number of ngrams.
 */
void SpellingCorrectorTrainer::train (const std::string& _file_name,
                                      const std::vector<unsigned int>& _ngrams_to_train_with) {
    Ngram ngram;
    this->file_reader = std::make_unique<FileReader>(_file_name);
    std::string read_line;
    while (!(this->file_reader->done_reading)) {
        read_line = this->file_reader->read_up_to('\n');

        // Tokenize the line.
        this->tokenizer.tokenize(read_line, ' ');

        // Add the tokens to the ngram.
        std::for_each(this->tokenizer.get_tokens().begin(), this->tokenizer.get_tokens().end(),
            [&](const Token& _to_add) {
                ngram.add(_to_add);
            }
        );

        this->tokenizer.reset_tokens();
    }

    // Add all the ngrams to the database.
    for (unsigned int n : _ngrams_to_train_with) {
        if (!(this->already_trained_on(_file_name, n))) {
            this->add_to_already_trained_on(_file_name, n);
            this->insert_ngram_into_db(ngram, n);
        }
    }
}

/**
 * Inserts the token string into the database backend.
 */
void SpellingCorrectorTrainer::insert_token_into_db (const Token& _to_insert) {
    const std::string& token_str = _to_insert.get_token_str();
    std::string sql_query  = "INSERT INTO unigrams (word) VALUES (\""+token_str+"\") ";
                sql_query += "ON DUPLICATE KEY UPDATE count=count+1;";
    this->mysql_conn->exec_statement(sql_query);
}

/**
 * Inserts a token with its known count into the database backend;
 */
void SpellingCorrectorTrainer::insert_token_into_db (const Token& _to_insert, unsigned long _count) {
    const std::string& token_str = _to_insert.get_token_str();
    const std::string& count_str = std::to_string(_count);
    // Query to update the token count if it exists in the database, and add it with its count if it doesn't.
    std::string sql_query  = "INSERT INTO unigrams (word, count) VALUES (\""+token_str+"\", " + count_str + ") ";
                sql_query += "ON DUPLICATE KEY UPDATE count=count+"+count_str+";";
    this->mysql_conn->exec_statement(sql_query);
}

/**
 * Converts an ngram to a string.
 */
std::string ngram_to_str (Ngram& _ngram, unsigned int _n, char _sep=' ') {
    std::vector<Token> ngram = _ngram.get_ngram(_n);
    if (ngram.empty()) {
        return std::string();
    }

    std::string ret;
    std::for_each(ngram.begin(), ngram.end()-1,
        /**
         * Construct the string like so: "<token><sep><token>..."
         */
        [&](const Token& _token) {
            ret += (_token.get_token_str() + _sep);
        }
    );
    // The last token doesn't have a separation character after it.
    ret += (ngram.end()-1)->get_token_str();

    return ret;
}

/**
 * Inserts the ngram into the database.
 */
void SpellingCorrectorTrainer::insert_ngram_into_db (Ngram& _ngram, unsigned int _n) {
    // The table in the database which we will insert into will have the name "n + gram".
    // So if we are inserting an ngram with n = 2, the table will be named 2gram.
    // Similarly, if n = 3, the table will be named 3gram.
    const std::string& table_name = std::to_string(_n) + "gram";
    
    std::string ngram_str;
    std::string sql_query;
    while (_ngram.more(_n)) {
        ngram_str = ngram_to_str(_ngram, _n);
        sql_query  = "INSERT INTO "+table_name+"(word) VALUES (\""+ngram_str+"\") ";
        sql_query += "ON DUPLICATE KEY UPDATE count=count+1;";
        this->mysql_conn->exec_statement(sql_query);
    }
}

/**
 * Checks the database backend to see if we've already trained on a specific file.
 * This is done by getting the MD5 hash of the file and seeing if it exists in the database.
 * The second ngram argument checks if we've trained with a certain ngram on the file.
 */
bool SpellingCorrectorTrainer::already_trained_on (const std::string& _file_name,
                                                   unsigned int _ngram) {
    std::string md5_hash = md5hasher::get_hash(_file_name);
    if (md5_hash.empty()) {
        return true;
    }

    // Get the rows with the MD5 hash of the file and the ngram.
    std::string sql_query  = "SELECT * FROM files WHERE md5_hash=\""+md5_hash+"\" and ";
                sql_query += "ngram="+std::to_string(_ngram)+";";
    this->mysql_conn->exec_statement(sql_query);

    return !(this->mysql_conn->get_num_rows_returned() == 0);
}

/**
 * Added the MD5 hash of a file to the database backend.
 */
void SpellingCorrectorTrainer::add_to_already_trained_on (const std::string& _file_name,
                                                          unsigned int _ngram) {
    std::string md5_hash = md5hasher::get_hash(_file_name);

    // Add the MD5 hash to the database.
    std::string sql_query  = "INSERT IGNORE INTO files(md5_hash, ngram) VALUES(\""+md5_hash+"\", ";
                sql_query += std::to_string(_ngram)+");";
    this->mysql_conn->exec_statement(sql_query);
}