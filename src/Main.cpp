#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include "SpellingCorrectorTrainer.h"

namespace po = boost::program_options;

int main (int argc, char const* argv[]) {
    std::vector<unsigned int> ngrams_to_train_with;
    const unsigned int max_n = 5;
    std::string training_file;
    
    po::options_description training_desc("Spelling corrector training");
    training_desc.add_options()
        ("help,h", "View available options.")
        ("ngram,n", po::value<decltype(ngrams_to_train_with)>(&ngrams_to_train_with)
                                        ->value_name("n")->multitoken()
                                        ->default_value(std::vector<unsigned int>(1, 1), "1"),
                                                    "Train with n-gram (default is 1). "
                                                    "The higher the number, "
                                                    "the better the spelling correction will be, "
                                                    "but the slower the training will be. "
                                                    "It is recommended to use 1 and 2. The maximum "
                                                    "n is 5.")
        
        ("train,t", po::value<decltype(training_file)>(&training_file)
                                        ->value_name("path/to/file")->required(),
                                                    "Train on a file.");

    po::variables_map vm;
    try {
        if (vm.count("help")) {
            std::cout << training_desc;
            return 0;
        }
        po::store(po::command_line_parser(argc, argv).options(training_desc).run(), vm);
        po::notify(vm);
        // Make sure n does not exceed the maximum n.
        for (auto& n : ngrams_to_train_with) {
            if (n > max_n) {
                n = 0;
            }
        }

        SpellingCorrectorTrainer spt;
        spt.train(training_file, ngrams_to_train_with);
    } catch (...) {
        std::cout << training_desc;
        return 1;
    }
    return 0;
}