#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Token.h"

class Tokenizer {
	// A unique pointer type to a token.
	typedef std::unique_ptr<Token> TokenPtr;
	// A type that is just a list of Token pointers.
	typedef std::vector<TokenPtr> TokenList;
public:
	Tokenizer (const std::string&);
	Tokenizer (const Tokenizer&) = delete;
	Tokenizer& operator= (const Tokenizer&) = delete;
	void tokenize (char);
	Tokenizer::TokenList tokens;
private:
	std::string str_to_tokenize;
};

#endif /* TOKENIZER_H */