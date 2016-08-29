#include "DatabaseConfigReader.h"

/**
 * All the constructor does is read the JSON file into the property tree.
 * It's a small file and will not be in memory for long so it's alright.
 */
DatabaseConfigReader::DatabaseConfigReader (const std::string& _config_file_name) {
    JSONReader auth_reader(this->auth_file);
    this->auth_data = auth_reader.get_json_data("auth");
    
    JSONReader conf_reader(_config_file_name);
    this->config_data = conf_reader.get_json_data("config");
}

/**
 * Given a config, create the structure that the MySQL interface understands.
 */
mysql_interface::db_info DatabaseConfigReader::get_db_info () {
    return mysql_interface::db_info(
        (this->config_data)["db_url_prefix"],
        (this->config_data)["db_name"],
        (this->auth_data)["db_uname"],
        (this->auth_data)["db_password"]
    );
}