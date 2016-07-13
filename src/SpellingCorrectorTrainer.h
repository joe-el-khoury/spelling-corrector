#ifndef SPELLINGCORRECTORTRAINER_H
#define SPELLINGCORRECTORTRAINER_H

#include <memory>

class SpellingCorrectorTrainer {
private:
    // Used for training.
    std::unique_ptr<FileReader> file_reader;
    std::unique_ptr<Tokenizer> tokenizer;
    std::unique_ptr<TokenHistogram> token_histogram;
};

#endif