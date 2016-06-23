#include "TokenEditor.h"

//////////////////////////////////////////////////////////////////
///////////////// HELPER FUNCTIONS ///////////////////////////////
//////////////////////////////////////////////////////////////////

/**
 * Just like Python's awesome string splicing capabilities.
 */
std::string splice_string_from_to (const std::string& _to_splice, size_t _from, size_t _to) {
    return _to_splice.substr(_from, _to);
}

/**
 * splice_token_from_to("hello", 0, 3) = "hel".
 */
Token splice_token_from_to (const Token& _to_splice, size_t _from, size_t _to) {
    std::string token_str = _to_splice.get_token_str();
    std::string spliced_token_str = splice_string_from_to(token_str, _from, _to);
    
    return Token(spliced_token_str);
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

//////////////////////////////////////////////////////////////////
///////////////// EDIT FUNCTIONS /////////////////////////////////
//////////////////////////////////////////////////////////////////

/**
 * Creates edits of the token as splits.
 * get_split_edits("joe") = ("", "joe"), ("j", "oe"), ("jo", "e"), ("joe", "").
 */
splits TokenEditor::get_split_edits (const Token& _to_edit) {
    std::string token_str = _to_edit.get_token_str();
    
    // Construct the vector that will store the splits.
    // The vector's size will be the length of the string plus one.
    unsigned int token_str_length = token_str.length();
    splits ret(token_str_length+1);

    for (size_t i = 0; i < (size_t)(ret.size()); ++i) {
        ret[i] = split_at(token_str, i);
    }

    return ret;
}

/**
 * Creates edits of the token as deletions.
 * get_delete_edits("joe") = "oe", "je", "jo".
 */
deletes TokenEditor::get_delete_edits (const Token& _to_edit) {
    std::string token_str = _to_edit.get_token_str();
    
    // The number of deletes is equal to the size of the string. That's nice!
    unsigned int token_str_length = token_str.length();
    deletes ret(token_str_length);

    // The token's deletion.
    // Each deletion length will be the length of the token string minus one.
    std::string deletion;
    deletion.reserve(token_str_length-1);

    splits split_edits = get_split_edits(_to_edit);
    
    // The index of the vector we will be adding to.
    int i = 0;
    for (const split_pair& split : split_edits) {
        // Extract the strings from each pair.
        std::string first_str  = split.first.get_token_str();
        std::string second_str = split.second.get_token_str();
        
        if (second_str.empty()) {
            // Ignore a pair if it's second string is empty.
            continue;
        }

        // Create the deletion from the split, ignoring the second split's first character.
        deletion = first_str + splice_string_from_to(second_str, 1, second_str.length());

        ret[i] = Token(deletion);
        i++;
    }

    return ret;
}