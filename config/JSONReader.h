#ifndef JSONREADER_H
#define JSONREADER_H

#include <unordered_map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/exceptions.hpp>

namespace bpt = boost::property_tree;

namespace json_reader {
    typedef std::unordered_map<std::string, std::string> json_data;
} /* json_reader */

class JSONReader {
public:
    json_reader::json_data get_json_data (const std::string&);
};

#endif /* JSONREADER_H */