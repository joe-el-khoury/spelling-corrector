#include "TokenEditor.h"

//////////////////////////////////////////////////////////////////
///////////////// HELPER FUNCTIONS ///////////////////////////////
//////////////////////////////////////////////////////////////////

/**
 * Swap two characters in a string.
 */
void swap_str_chars (std::string& _to_swap, int _pos1, int _pos2) {
    char temp_char  = _to_swap[_pos1];
    _to_swap[_pos1] = _to_swap[_pos2];
    _to_swap[_pos2] = temp_char;
}

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

    // Each deletion length will be the length of the token minus one.
    std::string deletion;
    deletion.reserve(token_str_length-1);

    splits split_edits = this->get_split_edits(_to_edit);
    
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

/**
 * Creates edits of the token as transposes.
 * get_transpose_edits("joe") = "oje", "jeo"
 */
transposes TokenEditor::get_transpose_edits (const Token& _to_edit) {
    std::string token_str = _to_edit.get_token_str();
    
    // The number of transposes is equal to the length of the string minus one.
    unsigned int token_str_length = token_str.length();
    transposes ret(token_str_length-1);

    // Each transpose length will be equal to the length of the token.
    std::string transpose;
    transpose.reserve(token_str_length);

    // Go through the string, transposing (swapping) characters.
    for (unsigned int i = 0; i < token_str_length-1; ++i) {
        transpose = token_str;
        swap_str_chars(transpose, i, i+1);

        ret[i] = transpose;
    }

    return ret;
}

/**
 * Creates edits of the tokens as replacements.
 * get_replace_edits("joe") = "aoe", ... "zoe", ... "jae", ... "jze", ... "joa", ... "joz".
 */
replaces TokenEditor::get_replace_edits (const Token& _to_edit) {
    std::string token_str = _to_edit.get_token_str();
    
    // The number of replaces is equal to the length of the string times 26.
    unsigned int token_str_length = token_str.length();
    transposes ret(token_str_length*26);

    // Each replace length will be equal to the length of the token.
    std::string replace;
    replace.reserve(token_str_length);

    // The index of the vector that will store the replaces.
    int j = 0;
    // Go through the string, replacing characters.
    for (unsigned int i = 0; i < token_str_length; ++i) {
        replace = token_str;
        for (const char& alphabet_char : this->alphabet) {
            replace[i] = alphabet_char;
            ret[j] = Token(replace);
            j++;
        }
    }

    return ret;
}