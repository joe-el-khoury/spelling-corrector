#include "TokenEditor.h"

/**
 * Just like Python's awesome string splicing capabilities.
 * splice_token_from_to("hello", 0, 3) = "hel".
 */
Token splice_token_from_to (const Token& _to_splice, size_t _from, size_t _to) {
    std::string token_str = _to_splice.get_token_str();
    return token_str.substr(_from, _to);
}

/**
 * Splits a token at the pivot.
 * split_at("joe", 1) = ("j", "oe").
 */
split_pair split_at (const Token& _to_split, size_t _pivot) {
    Token first  = splice_token_from_to(_to_split, 0, _pivot);
    Token second = splice_token_from_to(_to_split, _pivot, _to_split.get_token_str().length());

    return std::make_pair(first, second);
}

/**
 * Creates edits of the token as splits.
 * get_split_edits("joe") = ("", "joe"), ("j", "oe"), ("jo", "e"), ("joe", "").
 */
splits TokenEditor::get_split_edits (const Token& _to_edit) {
    std::string token_str = _to_edit.get_token_str();
    
    // Construct the vector that will store the splits.
    // The vector's size will be the length of the string plus one.
    unsigned int str_length = _to_edit.get_token_str().length();
    splits ret(str_length+1);

    for (size_t i = 0; i <= (size_t)(str_length); ++i) {
        ret[i] = split_at(token_str, i);
    }

    return ret;
}