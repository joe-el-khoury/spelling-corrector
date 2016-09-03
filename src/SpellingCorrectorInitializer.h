#ifndef SPELLINGCORRECTORINITIALIZER_H
#define SPELLINGCORRECTORINITIALIZER_H

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <memory>

#include "../config/DatabaseConfigReader.h"
#include "../config/JSONReader.h"
#include "util/MySQLInterface.h"

class SpellingCorrectorInitializer {
public:
    SpellingCorrectorInitializer ();
    ~SpellingCorrectorInitializer ();
    
    bool is_initialized ();
    void initialize ();
private:
    // Whether the user has checked if the spelling corrector has been initialized.
    bool been_checked;
    std::vector<std::string> missing_databases;
    std::unordered_map<std::string, std::vector<std::string>> database_and_missing_tables;
};

#endif /* SPELLINGCORRECTORINITIALIZER_H */