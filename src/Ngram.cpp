#include "Ngram.h"

/**
 * Adds a token to the list of tokens.
 */
void Ngram::add (const Token& _to_add) {
    this->tokens.push_back(_to_add);
}

/**
 * Gets the index we're at int the token list for the particular n.
 */
unsigned int Ngram::get_at_index (unsigned int _n) const {
    auto got = this->n_and_at_index.find(_n);
    if (got == this->n_and_at_index.end()) {
        return 0;
    } else {
        return got->second;
    }
}

/**
 * Checks whether there are any more ngrams to get from the list of tokens.
 */
bool Ngram::more (unsigned int _n) const {
    // joe elie jack john rachel chris sam
    unsigned int at_index = this->get_at_index(_n);
    return at_index <= (this->tokens.size() - _n);// && _n <= this->tokens.size();
}

/**
 * Gets an ngram from the list of tokens.
 * _n is the n in ngrams.
 */
std::vector<Token> Ngram::get_ngram (unsigned int _n) {
    if (!this->more(_n)) {
        return std::vector<Token>();
    }

    // Construct the vector we are returning.
    std::vector<Token> ret;
    ret.reserve(_n);

    // Insert the new n into the hash table if it doesn't exist.
    unsigned int at_index = this->get_at_index(_n);
    if (at_index == 0) {
        this->n_and_at_index.insert({_n, 0});
    }

    ret.insert(ret.end(), this->tokens.begin()+at_index, this->tokens.begin()+at_index+_n);
    (this->n_and_at_index)[_n]++;

    return ret;
}