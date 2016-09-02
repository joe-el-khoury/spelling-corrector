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
};

#endif /* SPELLINGCORRECTORINITIALIZER_H */