#ifndef DATABASECONFIGREADER_H
#define DATABASECONFIGREADER_H

#include <boost/property_tree/ptree.hpp>

#include <string>
#include <unordered_map>

class DatabaseConfigReader {
public:
    DatabaseConfigReader (const std::string&);
    std::unordered_map<std::string, std::string> get_config_data ();
private:
    boost::property_tree::ptree json_tree;
};

#endif /* DATABASECONFIGREADER_H */