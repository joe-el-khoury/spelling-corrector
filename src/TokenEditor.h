#ifndef TOKENEDITOR_H
#define TOKENEDITOR_H

#include <vector>
#include <utility>

#include "Token.h"

class TokenEditor {
    // Custom types for splitting tokens.
    typedef std::pair<Token, Token> split_pair;
    typedef std::vector<split_pair> splits;
public:
    TokenEditor::splits get_split_edits (const Token&);
private:
    TokenEditor::split_pair split_at (const Token&, size_t);
    Token splice_token_from_to (const Token&, size_t, size_t);
}

#endif /* TOKENEDITOR_H */