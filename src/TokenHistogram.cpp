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
 * Add a token to the histogram.
 * All that has to be done is to increment the count of the token.
 */
void TokenHistogram::add_token (const Token& _to_add) {
    // First check if the token is already in the histogram.
    TokenHistogram::Histogram::iterator got = (this->histogram).find(_to_add);
    bool token_exists = (got != (this->histogram).end());

    // The count of the token will be incremented if it exists, otherwise the token
    // will be added to the histogram with the default value.
    if (token_exists) {
        // Increment the count.
        (got->second)++;
    } else {
        // Add the token with the default count.
        (this->histogram).insert({_to_add, this->default_value});
    }
}

/**
 * Get the count of the particular token. If the token does not exist, then
 * just return the default value.
 */
int TokenHistogram::get_count (const Token& _to_get) {
    TokenHistogram::Histogram::iterator got = (this->histogram).find(_to_get);
    bool token_exists = (got != (this->histogram).end());

    return token_exists ? got->second : this->default_value;
}

/**
 * Prints the histogram in a debugging friendly way.
 */
void TokenHistogram::print (unsigned long _threshold) const {
    // Used in the loop below.
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
