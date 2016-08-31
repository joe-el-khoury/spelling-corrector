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
        std::vector<std::pair<std::string, std::string>> data;

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
    };
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
private:
    bpt::ptree json_tree;
};

#endif /* JSONREADER_H */