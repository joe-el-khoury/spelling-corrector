#ifndef TOKENEDITOR_H
#define TOKENEDITOR_H

#include <vector>
#include <utility>

#include "Token.h"

// Custom types.
typedef std::pair<Token, Token> split_pair;
typedef std::vector<split_pair> splits;
typedef std::vector<Token> deletes;

class TokenEditor {
public:
    splits  get_split_edits  (const Token&);
    deletes get_delete_edits (const Token&);
};

#endif /* TOKENEDITOR_H */