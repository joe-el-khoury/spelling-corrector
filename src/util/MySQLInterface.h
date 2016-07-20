#ifndef MYSQLINTERFACE_H
#define MYSQLINTERFACE_H

#include <driver.h>
#include <connection.h>
#include <statement.h>
#include <resultset.h>

struct db_info {
    std::string db_url_prefix;
    std::string db_name;
    std::string db_uname;
    std::string db_password;

    db_info (const std::string& _db_url_prefix, const std::string& _db_name, const std::string& _db_uname, 
            const std::string& _db_password)
        : db_url_prefix(_db_url_prefix), db_name(_db_name), db_uname(_db_uname), db_password(_db_password) {}
};

class MySQLInterface {
public:
    MySQLInterface (const db_info&);
    ~MySQLInterface ();
private:
    std::string construct_db_url (const db_info&);

    // The connection to the database.
    sql::Connection* db_connection;
    // The last result (if any) obtained from the last statement.
    sql::ResultSet* last_result;
};

#endif