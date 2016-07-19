#include <boost/property_tree/json_parser.hpp>

#include "DatabaseConfigReader.h"

/**
 * All the constructor does is read the JSON file into the property tree.
 * It's a small file and will not be in memory for long so it's alright.
 */
DatabaseConfigReader::DatabaseConfigReader (const std::string& _config_file_name) {
    boost::property_tree::read_json(_config_file_name, this->json_tree);
}