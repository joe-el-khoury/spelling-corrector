#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <vector>

class Token {
public:
    Token (const std::string&);
    bool operator== (const Token&) const;
    bool operator== (const std::string&) const;

    // Used for cleaning up the token.
    void delimit_token ();
    const char delimit_token_with = ' ';

    std::string get_token_str () const;
private:
    bool is_clean_char (char);
    std::string token_str;
};

#endif /* TOKEN_H */