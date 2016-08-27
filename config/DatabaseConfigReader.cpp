#include <boost/property_tree/json_parser.hpp>

#include "DatabaseConfigReader.h"

/**
 * All the constructor does is read the JSON file into the property tree.
 * It's a small file and will not be in memory for long so it's alright.
 */
DatabaseConfigReader::DatabaseConfigReader (const std::string& _config_file_name) {
    boost::property_tree::read_json(_config_file_name, this->json_tree);
    this->get_config_data();
}

/**
 * Read all the config data into a hash table.
 */
void DatabaseConfigReader::get_config_data () {
    // Go through the JSON, reading values into the hash table.
    for (const boost::property_tree::ptree::value_type& row : (this->json_tree).get_child("config")) {
        // Get the key and value from the JSON.
        std::string key = row.first;
        std::string val = row.second.data();

        this->config_data.insert({key, val});
    }
}

/**
 * Given a config, create the structure that the MySQL interface understands.
 */
mysql_interface::db_info DatabaseConfigReader::get_db_info () {
    return mysql_interface::db_info(
        (this->config_data)["db_url_prefix"],
        (this->config_data)["db_name"],
        (this->config_data)["db_uname"],
        (this->config_data)["db_password"]
    );
}