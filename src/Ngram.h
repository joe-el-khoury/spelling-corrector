#ifndef NGRAM_H
#define NGRAM_H

#include <deque>
#include <vector>
#include <unordered_map>

#include "Token.h"

class Ngram {
public:
    void add (const Token&);
    bool more (unsigned int) const;

    std::vector<Token> get_ngram (unsigned int);
private:
    std::vector<Token> tokens;
    // The n and the index we're in in the list of tokens.
    std::unordered_map<unsigned int, unsigned int> n_and_at_index;
    unsigned int get_at_index (unsigned int) const;
};

#endif /* NGRAM_H */