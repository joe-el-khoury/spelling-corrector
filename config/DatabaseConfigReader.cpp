#include <boost/property_tree/json_parser.hpp>

#include "DatabaseConfigReader.h"

/**
 * All the constructor does is read the JSON file into the property tree.
 * It's a small file and will not be in memory for long so it's alright.
 */
DatabaseConfigReader::DatabaseConfigReader (const std::string& _config_file_name) {
    bpt::read_json(_config_file_name, this->config_json_tree);
    bpt::read_json(this->auth_file, this->auth_json_tree);
    this->get_config_data();
    this->get_auth_data();
}

/**
 * Read all the config data into a hash table.
 */
void DatabaseConfigReader::get_config_data () {
    for (const bpt::ptree::value_type& row : (this->config_json_tree).get_child("config")) {
        // Get the key and value from the JSON.
        std::string key = row.first;
        std::string val = row.second.data();

        this->config_data.insert({key, val});
    }
}

/**
 * Read all the authentication data into a hash table.
 */
void DatabaseConfigReader::get_auth_data () {
    for (const bpt::ptree::value_type& row : (this->auth_json_tree).get_child("auth")) {
        // Get the key and value from the JSON.
        std::string key = row.first;
        std::string val = row.second.data();

        this->auth_data.insert({key, val});
    }
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