#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

#include "Token.h"
#include "FileReader.h"

class Tokenizer {
    // A type that is just a list of Tokens.
    typedef std::vector<Token> TokenList;
public:
    Tokenizer (const std::string&);
    void tokenize (char);
    
    Tokenizer::TokenList get_tokens ();
private:
    Tokenizer::TokenList split_and_clean_token (Token&);
    Tokenizer::TokenList tokens;
    std::string str_to_tokenize;
};

#endif /* TOKENIZER_H */