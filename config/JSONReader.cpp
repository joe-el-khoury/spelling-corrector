#include "JSONReader.h"

/**
 * Creates a propery tree.
 */
JSONReader::JSONReader (const std::string& _file_name) {
    try {
        bpt::read_json(_file_name, this->json_tree);
    } catch (bpt::ptree_error& e) {
        // Catch errors arising from reading the json.
        throw e;
    }
}

/**
 * Loads the JSON data from the property tree into a hash table.
 */
json_reader::json_data JSONReader::get_json_data () {
    json_reader::json_data ret;
    // Go through the JSON tree.
    for (const bpt::ptree::value_type& row : json_tree) {
        std::string key = row.first;
        std::string val = row.second.data();

        ret.insert({key, val});
    }
    
    return ret;
}

/**
 * Gets the JSON children data of a parent.
 */
json_reader::json_data JSONReader::get_json_data (const std::string& _parent_name) {
    json_reader::json_data ret;
    // Go through the JSON tree from the parent.
    for (const boost::property_tree::ptree::value_type& row : (this->json_tree).get_child(_parent_name)) {
        // Get the key and value from the JSON.
        std::string key = row.first;
        std::string val = row.second.data();

        ret.insert({key, val});
    }

    return ret;
}

/**
 * Loads the JSON data from the property tree in order.
 */
json_reader::ordered_json_data JSONReader::get_json_data_in_order () {
    json_reader::ordered_json_data ret;
    // Go through the JSON tree.
    for (const bpt::ptree::value_type& row : json_tree) {
        std::string key = row.first;
        std::string val = row.second.data();

        ret.insert({key, val});
    }

    return ret;
}

/**
 * Gets the JSON data of a parent in order.
 */
json_reader::ordered_json_data JSONReader::get_json_data_in_order (const std::string& _parent_name) {
    json_reader::ordered_json_data ret;
    // Go through the JSON tree from the parent.
    for (const boost::property_tree::ptree::value_type& row : (this->json_tree).get_child(_parent_name)) {
        // Get the key and value from the JSON.
        std::string key = row.first;
        std::string val = row.second.data();

        ret.insert({key, val});
    }

    return ret;
}

/**
 * Gets the keys in the JSON file.
 */
json_reader::json_keys JSONReader::get_json_keys () {
    json_reader::json_keys ret;
    // Go through the JSON tree.
    for (const boost::property_tree::ptree::value_type& row : this->json_tree) {
        std::string key = row.first;
        ret.push_back(key);
    }

    return ret;
}

/**
 * Gets the keys in the JSON file from the parent.
 */
json_reader::json_keys JSONReader::get_json_keys (const std::string& _parent_name) {
    json_reader::json_keys ret;
    // Go through the JSON tree from the parent.
    for (const boost::property_tree::ptree::value_type& row : (this->json_tree).get_child(_parent_name)) {
        std::string key = row.first;
        ret.push_back(key);
    }

    return ret;
}