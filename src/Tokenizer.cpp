#include <string>
#include <vector>
#include <algorithm>

#include "Tokenizer.h"
#include "FileReader.h"
#include "Token.h"

Tokenizer::Tokenizer (const std::string& _file_name) : fr(_file_name) {
}

Tokenizer::TokenList Tokenizer::get_tokens () {
    return this->tokens;
}

void Tokenizer::tokenize (char _delimiter) {
    std::string token_str;
    // Keep reading the file until the end. Never quit!
    while (!(this->fr).done_reading) {
        // Read the file until the delimiter.
        token_str = (this->fr).get_string_up_to(_delimiter);
        
        if (token_str.length() > 0) {
            Token token_to_add(token_str);
            Tokenizer::TokenList v = this->split_and_clean_token(token_to_add);

            // Add the tokens from the split to the list.
            for (Token& t : v) {
                (this->tokens).push_back(t);
            }
        }
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