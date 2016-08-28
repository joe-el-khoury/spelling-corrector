#include "JSONReader.h"

/**
 * Loads the JSON data into a hash table.
 */
json_reader::json_data JSONReader::get_json_data (const std::string& _file_name) {
    bpt::ptree json_tree;
    try {
        bpt::read_json(_file_name, json_tree);
    } catch (bpt::ptree_error& e) {
        // Catch errors arising from reading the json.
        throw e;
    }

    json_reader::json_data ret;
    // Go through the JSON tree.
    for (const bpt::ptree::value_type& row : json_tree) {
        std::string key = row.first;
        std::string val = row.second.data();

        ret.insert({key, val});
    }

    return ret;
}