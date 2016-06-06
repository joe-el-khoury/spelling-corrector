#include "Token.h"

Token::Token (const std::string& _token_str) {
	this->token_str = _token_str;
}

std::ostream& operator<< (std::ostream& os, const Token& _token) {
	return (os << _token.token_str);
}

void Token::cleanup_token () {
}