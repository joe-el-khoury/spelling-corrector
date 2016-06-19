#ifndef SPELLINGCORRECTOR_H
#define SPELLINGCORRECTOR_H

#include <string>
#include <vector>
#include <memory>

#include "FileReader.h"
#include "Tokenizer.h"
#include "TokenHistogram.h"

class SpellingCorrector {
public:
    SpellingCorrector ();

    // Trains the spelling corrector on a file.
    void train (const std::string&);
private:
    // The parts of the engine.
    std::unique_ptr<FileReader> file_reader;
    std::unique_ptr<Tokenizer> tokenizer;
    std::unique_ptr<TokenHistogram> token_histogram;
    
    // The names of the files we've already trained on.
    std::vector<std::string> file_names;
};

#endif /* SPELLINGCORRECTOR_H */