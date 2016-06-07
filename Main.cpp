#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "Tokenizer.h"

/* DELETE THIS INCLUDE STATEMENT LATER */
#include <memory>

int main (int argc, const char* argv[]) {
	Tokenizer tk("Hello");
	unsigned int size = tk.tokens.size();
	for (unsigned int i = 0; i < size; i++) {
		std::cout << *tk.tokens.at(i).get() << std::endl;
	}
	return 0;
}