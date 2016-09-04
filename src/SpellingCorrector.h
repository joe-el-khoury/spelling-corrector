#ifndef SPELLINGCORRECTOR_H
#define SPELLINGCORRECTOR_H

#include <string>
#include <vector>
#include <memory>
#include <exception>
#include <stdexcept>

#include "Token.h"
#include "util/MySQLInterface.h"
#include "SpellingCorrectorInitializer.h"

class SpellingCorrector {
public:
    SpellingCorrector ();
    
    Token correct_word (const Token&);
private:
    Token get_best_candidate (const std::vector<Token>&);
    std::vector<Token> get_known_edits_of (const Token&, unsigned int=1);
    void remove_unknown_words_from (std::vector<Token>&);
    bool is_known_word (const Token&) const;

    // Stuff related to the backend.
    std::unique_ptr<MySQLInterface> mysql_conn;
};

#endif /* SPELLINGCORRECTOR_H */