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
 * Gets a word and its count from the database.
 */
std::tuple<Token, unsigned int> SpellingCorrector::get_word_and_count (const Token& _word) {
    this->mysql_conn->exec_statement("SELECT * FROM 1gram WHERE word=\""+_word.get_token_str()+"\";");
    if (this->mysql_conn->get_num_rows_returned() < 1) {
        throw std::runtime_error(_word.get_token_str()+" was not found.");
    }

    auto* result = this->mysql_conn->get_last_result();
    unsigned int count;
    while (result->next()) {
        count = result->getInt(2);
    }

    return std::make_tuple(_word, count);
}

/**
 * Get the number of times a word appears in the database.
 */
unsigned int SpellingCorrector::get_word_count (const Token& _word) {
    unsigned int word_count;
    try {
        std::tie(std::ignore, word_count) = this->get_word_and_count(_word);
    } catch (...) {
        // The word doesn't exist.
        return 0;
    }

    return word_count;
}

/**
 * Checks if a word is in the database (has been seen before).
 */
bool SpellingCorrector::word_in_db (const Token& _word) {
    try {
        this->get_word_and_count(_word);
    } catch (...) {
        // The word doesn't exist.
        return false;
    }

    return true;
}

Token SpellingCorrector::correct_word (const Token& _to_correct) {
    // Silence, warnings!
    return Token();
}