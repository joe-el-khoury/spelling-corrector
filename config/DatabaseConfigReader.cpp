#include <boost/property_tree/json_parser.hpp>

#include "DatabaseConfigReader.h"

/**
 * All the constructor does is read the JSON file into the property tree.
 * It's a small file and will not be in memory for long so it's alright.
 */
DatabaseConfigReader::DatabaseConfigReader (const std::string& _config_file_name) {
    boost::property_tree::read_json(_config_file_name, this->json_tree);
}

/**
 * Read all the config data into a hash table.
 */
config DatabaseConfigReader::get_config_data () {
    config config_data;

    // Go through the JSON, reading values into the hash table.
    for (const boost::property_tree::ptree::value_type& row : (this->json_tree).get_child("config")) {
        // Get the key and value from the JSON.
        std::string key = row.first;
        std::string val = row.second.data();

        config_data.insert({key, val});
    }

    return config_data;
}

/**
 * Given a config, create the structure that the MySQL interface understands.
 */
mysql_interface::db_info DatabaseConfigReader::config_to_db_info (config& _config_data) {
    return mysql_interface::db_info(
        _config_data["db_url_prefix"],
        _config_data["db_name"],
        _config_data["db_uname"],
        _config_data["db_password"]
    );
}