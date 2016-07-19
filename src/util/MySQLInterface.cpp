#include "MySQLInterface.h"

MySQLInterface::MySQLInterface (const db_info& _db_info) {
    // Get the information about the database.
    std::string db_name     = _db_info.db_name;
    std::string db_uname    = _db_info.db_uname;
    std::string db_password = _db_info.db_password;
}