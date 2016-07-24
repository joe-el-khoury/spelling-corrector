#ifndef MYSQLINTERFACE_H
#define MYSQLINTERFACE_H

#include <driver.h>
#include <connection.h>
#include <statement.h>
#include <resultset.h>

namespace mysql_interface {
struct db_info {
    std::string db_url_prefix;
    std::string db_name;
    std::string db_uname;
    std::string db_password;

    db_info (const std::string& _db_url_prefix, const std::string& _db_name, const std::string& _db_uname, 
            const std::string& _db_password)
        : db_url_prefix(_db_url_prefix), db_name(_db_name), db_uname(_db_uname), db_password(_db_password) {}
};
} /* mysql_interface */

class MySQLInterface {
public:
    MySQLInterface (const mysql_interface::db_info&);
    ~MySQLInterface ();

    void exec_statement (const std::string&);
    sql::ResultSet* get_last_result ();
private:
    // The connection to the database.
    sql::Connection* db_connection;
    // The last result (if any) obtained from the last statement.
    sql::ResultSet* last_result;
};

#endif