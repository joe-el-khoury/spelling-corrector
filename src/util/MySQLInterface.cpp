#include "MySQLInterface.h"

/**
 * Construct the URL used to connect to the database.
 */
std::string construct_db_url (const mysql_interface::db_info& _db_info) {
    const std::string& db_url_prefix = _db_info.db_url_prefix;
    const std::string& db_name       = _db_info.db_name;
    
    return db_url_prefix + db_name;
}

/**
 * Create the connection to the database.
 * db_info contains information for connecting *directly* to the database, but sometimes it may not
 * exist, so the boolean value dictates whether it is allowed to connect just to the MySQL instance and
 * not to a specific database.
 */
MySQLInterface::MySQLInterface (const mysql_interface::db_info& _db_info, bool _strict) {
    this->last_result = nullptr;

    // Get the username, password, and URL of the database.
    const std::string& db_uname    = _db_info.db_uname;
    const std::string& db_password = _db_info.db_password;
    const std::string& db_url      = construct_db_url(_db_info);

    try {
        // Connect to the database.
        sql::Driver* driver = get_driver_instance();
        this->db_connection = driver->connect(db_url, db_uname, db_password);

        // Initiaize the insertion thread with the database connection.
        this->insertion_thread = std::make_unique<MySQLInsertionThread>(this->db_connection);
    } catch (sql::SQLException& e) {
        if (!_strict) {
            try {
                // Connect to JUST THE MySQL INSTANCE.
                sql::Driver* driver = get_driver_instance();
                this->db_connection = driver->connect(_db_info.db_url_prefix, db_uname, db_password);

                // Initialize the thread.
                this->insertion_thread = std::make_unique<MySQLInsertionThread>(this->db_connection);
            } catch (sql::SQLException& e) {
                throw e;
            }
        
        } else {
            throw e;
        }
    }
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
    struct is_insert {
        bool in_quote;
        is_insert () {
            in_quote = false;
        }
        
        bool operator() (char _c1, char _c2) {
            if (_c1 == '\'' || _c1 == '"') {
                in_quote = !in_quote;
            }

            return in_quote ? false : std::tolower(_c1) == std::tolower(_c2);
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
    
    sql::Statement* stmt = nullptr;
    bool result_was_returned;
    try {
        // Create the SQL statement and execute it.
        stmt = this->db_connection->createStatement();
        result_was_returned = stmt->execute(_sql_query);
    } catch (sql::SQLException& e) {
        if (stmt) {
            delete stmt;
        }
        throw e;
    }

    // Executing the statement returns a boolean value.
    // If true is returned, then the statement was a "getter".
    if (result_was_returned) {
        // Get the result set and the number of rows that were returned.
        this->last_result = stmt->getResultSet();
        this->num_rows_returned = this->last_result->rowsCount();
    }

    if (stmt) {
        delete stmt;
    }
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