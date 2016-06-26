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
    /**
     * Used the FNV-1a hash function to hash the token.
     */
    size_t operator() (const Token& _to_hash) const {
        unsigned long long hash      = 0xcbf29ce484222325;
                 long long fnv_prime = 0x100000001b3;
        const std::string& str = _to_hash.get_token_str();
        for (const char& c : str) {
            hash ^= c;
            hash *= fnv_prime;
        }

        return (size_t)(hash);
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