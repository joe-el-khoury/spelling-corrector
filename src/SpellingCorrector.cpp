#include <memory>
#include <algorithm>

#include "SpellingCorrector.h"
#include "FileReader.h"
#include "Tokenizer.h"
#include "TokenHistogram.h"
#include "Token.h"

SpellingCorrector::SpellingCorrector () {
    this->tokenizer = std::make_unique<Tokenizer>();
    this->token_histogram = std::make_unique<TokenHistogram>();
}

/**
 * Checks if we've already trained on a particular file before.
 */
bool SpellingCorrector::already_trained_on (const std::string& _file_name) const {
    std::vector<std::string>::const_iterator got;
    got = std::find((this->files_trained_on).begin(), (this->files_trained_on).end(), _file_name);

    return (got != (this->files_trained_on).end());
}

/**
 * Trains the spelling corrector on a file with the file name specified.
 */
void SpellingCorrector::train (const std::string& _file_name) {
    if (this->already_trained_on(_file_name)) {
        return;
    }
}