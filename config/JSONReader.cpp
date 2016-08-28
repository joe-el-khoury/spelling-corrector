#include "JSONReader.h"

void JSONReader::read_file (const std::string& _file_name) {
    try {
        bpt::read_json(_file_name, this->json_tree);
    } catch (bpt::ptree_error& e) {
        // Catch errors arising from reading the json.
        throw e;
    }
}

/**
 * Loads the JSON data from the propery tree into a hash table.
 */
json_reader::json_data get_json_data () {
    json_reader::json_data ret;
    // Go through the JSON tree.
    for (const bpt::ptree::value_type& row : this->json_tree) {
        std::string key = row.first;
        std::string val = row.second.data();

        ret.insert({key, val});
    }

    return ret;
}