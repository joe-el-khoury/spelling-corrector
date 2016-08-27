#ifndef DATABASECONFIGREADER_H
#define DATABASECONFIGREADER_H

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <unordered_map>

#include "../src/util/MySQLInterface.h"

namespace bpt = boost::property_tree;

typedef std::unordered_map<std::string, std::string> config;

class DatabaseConfigReader {
public:
    DatabaseConfigReader (const std::string&);

    mysql_interface::db_info get_db_info ();
private:
    bpt::ptree config_json_tree;
    void get_config_data ();
    config config_data;
    
    const std::string auth_file = "config/auth.json";
    bpt::ptree auth_json_tree;
    void get_auth_data ();
    config auth_data;
};

#endif /* DATABASECONFIGREADER_H */