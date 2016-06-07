#include <iostream>
#include <string>
#include <sstream>
#include "Tokenizer.h"

/* DELETE THESE INCLUDE STATEMENTS LATER */
#include <vector>
#include <fstream>
#include <algorithm>
#include <memory>

int main (int argc, const char* argv[]) {
	Tokenizer tk("Hel,lo my nam'e is joe");
	unsigned int size = tk.tokens.size();
	for (unsigned int i = 0; i < size; i++) {
		std::cout << (tk.tokens)[i] << std::endl;
	}
	return 0;
}