#ifndef DBINFO_H
#define DBINFO_H

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

#endif /* DBINFO_H */