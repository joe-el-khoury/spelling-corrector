#include <iostream>
#include <chrono>

#include "SpellingCorrector.h"

int main (int argc, const char* argv[]) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;

    SpellingCorrector sp;
    std::cout << "+================Training================+" << std::endl;
    std::string to_train_on;
    std::cout << "train (type \"done\" to finish)>> ";
    while (std::getline(std::cin, to_train_on)) {
        if (to_train_on == "done") {
            break;
        }
        start = std::chrono::system_clock::now();
        sp.train(to_train_on);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end-start;
        std::cout << "Training on <" << to_train_on << "> took " << elapsed_seconds.count();
        std::cout << " second(s)." << std::endl;
        std::cout << "train>> ";
    }
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