#include <iostream>
#include <string>

#include "SpellingCorrector.h"
#include "SpellingCorrectorTrainer.h"

int main (int argc, const char* argv[]) {
    if (argc < 3) {
        std::cout << "usage: SpellingCorrector --train <file>" << std::endl;
        return 0;
    } else if (std::string(argv[1]) != std::string("--train")) {
        std::cout << "usage: SpellingCorrector --train <file>" << std::endl;
        return 0;
    } else {
        SpellingCorrectorTrainer trainer;
        std::string file_name(argv[2]);
        std::cout << "Training..." << std::endl;
        trainer.train(file_name);
    }
    return 0;
}