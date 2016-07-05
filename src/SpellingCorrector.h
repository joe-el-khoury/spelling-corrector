#ifndef SPELLINGCORRECTOR_H
#define SPELLINGCORRECTOR_H

#include <string>
#include <vector>
#include <memory>

#include "util/FileReader.h"
#include "Tokenizer.h"
#include "TokenHistogram.h"

class SpellingCorrector {
public:
    SpellingCorrector ();
    
    // Trains the spelling corrector on a file.
    void train (const std::string&, int=900);

    std::vector<Token> get_known_edits_of (const Token&, unsigned int=1);
private:
    // The essential parts of the engine.
    std::unique_ptr<FileReader> file_reader;
    std::unique_ptr<Tokenizer> tokenizer;
    std::unique_ptr<TokenHistogram> token_histogram;

    void remove_unknown_words_from (std::vector<Token>&);
    bool is_known_word (const Token&);
    
    // The names of the files we've already trained on.
    std::vector<std::string> files_trained_on;
    bool already_trained_on (const std::string&) const;
};

#endif /* SPELLINGCORRECTOR_H */