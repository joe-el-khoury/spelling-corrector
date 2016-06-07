#include <memory>
#include <algorithm>

#include "Tokenizer.h"
#include "Token.h"

Tokenizer::Tokenizer (const std::string& _str_to_tokenize) {
	this->tokens = Tokenizer::TokenList();
	this->str_to_tokenize = _str_to_tokenize;
	this->tokenize(' ');
}

void Tokenizer::tokenize (char _delimiter) {
	size_t start = 0;
	size_t end   = (this->str_to_tokenize).find_first_of(_delimiter);

	while (end <= std::string::npos) {
		std::string token_substr = (this->str_to_tokenize).substr(start, end-start);
		if (token_substr.length() > 0) {
			Token token_to_add(token_substr);
			(this->tokens).push_back(token_to_add);
		}

		if (end == std::string::npos) {
			break;
		}

		start = end+1;
		end = str_to_tokenize.find_first_of(_delimiter, start);
	}
}