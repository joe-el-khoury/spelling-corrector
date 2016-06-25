#include "TokenHistogram.h"
#include "Token.h"

/**
 * Add a bunch of tokens to the histogram.
 */
void TokenHistogram::add_tokens (const std::vector<Token>& _tokens_to_add) {
    for (const Token& token_to_add : _tokens_to_add) {
        this->add_token(token_to_add);
    }
}

/**
 * Check if a token exists in the histogram.
 */
bool TokenHistogram::token_exists (const Token& _to_find) const {
    TokenHistogram::Histogram::const_iterator got = (this->histogram).find(_to_find);
    return (got != (this->histogram).end());
}

/**
 * Add a token to the histogram.
 * All that has to be done is to increment the count of the token.
 */
void TokenHistogram::add_token (const Token& _to_add) {
    // The count of the token will be incremented if it exists, otherwise the token
    // will be added to the histogram with the default value.
    if (this->token_exists(_to_add)) {
        (this->histogram)[_to_add]++;
    
    } else {
        (this->histogram).insert({_to_add, this->default_value});
    }
}

/**
 * Get the count of the particular token. If the token does not exist, then
 * just return the default value.
 */
unsigned long TokenHistogram::get_count (const Token& _to_get) {
    return this->token_exists(_to_get) ? (this->histogram)[_to_get] : this->default_value;
}

/**
 * Prints the histogram in a debugging friendly way.
 */
void TokenHistogram::print (unsigned long _threshold) const {
    std::string token_str;
    unsigned long token_count;

    TokenHistogram::Histogram::const_iterator it;
    for (it = (this->histogram).begin(); it != (this->histogram).end(); it++) {
        token_str = (it->first).get_token_str();
        token_count = it->second;

        if (token_count >= _threshold) {
            std::cout << token_str << " => " << token_count << " occurence(s)." << std::endl;
        }
    }
}
