#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <vector>

class Token {
public:
	Token (const std::string&);
	~Token();
	void cleanup_token ();
private:
	// These are characters in the token that should be removed from it in the
	// cleanup function.
	const std::vector<char> chars_to_cleanup = {
		'.', ',', '\'', ';'
	};
	friend std::ostream& operator<< (std::ostream&, const Token&);
	std::string token_str;
};

#endif /* TOKEN_H */