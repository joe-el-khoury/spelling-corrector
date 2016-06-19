#include <memory>

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
 * Trains the spelling corrector on a file with the file name specified.
 */
void SpellingCorrector::train (const std::string& _file_name) {
}