#ifndef NGRAM_H
#define NGRAM_H

#include <deque>
#include <vector>

#include "Token.h"

class Ngram {
public:
    // Add a token to the list of tokens.
    void add (const Token&);

    // Whether there are anymore ngrams to get.
    bool more (unsigned int);

    std::vector<Token> get_ngram (unsigned int);
private:
    std::deque<Token> tokens;
};

#endif