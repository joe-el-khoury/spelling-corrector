#include <unordered_map>
#include <algorithm>

#include "Ngram.h"
#include "SpellingCorrectorTrainer.h"
#include "../config/DatabaseConfigReader.h"
#include "util/MD5FileHasher.h"
#include "TokenHistogram.h"

/**
 * Converts an ngram to a string.
 */
std::string ngram_to_str (const Ngram& _ngram, unsigned int _n, char _sep) {
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
 * Initialize some member variables and stuff.
 */
SpellingCorrectorTrainer::SpellingCorrectorTrainer () {
    // Read information from the configuration file.
    DatabaseConfigReader conf_reader("config/training_config.json");
    config config_data = conf_reader.get_config_data();

    // Connect to the database.
    mysql_interface::db_info db_info = conf_reader.config_to_db_info(config_data);
    this->mysql_interface = std::make_unique<MySQLInterface>(db_info);
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

    // How often to commit from memory to the database.
    // Experiment with this number.
    unsigned int commit_every = 1000;

    // Number of tokens we have in memory so far.
    unsigned int tokens_in_mem = 0;
    std::string read_line;
    while (!(this->file_reader->done_reading)) {
        // Read a whole line from the file.
        read_line = this->file_reader->read_up_to('\n');

        // Tokenize the line and keep the tokens in memory in the token histogram.
        this->tokenizer.tokenize(read_line, ' ');
        this->token_histogram.add_tokens(this->tokenizer.get_tokens());
        tokens_in_mem += this->tokenizer.get_tokens().size();
        this->tokenizer.reset_tokens();

        if (tokens_in_mem >= commit_every) {
            std::unordered_map<Token, unsigned long> histogram = this->token_histogram.get_histogram();
            for (const auto& row : histogram) {
                Token to_insert = row.first;
                unsigned long count = row.second;
                this->insert_token_into_db(to_insert, count);
            }

            // Reset everything.
            this->token_histogram.reset();
            tokens_in_mem = 0;
        }
    }

    if (tokens_in_mem < commit_every) {
        std::unordered_map<Token, unsigned long> histogram = this->token_histogram.get_histogram();
        for (const auto& row : histogram) {
            Token to_insert = row.first;
            unsigned long count = row.second;
            this->insert_token_into_db(to_insert, count);
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
    this->mysql_interface->exec_statement(sql_query);
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
    this->mysql_interface->exec_statement(sql_query);
}

/**
 * Checks the database backend to see if we've already trained on a specific file.
 * This is done by getting the MD5 hash of the file and seeing if it exists in the database.
 */
bool SpellingCorrectorTrainer::already_trained_on (const std::string& _file_name) {
    std::string md5_hash = md5hasher::get_hash(_file_name);
    if (md5_hash.empty()) {
        return true;
    }

    // Get the rows with the MD5 hash of the file.
    const std::string sql_query = "SELECT * FROM files WHERE md5_hash=\""+md5_hash+"\";";
    this->mysql_interface->exec_statement(sql_query);

    return (this->mysql_interface->get_last_result()->next());
}

/**
 * Added the MD5 hash of a file to the database backend.
 */
void SpellingCorrectorTrainer::add_to_already_trained_on (const std::string& _file_name) {
    std::string md5_hash = md5hasher::get_hash(_file_name);

    // Add the MD5 hash to the database.
    const std::string sql_query = "INSERT IGNORE INTO files(md5_hash) VALUES(\""+md5_hash+"\");";
    this->mysql_interface->exec_statement(sql_query);
}