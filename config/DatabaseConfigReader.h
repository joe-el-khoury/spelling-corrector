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

    mysql_interface::db_info get_db_info ();
private:
    boost::property_tree::ptree json_tree;
    void get_config_data ();
    config config_data;
};

#endif /* DATABASECONFIGREADER_H */