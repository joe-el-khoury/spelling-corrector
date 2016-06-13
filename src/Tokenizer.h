#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <memory>

#include "Token.h"
#include "FileReader.h"

class Tokenizer {
    // A type that is just a list of Tokens.
    typedef std::vector<Token> TokenList;
public:
    Tokenizer (const std::string&);
    void tokenize (char);
private:
    Tokenizer::TokenList tokens;
    FileReader fr;
    std::string str_to_tokenize;
};

#endif /* TOKENIZER_H */