#ifndef TOKENEDITOR_H
#define TOKENEDITOR_H

#include <vector>
#include <utility>

#include "Token.h"

// Custom types.
typedef std::vector<Token> deletes;
typedef std::vector<Token> transposes;
typedef std::vector<Token> replaces;
typedef std::vector<Token> inserts;
typedef std::vector<Token> edits;
typedef std::pair<Token, Token> split_pair;
typedef std::vector<split_pair> splits;

class TokenEditor {
public:
    static edits get_edits (const Token&, unsigned int);
    
    // The English alphabet.
    static const std::vector<char> alphabet;
private:
    // Edit functions.
    static deletes    get_delete_edits    (const Token&);
    static transposes get_transpose_edits (const Token&);
    static replaces   get_replace_edits   (const Token&);
    static inserts    get_insert_edits    (const Token&);
    static splits     get_split_edits     (const Token&);
};

#endif /* TOKENEDITOR_H */