#include "Token.h"
#include "TokenEditor.h"

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
 * Delimits the token at unclean characters with a space.
 */
void Token::delimit_token () {
    for (char& c : this->token_str) {
        if (!(this->is_clean_char(c))) {
            c = this->delimit_token_with;
        }
    }
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

const std::string& Token::get_token_str () const {
    return this->token_str;
}

/**
 * Gets all the edits for this token.
 */
std::vector<Token> Token::get_edits () const {
    return TokenEditor::get_edits(*this);
}