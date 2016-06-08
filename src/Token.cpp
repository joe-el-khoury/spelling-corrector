#include <algorithm>

#include "Token.h"

Token::Token (const std::string& _token_str) {
	this->token_str = _token_str;
}

/**
 * Cleans up the token, removing any unecessary characters.
 */
void Token::cleanup_token () {
	// Go through the token, cleaning it up.
	for (char& c: this->token_str) {
		// The character should be lowercase.
		c = std::tolower(c);
		if (!(this->is_clean_char(c))) {
			// If the character is not clean then ignore it.
			c = '\0';
		}
	}
}

/**
 * Checks if a character is "clean". A clean character is one that is either a digit (0-9),
 * an uppercase character (A-Z), or a lowercase character (a-z).
 */
bool Token::is_clean_char (char _char) {
	bool is_digit        = (0x30 <= _char && _char <= 0x39);
	bool is_upper_letter = (0x41 <= _char && _char <= 0x5A);
	bool is_lower_letter = (0x61 <= _char && _char <= 0x7A);
	return (is_digit || is_upper_letter || is_lower_letter);
}

/**
 * For printing purposes.
 */
std::ostream& operator<< (std::ostream& os, const Token& _token) {
	return (os << _token.token_str);
}