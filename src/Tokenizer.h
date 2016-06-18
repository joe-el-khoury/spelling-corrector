#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

#include "Token.h"

class Tokenizer {
    // A type that is just a list of Tokens.
    typedef std::vector<Token> TokenList;
public:
    void tokenize (const std::string&, char);
    Tokenizer::TokenList get_tokens ();
private:
    Tokenizer::TokenList split_and_clean_token (Token&);
    Tokenizer::TokenList tokens;
};

#endif /* TOKENIZER_H */