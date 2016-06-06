#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "Tokenizer.h"

template<typename T>
void print_vector (const std::vector<T>& vec) {
	typename std::vector<T>::const_iterator iter;
	for (iter = vec.begin(); iter != vec.end(); iter++) {
		std::cout << *iter << std::endl;
	}
}

/**
 * Tokenizes a string at a delimiter.
 */
std::vector<std::string> tokenize (const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	size_t start = 0;
	size_t end = str.find_first_of(delimiter);
	
	while (end <= std::string::npos) {
		token = str.substr(start, end-start);
		if (token.length() > 0) {
			// Only include non empty tokens.
			tokens.push_back(str.substr(start, end-start));
		}

		if (end == std::string::npos) {
			break;
		}

		start = end+1;
		end = str.find_first_of(delimiter, start);
	}

	return tokens;
}
#include <memory>
int main (int argc, const char* argv[]) {
	Tokenizer tk("Hello");
	unsigned int size = tk.tokens.size();
	for (unsigned int i = 0; i < size; i++) {
		std::cout << *tk.tokens.at(i).get() << std::endl;
	}
	return 0;
}