#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <vector>

class Token {
public:
    Token () { /* empty constructor */ };
    Token (const std::string&);
    Token (Token&&);
    Token& operator= (Token&&);
    Token (const Token&);
    Token& operator= (const Token&);
    
    bool operator== (const Token&) const;
    bool operator== (const std::string&) const;

    std::vector<Token> get_edits (unsigned int=1) const;

    // Used for cleaning up the token.
    void delimit_token ();
    char delimit_token_with = ' ';

    const std::string& get_token_str () const;
private:
    bool is_clean_char (char);
    std::string token_str;
};

#endif /* TOKEN_H */