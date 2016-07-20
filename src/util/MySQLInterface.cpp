#include "MySQLInterface.h"

/**
 * Create the connection to the database.
 */
MySQLInterface::MySQLInterface (const db_info& _db_info) {
    this->last_result = nullptr;

    // Get the username, password, and URL of the database.
    std::string db_uname    = _db_info.db_uname;
    std::string db_password = _db_info.db_password;
    std::string db_url      = this->construct_db_url(_db_info);

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
 * Construct the URL used to connect to the database.
 */
std::string MySQLInterface::construct_db_url (const db_info& _db_info) {
    std::string db_name       = _db_info.db_name;
    std::string db_url_prefix = _db_info.db_url_prefix;
    
    return db_url_prefix + db_name;
}