#ifndef SPELLINGCORRECTORINITIALIZER_H
#define SPELLINGCORRECTORINITIALIZER_H

#include <unordered_map>
#include <vector>
#include <memory>

#include "../config/DatabaseConfigReader.h"
#include "../config/JSONReader.h"
#include "util/MySQLInterface.h"

class SpellingCorrectorInitializer {
public:
    bool is_initialized ();
    void initialize ();
private:
    std::vector<std::string> missing_databases;
    std::unordered_map<std::string, std::vector<std::string>> database_and_missing_tables;
};

#endif /* SPELLINGCORRECTORINITIALIZER_H */