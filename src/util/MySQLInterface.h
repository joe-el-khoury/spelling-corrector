#ifndef MYSQLINTERFACE_H
#define MYSQLINTERFACE_H

#include <driver.h>
#include <connection.h>
#include <statement.h>
#include <resultset.h>
#include <exception.h>

#include <memory>

#include "MySQLInsertionThread.h"
#include "DBInfo.h"
#include "../../config/DatabaseConfigReader.h"

class MySQLInterface {
public:
    MySQLInterface (const std::string&, bool=true);
    ~MySQLInterface ();

    void exec_statement (const std::string&);
    sql::ResultSet* get_last_result ();
    unsigned int get_num_rows_returned ();
private:
    // The connection to the database.
    sql::Connection* db_connection;
    // The last result (if any) obtained from the last statement.
    sql::ResultSet* last_result;
    unsigned int num_rows_returned;

    // The thread responsible for dealing with insertions into the database.
    std::unique_ptr<MySQLInsertionThread> insertion_thread;
};

#endif