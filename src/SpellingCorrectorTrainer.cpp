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
}

/**
 * Checks the database backend to see if we've already trained on a specific file.
 * This is done by getting the MD5 hash of the file and seeing if it exists in the database.
 */
bool SpellingCorrectorTrainer::already_trained_on (const std::string& _file_name) {
    std::string md5_hash = md5hasher::get_hash(_file_name);

    // Get the rows with the MD5 hash of the file.
    const std::string sql_query = "SELECT * FROM files WHERE md5_hash=\""+md5_hash+"\";";
    this->mysql_interface->exec_statement(sql_query);

    return (this->mysql_interface->get_last_result()->next());
}