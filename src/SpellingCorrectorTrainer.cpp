#include <unordered_map>

#include "SpellingCorrectorTrainer.h"
#include "../config/DatabaseConfigReader.h"
#include "util/MD5FileHasher.h"

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

    std::string read_line;
    while (!(this->file_reader->done_reading)) {
        // Read a whole line from the file.
        read_line = this->file_reader->read_up_to('\n');

        // Tokenize the line and insert the tokens to the database.
        this->tokenizer.tokenize(read_line, ' ');
        for (const Token& to_insert : this->tokenizer.get_tokens()) {
            this->insert_token_into_db(to_insert);
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