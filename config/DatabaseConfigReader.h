#ifndef DATABASECONFIGREADER_H
#define DATABASECONFIGREADER_H

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <unordered_map>

#include "../src/util/MySQLInterface.h"

typedef std::unordered_map<std::string, std::string> config;

class DatabaseConfigReader {
public:
    DatabaseConfigReader (const std::string&);
    config get_config_data ();

    mysql_interface::db_info config_to_db_info (config&);
private:
    boost::property_tree::ptree json_tree;
};

#endif /* DATABASECONFIGREADER_H */