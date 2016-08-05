#include "Token.h"
#include "TokenEditor.h"

/**
 * Move constructor.
 */
Token::Token (Token&& _other) {
    this->token_str = std::move(_other.get_token_str());
}

/**
 * Move assignment operator.
 */
Token& Token::operator= (Token&& _other) {
    this->token_str = std::move(_other.get_token_str());
    return *this;
}

/**
 * Copy constructor.
 */
Token::Token (const Token& _other) {
    this->token_str = _other.get_token_str();
}

/**
 * Copy assignment operator.
 */
Token& Token::operator= (const Token& _other) {
    this->token_str = _other.get_token_str();
    return *this;
}

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

namespace {
template<typename T>
void print_vect (const std::vector<T>& _v) {
    for (const T& elem : _v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template<>
void print_vect<Token> (const std::vector<Token>& _v) {
    for (const Token& tk : _v) {
        std::cout << tk.get_token_str() << " ";
    }
    std::cout << std::endl;
}
}

/**
 * Gets all the edits for this token.
 */
const std::vector<Token>& Token::get_edits (unsigned int _edit_distance) {
    this->token_edits = TokenEditor::get_edits(this->token_edits, *this, _edit_distance);
    return this->token_edits;
}