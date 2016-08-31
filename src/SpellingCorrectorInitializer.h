#ifndef SPELLINGCORRECTORINITIALIZER_H
#define SPELLINGCORRECTORINITIALIZER_H

#include "util/MySQLInterface.h"
#include "../config/JSONReader.h"

class SpellingCorrectorInitializer {
public:
    bool is_initialized ();
    void initialize_spelling_corrector ();
};

#endif /* SPELLINGCORRECTORINITIALIZER_H */