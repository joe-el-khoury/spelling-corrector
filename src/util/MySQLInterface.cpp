#include "MySQLInterface.h"

/**
 * Construct the URL used to connect to the database.
 */
std::string construct_db_url (const mysql_interface::db_info& _db_info) {
    std::string db_name       = _db_info.db_name;
    std::string db_url_prefix = _db_info.db_url_prefix;
    
    return db_url_prefix + db_name;
}

/**
 * Create the connection to the database.
 */
MySQLInterface::MySQLInterface (const mysql_interface::db_info& _db_info) {
    this->last_result = nullptr;

    // Get the username, password, and URL of the database.
    std::string db_uname    = _db_info.db_uname;
    std::string db_password = _db_info.db_password;
    std::string db_url      = construct_db_url(_db_info);

    // Connect to the database.
    sql::Driver* driver = get_driver_instance();
    this->db_connection = driver->connect(db_url, db_uname, db_password);
}

/**
 * Destroy the connection to the database.
 */
MySQLInterface::~MySQLInterface () {
    if (this->last_result) {
        delete this->last_result;
    }
    this->db_connection->close();
    delete this->db_connection;
}

/**
 * Execute a statament on the database.
 */
void MySQLInterface::exec_statement (const std::string& _sql_query) {
    // Create the SQL statement and execute it.
    sql::Statement* stmt = this->db_connection->createStatement();
    bool returned_result = stmt->execute(_sql_query);

    // Executing the statement returns a boolean value.
    // If true is returned, then the statement was a "getter".
    if (returned_result) {
        // I hate camel case!
        this->last_result = stmt->getResultSet();
    }

    delete stmt;
}

/**
 * Get the result from the last executed statement, if any exists.
 */
sql::ResultSet* MySQLInterface::get_last_result () {
    return this->last_result;
}