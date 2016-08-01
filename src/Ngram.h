#ifndef NGRAM_H
#define NGRAM_H

#include <deque>
#include <vector>

#include "Token.h"

class Ngram {
public:
    void add (const Token&);
    bool more (unsigned int);

    std::vector<Token> get_ngram (unsigned int);
private:
    std::deque<Token> tokens;
};

#endif