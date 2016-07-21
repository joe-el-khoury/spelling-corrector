#ifndef SPELLINGCORRECTORTRAINER_H
#define SPELLINGCORRECTORTRAINER_H

#include <memory>

#include "util/FileReader.h"
#include "util/MySQLInterface.h"
#include "Tokenizer.h"

class SpellingCorrectorTrainer {
public:
    SpellingCorrectorTrainer ();
private:
    // Used for training.
    std::unique_ptr<FileReader> file_reader;
    Tokenizer tokenizer;
    std::unique_ptr<MySQLInterface> mysql_interface;
};

#endif