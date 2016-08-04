#include "Ngram.h"

/**
 * Adds a token to the list of tokens.
 */
void Ngram::add (const Token& _to_add) {
    this->tokens.push_back(_to_add);
}

/**
 * Checks whether there are any more ngrams to get from the list of tokens.
 */
bool Ngram::more (unsigned int _n) const {
    return _n <= this->tokens.size();
}

/**
 * Gets an ngram from the list of tokens.
 * _n is the n in ngrams.
 */
std::vector<Token> Ngram::get_ngram (unsigned int _n) {
    if (!this->more(_n)) {
        return {};
    }

    // Construct the vector to return.
    std::vector<Token> ret;
    ret.reserve(_n);

    // Insert into the vector n tokens from the beginning, and remove the first
    // token from the list of tokens.
    ret.insert(ret.end(), this->tokens.begin(), this->tokens.begin()+_n);
    this->tokens.pop_front();

    return ret;
}