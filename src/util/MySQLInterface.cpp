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

    // Initiaize the insertion thread with the database connection.
    this->insertion_thread = std::make_unique<MySQLInsertionThread>(this->db_connection);
}

/**
 * Destroy the connection to the database.
 */
MySQLInterface::~MySQLInterface () {
    if (this->last_result) {
        delete this->last_result;
    }
    this->insertion_thread->stop();
    this->db_connection->close();
    delete this->db_connection;
}

/**
 * Checks if the query is an insert query.
 */
bool is_insert_query (const std::string& _sql_query) {
    // Predicate for the search algorithm.
    // One small bug: if the word insert is part of a select query, for example, it
    // will be incorrectly considered an insert query.
    struct is_insert {
        bool operator() (char c1, char c2) {
            return std::tolower(c1) == std::tolower(c2);
        }
    };

    std::string insert = "insert";
    std::string::const_iterator it = std::search(
        _sql_query.begin(), _sql_query.end(), insert.begin(), insert.end(),
        is_insert()
    );

    return (it != _sql_query.end());
}

/**
 * Execute a statament on the database.
 */
void MySQLInterface::exec_statement (const std::string& _sql_query) {
    // Check if the query is an insert first.
    if (is_insert_query(_sql_query)) {
        this->insertion_thread->add_to_insertion_queue(_sql_query);
        return;
    }
    
    // Create the SQL statement and execute it.
    sql::Statement* stmt = this->db_connection->createStatement();
    bool returned_result = stmt->execute(_sql_query);

    // Executing the statement returns a boolean value.
    // If true is returned, then the statement was a "getter".
    if (returned_result) {
        // Get the result set and the number of rows that were returned.
        this->last_result = stmt->getResultSet();
        this->num_rows_returned = this->last_result->rowsCount();
    }

    delete stmt;
}

/**
 * Get the result from the last executed statement, if any exists.
 */
sql::ResultSet* MySQLInterface::get_last_result () {
    return this->last_result;
}

unsigned int MySQLInterface::get_num_rows_returned () {
    return this->num_rows_returned;
}