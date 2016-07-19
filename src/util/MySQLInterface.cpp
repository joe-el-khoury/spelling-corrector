#include "MySQLInterface.h"

MySQLInterface::MySQLInterface (const db_info& _db_info) {
    // Get the username and password of the database.
    std::string db_uname    = _db_info.db_uname;
    std::string db_password = _db_info.db_password;
}

std::string MySQLInterface::construct_url (const db_info& _db_info) {
    std::string db_name       = _db_info.db_name;
    std::string db_url_prefix = _db_info.db_url_prefix;
    
    return db_url_prefix + db_name;
}