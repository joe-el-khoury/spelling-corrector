#include <string>
#include <utility>

#include "TokenHistogram.h"
#include "Token.h"

TokenHistogram::TokenHistogram () {
    this->histogram = TokenHistogram::Histogram();
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