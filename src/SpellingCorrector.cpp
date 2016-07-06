#include <algorithm>

#include "SpellingCorrector.h"
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
 *
 * The second parameter specifies how often to "send" the tokens to the histogram,
 * in order to minimize the number of tokens sent at once.
 */
void SpellingCorrector::train (const std::string& _file_name, int _train_every) {
    if (this->already_trained_on(_file_name)) {
        // Ignore files we've already trained on.
        return;
    }

    (this->files_trained_on).push_back(_file_name);

    // Create the file reader.
    this->file_reader = std::make_unique<FileReader>(_file_name);

    int num_tokens = 0;
    while (!(this->file_reader->done_reading)) {
        // 1) Read a line from the file.
        std::string read_line = this->file_reader->read_up_to('\n');

        // 2) Tokenize the line at the spaces.
        this->tokenizer->tokenize(read_line, ' ');
        num_tokens += (this->tokenizer->get_tokens()).size();

        if (num_tokens >= _train_every) {
            num_tokens = 0;
            
            // 3) Send the tokens to the histogram and then reset the tokenizer.
            this->token_histogram->add_tokens(this->tokenizer->get_tokens());
            this->tokenizer->reset_tokens();
        }
    }

    if (num_tokens < _train_every) {
        // Send the last batch to the histogram.
        this->token_histogram->add_tokens(this->tokenizer->get_tokens());
        this->tokenizer->reset_tokens();
    }
}

bool SpellingCorrector::is_known_word (const Token& _word) const {
    return (this->token_histogram->token_exists(_word));
}

/**
 * From the list of words given, remove all the ones that are "unknown".
 * An unknown word is one we haven't encountered in the training set.
 */
void SpellingCorrector::remove_unknown_words_from (std::vector<Token>& _words) {
    // Remove all unknown words.
    if (!_words.empty()) {
        std::vector<Token>::iterator last_known;
        last_known = std::remove_if(_words.begin(), _words.end(), [&](const Token& _token) {
            return !(this->is_known_word(_token));
        });

        _words.erase(last_known, _words.end());
    }
}

/**
 * Gets the edits of a word, and discards the ones that are unkown.
 */
std::vector<Token> SpellingCorrector::get_known_edits_of (const Token& _word, unsigned int _edit_distance) {
    // Get the edits of the word and remove the unknown ones.
    std::vector<Token> word_edits = _word.get_edits(_edit_distance);
    this->remove_unknown_words_from(word_edits);

    return word_edits;
}

/**
 * Gets the best candidate from a list of candidates. The best candidate is one that appears
 * the most times in the training set.
 */
Token SpellingCorrector::get_best_candidate (const std::vector<Token>& _candidates) {
    std::vector<Token>::const_iterator best_candidate_iter;
    best_candidate_iter = std::max_element(_candidates.cbegin(), _candidates.cend(),
    // Lambda function to find the better candidate.
    [&](const Token& _t1, const Token& _t2) {
        unsigned long count1 = this->token_histogram->get_count(_t1);
        unsigned long count2 = this->token_histogram->get_count(_t2);
        return count1 < count2;
    });

    return *best_candidate_iter;
}

/**
 * Obviously the most important part of the spelling corrector.
 */
Token SpellingCorrector::correct_word (const Token& _to_correct) {
    // 1) Check if the word is correct already.
    if (this->is_known_word(_to_correct)) {
        // The word is already correct, so leave the function.
        return _to_correct;
    }

    std::vector<Token>::const_iterator corrected_word_iter;
    
    // 2) Get the known edits at a distance of 1, and check for the best candidate.
    std::vector<Token> known_edits_dist1 = this->get_known_edits_of(_to_correct);
    if (!(known_edits_dist1.empty())) {
        return this->get_best_candidate(known_edits_dist1);
    }

    // 3) Get the known edits at a distance of 2, and check for the best candidate.
    std::vector<Token> known_edits_dist2 = this->get_known_edits_of(_to_correct, 2);
    if (!(known_edits_dist2.empty())) {
        return this->get_best_candidate(known_edits_dist2);
    }

    // 4) If none of the above are satisfied, then just return the word, as we have
    // no idea what the word is. Because of that, add it to the token histogram.
    this->token_histogram->add_token(_to_correct);
    return _to_correct;
}