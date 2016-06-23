#include "TokenEditor.cpp"

/**
 * Just like Python's awesome string splicing capabilities.
 * splice_token_from_to("hello", 0, 3) = "hel".
 */
Token TokenEditor::splice_token_from_to (const Token& _to_splice, size_t _from, size_t _to) {
    std::string token_str = _to_splice.get_token_str();

    std::string new_token_str = token_str.substr(_from, _to);
    return Token(new_token_str);
}

/**
 * Splits a token at the pivot.
 * split_at("joe", 1) = ("j", "oe").
 */
TokenEditor::split_pair TokenEditor::split_at (const Token& _to_split, size_t _pivot) {
    std::string token_str = _to_split.get_token_str();
    Token first  = splice_token_from_to(token_str, 0, _pivot);
    Token second = splice_token_from_to(token_str, _pivot, token_str.length());

    return std::make_pair(first, second);
}

/**
 * Creates edits of the token as splits.
 * get_split_edits("joe") = ("", "joe"), ("j", "oe"), ("jo", "e"), ("joe", "").
 */
TokenEditor::splits get_split_edits (const Token& _to_edit) {
    // Construct the vector that will store the splits.
    // The vector's size will be the length of the string plus one.
    unsigned int str_length = _to_edit.get_token_str().length();
    std::vector<TokenEditor::split_pair> ret(str_length+1);

    for (size_t i = 0; i <= (size_t)(str_length); ++i) {
        ret[i] = split_at(_str, i);
    }

    return ret;
}