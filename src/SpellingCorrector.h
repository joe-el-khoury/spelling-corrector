#ifndef SPELLINGCORRECTOR_H
#define SPELLINGCORRECTOR_H

#include <memory>

#include "FileReader.h"
#include "Tokenizer.h"
#include "TokenHistogram.h"

class SpellingCorrector {
public:
    SpellingCorrector ();
private:
    // The parts of the engine.
    std::unique_ptr<FileReader> file_reader;
    std::unique_ptr<Tokenizer> tokenizer;
    std::unique_ptr<TokenHistogram> token_histogram;
};

#endif /* SPELLINGCORRECTOR_H */