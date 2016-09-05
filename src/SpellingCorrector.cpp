#include <algorithm>

#include "SpellingCorrector.h"

/**
 * Connect to the database.
 */
SpellingCorrector::SpellingCorrector () {
    // Throw an error if the spelling corrector is not initialized.
    SpellingCorrectorInitializer spi;
    if (!(spi.is_initialized())) {
        throw std::runtime_error("Backend is not initialized.");
    }

    this->mysql_conn = std::make_unique<MySQLInterface>("training_data");
}

/**
 * Checks if a word is in the database (has been seen before).
 */
bool SpellingCorrector::word_in_db (const Token& _word_to_check) {
    this->mysql_conn->exec_statement("SELECT * FROM 1gram WHERE word=\""+_word_to_check.get_token_str()+"\";");
    return (this->mysql_conn->get_num_rows_returned() >= 1);
}

Token SpellingCorrector::correct_word (const Token& _to_correct) {
    // Silence, warnings!
    return Token();
}