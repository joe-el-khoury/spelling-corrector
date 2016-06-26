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
 * All the training does is count the frequency of the words in the training file.
 */
void SpellingCorrector::train (const std::string& _file_name) {
    if (this->already_trained_on(_file_name)) {
        // Ignore files we've already trained on.
        return;
    }

    (this->files_trained_on).push_back(_file_name);

    // Create the file reader.
    this->file_reader = std::make_unique<FileReader>(_file_name);

    // Read the file until the end.
    while (!(this->file_reader->done_reading)) {
        // 1) Read a line from the file.
        std::string read_line = this->file_reader->read_up_to('\n');

        // 2) Tokenize the line at the spaces.
        this->tokenizer->tokenize(read_line, ' ');
    }

    // 3) Add the tokens to the histogram.
    this->token_histogram->add_tokens(this->tokenizer->get_tokens());
}

bool SpellingCorrector::is_known_word (const Token& _word) {
    return (this->token_histogram->token_exists(_word));
}

/**
 * From the list of words given, remove all the ones that are "unknown".
 * An unknown word is one we haven't encountered in the training set.
 */
std::vector<Token>& SpellingCorrector::remove_unknown_words (std::vector<Token>& _words) {
}