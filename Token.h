#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

class Token {
public:
	Token (const std::string&);
	Token (const Token&) = delete;
	Token& operator= (const Token&) = default;
	void cleanup_token ();
private:
	friend std::ostream& operator<< (std::ostream&, const Token&);
	std::string token_str;
};

#endif /* TOKEN_H */