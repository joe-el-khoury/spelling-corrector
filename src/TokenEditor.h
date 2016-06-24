#ifndef TOKENEDITOR_H
#define TOKENEDITOR_H

#include <vector>
#include <utility>

#include "Token.h"

typedef std::pair<Token, Token> split_pair;
typedef std::vector<split_pair> splits;

typedef std::vector<Token> deletes;
typedef std::vector<Token> transposes;
typedef std::vector<Token> replaces;
typedef std::vector<Token> inserts;

class TokenEditor {
public:
    void x (std::string&);
    // Edit functions.
    deletes    get_delete_edits    (const Token&);
    transposes get_transpose_edits (const Token&);
    replaces   get_replace_edits   (const Token&);
    inserts    get_insert_edits    (const Token&);
    
private:
    splits get_split_edits (const Token&);
    // The English alphabet.
    const std::vector<char> alphabet = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };
};

#endif /* TOKENEDITOR_H */