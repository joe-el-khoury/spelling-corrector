#ifndef JSONREADER_H
#define JSONREADER_H

#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/exceptions.hpp>

namespace bpt = boost::property_tree;

namespace json_reader {
    typedef std::unordered_map<std::string, std::string> json_data;

    struct ordered_json_data {
        typedef std::vector<std::pair<std::string, std::string>> vector_pair;
        vector_pair data;

        void insert (std::pair<std::string, std::string>&& _pair) {
            this->data.push_back(_pair);
        }

        std::string operator[] (const std::string& _key) {
            for (const auto& pair : this->data) {
                if (pair.first == _key) {
                    return pair.second;
                }
            }

            return std::string();
        }

        // Simple overloads.
        vector_pair::iterator begin () {
            return this->data.begin();
        }
        vector_pair::iterator end () {
            return this->data.end();
        }
        vector_pair::const_iterator cbegin () const {
            return this->data.cbegin();
        }
        vector_pair::const_iterator cend () const {
            return this->data.cend();
        }
    };

    typedef std::vector<std::string> json_keys;
} /* json_reader */

class JSONReader {
public:
    JSONReader (const std::string&);
    // Get the data in an arbitrary order (hash table).
    json_reader::json_data get_json_data ();
    json_reader::json_data get_json_data (const std::string&);

    // Get the data in order.
    json_reader::ordered_json_data get_json_data_in_order ();
    json_reader::ordered_json_data get_json_data_in_order (const std::string&);

    // Get the keys in the JSON files.
    json_reader::json_keys get_json_keys ();
    json_reader::json_keys get_json_keys (const std::string&);
private:
    bpt::ptree json_tree;
};

#endif /* JSONREADER_H */