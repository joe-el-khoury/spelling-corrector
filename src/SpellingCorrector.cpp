#include <algorithm>

#include "SpellingCorrector.h"

SpellingCorrector::SpellingCorrector () {
    // Throw an error if the spelling corrector is not initialized.
    SpellingCorrectorInitializer spi;
    if (!(spi.is_initialized())) {
        throw std::runtime_error("Backend is not initialized.");
    }

    this->mysql_conn = std::make_unique<MySQLInterface>("training_data");
}

Token SpellingCorrector::correct_word (const Token& _to_correct) {
    // Silence, warnings!
    return Token();
}