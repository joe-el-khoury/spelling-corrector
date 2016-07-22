#ifndef SPELLINGCORRECTORTRAINER_H
#define SPELLINGCORRECTORTRAINER_H

#include <memory>

#include "util/FileReader.h"
#include "util/MySQLInterface.h"
#include "Tokenizer.h"
#include "Token.h"

class SpellingCorrectorTrainer {
public:
    SpellingCorrectorTrainer ();
    
    void train (const std::string&);
private:
    // Used for training.
    std::unique_ptr<FileReader> file_reader;
    Tokenizer tokenizer;
    std::unique_ptr<MySQLInterface> mysql_interface;

    void insert_token_into_db (const Token&);

    void add_to_already_trained_on (const std::string&);
    bool already_trained_on (const std::string&);
};

#endif