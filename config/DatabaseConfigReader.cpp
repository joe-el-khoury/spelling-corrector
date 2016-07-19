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
std::unordered_map<std::string, std::string> DatabaseConfigReader::get_config_data () {
    std::unordered_map<std::string, std::string> config_data;

    // Go through the JSON, reading values into the hash table.
    for (const boost::property_tree::ptree::value_type& row : (this->json_tree).get_child("config")) {
        // Get the key and value from the JSON.
        std::string key = row.first;
        std::string val = row.second.data();

        config_data.insert({key, val});
    }

    return config_data;
}