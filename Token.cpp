#include <algorithm>

#include "Token.h"

Token::Token (const std::string& _token_str) {
	this->token_str = _token_str;
}

Token::~Token() {
}

/**
 * Cleans up the token, removing any unecessary characters.
 */
void Token::cleanup_token () {
	// Just so I don't have to type in this->... every time. It's tedious!
	const std::vector<char>* chars_to_cleanup = &(this->chars_to_cleanup);
	// Go through the token, cleaning up as I go.
	for (char& c: this->token_str) {
		bool should_cleanup = 
			std::find((chars_to_cleanup)->begin(), (chars_to_cleanup)->end(), c) != (chars_to_cleanup)->end();
		if (should_cleanup) {
			// Replace the character with a null character if it should be cleaned up.
			c = '\0';
		}
	}
}

/**
 * For printing purposes.
 */
std::ostream& operator<< (std::ostream& os, const Token& _token) {
	return (os << _token.token_str);
}