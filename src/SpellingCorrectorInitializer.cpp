#include "SpellingCorrectorInitializer.h"

SpellingCorrectorInitializer::SpellingCorrectorInitializer () {
    this->been_checked = false;
}

SpellingCorrectorInitializer::~SpellingCorrectorInitializer () {
}

/**
 * Checks if all databases are setup, and the config files are up to date.
 */
bool SpellingCorrectorInitializer::is_initialized () {
    this->been_checked = true;
    
    std::unique_ptr<JSONReader> reader;
    try {
        reader = std::make_unique<JSONReader>("config/setup.json");
    } catch (...) {
        std::cerr << "Parse error in config/setup.json or not found." << std::endl;
        return false;
    }

    // Keep track of all missing databases and config files.
    std::vector<std::string> missing_config_files;
    
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
            mysql = std::make_unique<MySQLInterface>(config_reader->get_db_info(), false);
        } catch (...) {
            std::cerr << "MySQL authentication error. Verify the credentials in config/auth.json are up to date." << std::endl;
            return false;
        }

        // Over here, everything is fine: we found the config file and we have successfully connected to the database.

        // Check if the database exists.
        mysql->exec_statement("SHOW DATABASES LIKE \""+database_name+"\";");
        bool database_exists = (mysql->get_num_rows_returned() == 1);

        if (!database_exists) {
            this->missing_databases.push_back(database_name);
        }

        // The database exists! Check its tables.

        // Get all the tables of the database.
        auto db_tables = reader->get_json_keys("tables."+database_name);
        for (const std::string& table_name : db_tables) {
            if (!database_exists) {
                if (this->database_and_missing_tables.find(database_name) == this->database_and_missing_tables.end()) {
                    this->database_and_missing_tables.insert({database_name, {table_name}});
                } else {
                    this->database_and_missing_tables[database_name].push_back(table_name);
                }
                continue;
            }
            std::string db_and_table_name = database_name+"."+table_name;
            mysql->exec_statement("SHOW TABLES LIKE \""+table_name+"\";");

            bool table_exists = (mysql->get_num_rows_returned() == 1);
            if (!table_exists) {
                if (this->database_and_missing_tables.find(database_name) == this->database_and_missing_tables.end()) {
                    this->database_and_missing_tables.insert({database_name, {table_name}});
                } else {
                    this->database_and_missing_tables[database_name].push_back(table_name);
                }
            }
        }
    }


    if (!missing_config_files.empty()) {
        std::cerr << "Missing configuration files:\n";
        for (const auto& missing_config_file : missing_config_files) {
            std::cerr << "\t*  " << missing_config_file << "\n";
        }
        std::cerr << std::endl;
    }
    if (!this->missing_databases.empty()) {
        std::cerr << "Missing databases:\n";
        for (const auto& missing_database : this->missing_databases) {
            std::cerr << "\t*  " << missing_database << "\n";
        }
        std::cerr << std::endl;
    }
    if (!this->database_and_missing_tables.empty()) {
        std::cerr << "Missing tables:\n";
        for (const auto& db_and_missing_tables : this->database_and_missing_tables) {
            std::string db_name = db_and_missing_tables.first;
            std::vector<std::string> missing_tables = db_and_missing_tables.second;
            if (!missing_tables.empty()) {
                std::cerr << "\tIn " << db_name << ":\n";
                for (const auto& missing_table : missing_tables) {
                    std::cerr << "\t  *  " << missing_table << "\n";
                }
            }
        }
        std::cerr << std::endl;
    }

    return missing_config_files.empty() && this->missing_databases.empty() && this->database_and_missing_tables.empty();
}

/**
 * Initializes the spelling corrector, assuming everything is present (config files needed, auth data, etc.).
 */
void SpellingCorrectorInitializer::initialize () {
    // Check if everything has been initialized and fill in member data.
    if (!this->been_checked) {
        if (this->is_initialized()) {
            return;
        }
    }
    
    // Everything we need right here!
    std::unique_ptr<MySQLInterface> mysql;
    std::unique_ptr<DatabaseConfigReader> config_reader;
    std::unique_ptr<JSONReader> reader;
    try {
        reader = std::make_unique<JSONReader>("config/setup.json");
    } catch (...) {
        std::cerr << "Parse error in config/setup.json or not found." << std::endl;
        return;
    }

    std::unordered_map<std::string, std::string> databases_and_create_queries = reader->get_json_data("databases");

    for (const auto& database_and_tables : this->database_and_missing_tables) {
        const std::string& database_name = database_and_tables.first;
        const auto& missing_tables_in_database = database_and_tables.second;
        if (missing_tables_in_database.empty()) {
            // No missing tables, keep going.
            continue;
        }

        // Check if the database exists and create it before proceeding.
        bool database_is_missing = std::find(this->missing_databases.begin(),
                                             this->missing_databases.end(),
                                             database_name) != this->missing_databases.end();
        
        std::string config_file_name = database_name + "_config.json";
        // Connect to the database.
        config_reader = std::make_unique<DatabaseConfigReader>("config/"+config_file_name);
        mysql         = std::make_unique<MySQLInterface>(config_reader->get_db_info(), false);
        
        if (database_is_missing) {
            // Create the database before proceeding.
            const std::string& query_to_execute = databases_and_create_queries[database_name];
            try {
                mysql->exec_statement(query_to_execute);
            } catch (...) {
                return;
            }
        }

        // Read the tables from the JSON in order (in case of table dependencies).
        for (const auto& table_and_query : reader->get_json_data_in_order("tables."+database_name)) {
            const std::string& table_name = table_and_query.first;
            const std::string& query_to_execute = table_and_query.second;

            // Check if the table from the JSON is actually a missing table.
            bool table_is_missing = std::find(missing_tables_in_database.begin(),
                                              missing_tables_in_database.end(),
                                              table_name) != missing_tables_in_database.end();
            if (!table_is_missing) {
                continue;
            }

            try {
                mysql->exec_statement(query_to_execute);
            } catch (...) {
                std::cerr << "Query <" << query_to_execute << "> failed." << std::endl;
                return;
            }
        }
    }
}