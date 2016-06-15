#ifndef TOKENHISTOGRAM_H
#define TOKENHISTOGRAM_H

#include <unordered_map>
#include <string>

#include "Token.h"

/**
 * Injecting a hash function into the standard namespace. Is it good practice
 * to do this in the TokenHistogram object or the Token object? I think it should
 * be better here because the Token object should't "know" that it is being hashed.
 */
namespace std {
    /**
     * Template specialization for hashing the Token object.
     */
    template<>
    struct hash<Token> {
        /**
         * Overload the () operator to define a custom hash function.
         */
        size_t operator() (const Token& _other) const {
            // Basically all I'm doing is hashing the string of the token object.
            return std::hash<std::string>()(_other.get_token_str());
        }
    };
}

class TokenHistogram {
    // The histogram is just an unordered map that maps tokens to
    // integers.
    typedef std::unordered_map<Token, unsigned long> Histogram;
public:
    TokenHistogram ();

    // Add/get a token to/from the histogram.
    void add_token (const Token&);
    int  get_count (const Token&);

    // For debugging purposes.
    void print ();
private:
    // The actual histogram son!
    Histogram histogram;
    
    // The default value any token takes when added to the histogram or
    // when an undefined token is accessed.
    const unsigned long default_value = 1;
};

#endif /* TOKENHISTOGRAM_H */