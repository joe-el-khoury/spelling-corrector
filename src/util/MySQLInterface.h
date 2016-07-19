#ifndef MYSQLINTERFACE_H
#define MYSQLINTERFACE_H

#include <driver.h>
#include <connection.h>
#include <statement.h>
#include <resultset.h>

struct db_info {
    std::string db_name;
    std::string db_uname;
    std::string db_password;

    db_info (const std::string& _db_name, const std::string& _db_uname, const std::string& _db_password)
        : db_name(_db_name), db_uname(_db_uname), db_password(_db_password) {}
};

class MySQLInterface {
public:
    MySQLInterface (const db_info&);
};

#endif