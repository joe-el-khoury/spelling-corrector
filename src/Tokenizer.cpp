#include <string>
#include <vector>
#include <algorithm>

#include "Tokenizer.h"
#include "FileReader.h"
#include "Token.h"

Tokenizer::Tokenizer (const std::string& _str_to_tokenize) {
    this->str_to_tokenize = _str_to_tokenize;
}

Tokenizer::TokenList Tokenizer::get_tokens () {
    return this->tokens;
}

void Tokenizer::tokenize (char _delimiter) {
    size_t start = 0;
    size_t end = (this->str_to_tokenize).find_first_of(_delimiter);

    while (end <= std::string::npos) {
        // Get the string from the start position to the delimiter.
        std::string token_substr = (this->str_to_tokenize).substr(start, end-start);
        if (token_substr.length() > 0) {
            Token token_to_add(token_substr);
            // Remove ugly characters from the token.
            Tokenizer::TokenList split_token = this->split_and_clean_token(token_to_add);
            for (Token& t : split_token) {
                (this->tokens).push_back(t);
            }
        }

        if (end == std::string::npos) {
            break;
        }

        start = end+1;
        end = (this->str_to_tokenize).find_first_of(_delimiter, start);
    }
}

/**
 * Cleans up the token, while splitting it.
 * Example: split_and_clean_token("joe.khoury") => ["joe", "khoury"].
 * This is better than "joekhoury".
 */
Tokenizer::TokenList Tokenizer::split_and_clean_token (Token& _to_clean) {
    // Delimit the token at unclean characters.
    _to_clean.delimit_token();

    Tokenizer::TokenList ret;

    std::string temp_token_str;
    // A flag that is set to true when we are building the string from
    // clean characters.
    bool building_str = false;
    
    for (char c : _to_clean.get_token_str()) {
        if (c != _to_clean.delimit_token_with) {
            building_str = true;
            temp_token_str += tolower(c);
        
        } else {
            if (building_str) {
                ret.push_back(Token(temp_token_str));   
                building_str = false;

                // Reset the string to start building a new one.
                temp_token_str = std::string();
            }
        }
    }

    // Don't forget to add the last token string!
    if (building_str) {
        ret.push_back(Token(temp_token_str));
    }

    return ret;
}
