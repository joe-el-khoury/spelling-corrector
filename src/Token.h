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

    void cleanup_token ();
    std::string get_token_str () const;
private:
    bool is_clean_char (char);
    std::string token_str;
    friend std::ostream& operator<< (std::ostream&, const Token&);
};

#endif /* TOKEN_H */