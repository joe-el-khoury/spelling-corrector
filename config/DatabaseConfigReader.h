#ifndef DATABASECONFIGREADER_H
#define DATABASECONFIGREADER_H

#include <string>
#include <unordered_map>

#include "../src/util/MySQLInterface.h"
#include "JSONReader.h"

typedef std::unordered_map<std::string, std::string> config;

class DatabaseConfigReader {
public:
    DatabaseConfigReader (const std::string&);

    mysql_interface::db_info get_db_info ();
private:
    config config_data;
    config auth_data;
    const std::string auth_file = "config/auth.json";
};

#endif /* DATABASECONFIGREADER_H */