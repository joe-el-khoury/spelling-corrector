#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Token.h"

class Tokenizer {
	// A type that is just a list of Token pointers.
	typedef std::vector<Token> TokenList;
public:
	Tokenizer (const std::string&);
	void tokenize (char);
	Tokenizer::TokenList tokens;
private:
	std::string str_to_tokenize;
};

#endif /* TOKENIZER_H */