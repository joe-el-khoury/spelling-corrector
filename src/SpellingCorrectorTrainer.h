#ifndef SPELLINGCORRECTORTRAINER_H
#define SPELLINGCORRECTORTRAINER_H

#include <memory>

#include "util/FileReader.h"
#include "util/MySQLInterface.h"
#include "Tokenizer.h"
#include "Token.h"
#include "TokenHistogram.h"
#include "Ngram.h"

class SpellingCorrectorTrainer {
public:
    SpellingCorrectorTrainer ();
    
    void train (const std::string&);
    void train (const std::string&, const std::vector<unsigned int>&);
private:
    // Used for training.
    std::unique_ptr<FileReader> file_reader;
    Tokenizer tokenizer;
    TokenHistogram token_histogram;
    std::unique_ptr<MySQLInterface> mysql_interface;

    void insert_token_into_db (const Token&);
    void insert_token_into_db (const Token&, unsigned long);
    void insert_ngram_into_db (Ngram&, unsigned int);

    void add_to_already_trained_on (const std::string&, unsigned int=1);
    bool already_trained_on (const std::string&, unsigned int=1);
};

#endif