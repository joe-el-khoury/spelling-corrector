#include <algorithm>

#include "Token.h"

Token::Token (const std::string& _token_str) {
    this->token_str = _token_str;
}

bool Token::operator== (const Token& _other_token) const {
    return (this->get_token_str() == _other_token.get_token_str());
}

bool Token::operator== (const std::string& _other_str) const {
    return (this->get_token_str() == _other_str);
}

/**
 * Cleans up the token, removing any unecessary characters.
 */
void Token::cleanup_token () {
    // Create a new string just in case the current one is unclean.
    std::string new_str;
    new_str.reserve((this->token_str).length());

    // Go through the token, cleaning it up.
    for (char& c : this->token_str) {
        c = std::tolower(c);
        if (this->is_clean_char(c)) {
            new_str += c;
        }
    }

    this->token_str = new_str;
}

std::string Token::get_token_str () const {
    return this->token_str;
}

/**
 * Checks if a character is "clean". A clean character is one that is either
 * an uppercase character (A-Z) or a lowercase character (a-z).
 */
bool Token::is_clean_char (char _char) {
    bool is_upper_letter = (0x41 <= _char && _char <= 0x5A);
    bool is_lower_letter = (0x61 <= _char && _char <= 0x7A);
    return (is_upper_letter || is_lower_letter);
}