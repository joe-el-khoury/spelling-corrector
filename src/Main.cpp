#include <iostream>
#include <chrono>

#include "SpellingCorrector.h"

int main (int argc, const char* argv[]) {std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;

    SpellingCorrector sp;
    std::cout << "+================Training================+" << std::endl;
    start = std::chrono::system_clock::now();
    sp.train("big.txt");
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    std::cout << "Training took " << elapsed_seconds.count() << " second(s)." << std::endl;

    std::cout << "+================Correcting================+" << std::endl;
    std::string to_correct;
    Token corrected;
    std::cout << "correct>> ";
    while (std::getline(std::cin, to_correct)) {
        start = std::chrono::system_clock::now();
        corrected = sp.correct_word(Token(to_correct));
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "<" << to_correct << "> ===> <" << corrected.get_token_str() << "> ";
        std::cout << "(" << elapsed_seconds.count() << " second(s)).\n" << std::endl;
        std::cout << "correct>> ";
    }
    
    return 0;
}