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
    static unsigned int get_edit_distance (const Token&, const Token&);
private:
    // Edit functions.
    static deletes&    get_delete_edits    (deletes&&, const Token&);
    static transposes& get_transpose_edits (transposes&&, const Token&);
    static replaces&   get_replace_edits   (replaces&&, const Token&);
    static inserts&    get_insert_edits    (inserts&&, const Token&);
    static splits&     get_split_edits     (splits&&, const Token&);
};

#endif /* TOKENEDITOR_H */