#include <memory>

#include "SpellingCorrector.h"
#include "FileReader.h"
#include "Tokenizer.h"
#include "TokenHistogram.h"

SpellingCorrector::SpellingCorrector () {
    this->tokenizer = std::make_unique<Tokenizer>();
    this->token_histogram = std::make_unique<TokenHistogram>();
}