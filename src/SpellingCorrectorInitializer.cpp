#include "SpellingCorrectorInitializer.h"

/**
 * Checks if all databases are setup, and the config files are up
 * to date.
 */
bool SpellingCorrectorInitializer::is_initialized () {
    std::unique_ptr<JSONReader> reader;
    try {
        reader = std::make_unique<JSONReader>("config/setup.json");
    } catch (...) {
        std::cerr << "config/setup.json not found." << std::endl;
        return false;
    }

    // Keep track of all missing databases and config files.
    std::vector<std::string> missing_config_files;
    std::vector<std::string> missing_databases;
    std::unordered_map<std::string, std::vector<std::string>> database_and_missing_tables;
    
    std::unique_ptr<MySQLInterface> mysql;
    std::unique_ptr<DatabaseConfigReader> config_reader;
    
    for (const auto& database_name : reader->get_json_keys("databases")) {
        // The name of the config file of the database.
        std::string config_file_name = database_name + "_config.json";
        try {
            config_reader = std::make_unique<DatabaseConfigReader>("config/"+config_file_name);
        } catch (...) {
            missing_config_files.push_back(config_file_name);
            continue;
        }

        try {
            // Connect to the database.
            mysql = std::make_unique<MySQLInterface>(config_reader->get_db_info());
        } catch (...) {
            std::cerr << "MySQL authentication error. Verify the credentials in config/auth.json are up to date." << std::endl;
            return false;
        }

        // Over here, everything is fine: we found the config file and we have successfully connected to the database.

        // Check if the database exists.
        mysql->exec_statement("SHOW DATABASES LIKE \""+database_name+"\";");
        bool database_exists = (mysql->get_num_rows_returned() == 1);

        if (!database_exists) {
            missing_databases.push_back(database_name);
            continue;
        }

        // The database exists! Check its tables.

        // Get all the tables of the database.
        auto db_tables = reader->get_json_keys("tables."+database_name);
        for (const std::string& table_name : db_tables) {
            std::string db_and_table_name = database_name+"."+table_name;
            mysql->exec_statement("SHOW TABLES LIKE \""+table_name+"\";");

            bool table_exists = (mysql->get_num_rows_returned() == 1);
            if (!table_exists) {
                if (database_and_missing_tables.find(database_name) == database_and_missing_tables.end()) {
                    database_and_missing_tables.insert({database_name, {table_name}});
                } else {
                    database_and_missing_tables[database_name].push_back(table_name);
                }
            }
        }
    }

    if (!missing_config_files.empty()) {
        std::cerr << "Missing configuration files:\n";
        for (const std::string& missing_config_file : missing_config_files) {
            std::cerr << "\t*  " << missing_config_file << "\n";
        }
        std::cerr << std::endl;
    }
    if (!missing_databases.empty()) {
        std::cerr << "Missing databases:\n";
        for (const std::string& missing_database : missing_databases) {
            std::cerr << "\t*  " << missing_database << "\n";
        }
        std::cerr << std::endl;
    }
    if (!database_and_missing_tables.empty()) {
        std::cerr << "Missing tables:\n";
        for (const auto& db_and_missing_tables : database_and_missing_tables) {
            std::string db_name = db_and_missing_tables.first;
            std::vector<std::string> missing_tables = db_and_missing_tables.second;
            if (!missing_tables.empty()) {
                std::cerr << "\tIn " << db_name << ":\n";
                for (const std::string& missing_table : missing_tables) {
                    std::cerr << "\t  *  " << missing_table << "\n";
                }
            }
        }
        std::cerr << std::endl;
    }

    return missing_config_files.empty() && missing_databases.empty() && database_and_missing_tables.empty();
}