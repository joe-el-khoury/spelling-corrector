#include <string>
#include <vector>

#include "Tokenizer.h"
#include "FileReader.h"
#include "Token.h"

Tokenizer::Tokenizer (const std::string& _file_name) : fr(_file_name) {
}

void Tokenizer::tokenize (char _delimiter) {
    std::string token_str;
    // Keep reading the file until the end. Never quit!
    while (!(this->fr).done_reading) {
        // Read the file until the delimiter.
        token_str = (this->fr).get_string_up_to(_delimiter);
        
        if (token_str.length() > 0) {
            Token token_to_add(token_str);
            token_to_add.cleanup_token();
            
            // Skip any empty tokens.
            if (token_to_add == "") {
                continue;
            }

            (this->tokens).push_back(token_to_add);
        }
    }
}