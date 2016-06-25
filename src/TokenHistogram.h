#ifndef TOKENHISTOGRAM_H
#define TOKENHISTOGRAM_H

#include <unordered_map>
#include <string>

#include "Token.h"

namespace std {
/**
 * Template specialization for hashing the Token object.
 */
template<>
struct hash<Token> {
    size_t operator() (const Token& _other) const {
        // Basically all I'm doing is hashing the string of the token object.
        return std::hash<std::string>()(_other.get_token_str());
    }
};
}

class TokenHistogram {
    // The histogram is just an unordered map that maps tokens to
    // unsigned long.
    typedef std::unordered_map<Token, unsigned long> Histogram;
public:
    void add_tokens (const std::vector<Token>&);
    void add_token (const Token&);
    unsigned long get_count (const Token&);

    bool token_exists (const Token&) const;

    // For debugging purposes.
    void print (unsigned long=0) const;
private:
    // The actual histogram son!
    Histogram histogram;
    
    // The default value any token takes when added to the histogram or
    // when an undefined token is accessed.
    const unsigned long default_value = 1;
};

#endif /* TOKENHISTOGRAM_H */