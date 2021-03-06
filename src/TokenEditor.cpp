#include "TokenEditor.h"
#include "util/Helper.h"

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
std::string splice_string_from_to (const std::string& _to_splice, size_t _from, size_t _to=std::string::npos) {
    return (_from >= _to_splice.length()) ? std::string() : _to_splice.substr(_from, _to);
}

/**
 * splice_token_from_to("hello", 0, 3) = "hel".
 */
Token splice_token_from_to (const Token& _to_splice, size_t _from, size_t _to=std::string::npos) {
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
splits& TokenEditor::get_split_edits (splits&& _splits, const Token& _to_edit) {
    std::string token_str = _to_edit.get_token_str();
    
    // Construct the vector that will store the splits.
    // The vector's size will be the length of the string plus one.
    unsigned int token_str_length = token_str.length();
    _splits.reserve(token_str_length+1);

    for (size_t i = 0; i < (size_t)(_splits.size()); ++i) {
        _splits.push_back(split_at(Token(token_str), i));
    }

    return _splits;
}

/**
 * Creates edits of the token as deletions.
 * get_delete_edits("joe") = "oe", "je", "jo".
 */
deletes& TokenEditor::get_delete_edits (deletes&& _deletes, const Token& _to_edit) {
    std::string token_str = _to_edit.get_token_str();
    
    // The number of deletes is equal to the size of the string. That's nice!
    unsigned int token_str_length = token_str.length();
    _deletes.reserve(token_str_length);

    // Each deletion length will be the length of the token minus one.
    std::string deletion;
    deletion.reserve(token_str_length-1);

    splits split_edits = TokenEditor::get_split_edits({}, _to_edit);
    
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

        _deletes.push_back(Token(deletion));
    }

    return _deletes;
}

/**
 * Creates edits of the token as transposes.
 * get_transpose_edits("joe") = "oje", "jeo"
 */
transposes& TokenEditor::get_transpose_edits (transposes&& _transposes, const Token& _to_edit) {
    std::string token_str = _to_edit.get_token_str();
    
    // The number of transposes is equal to the length of the string minus one.
    unsigned int token_str_length = token_str.length();
    _transposes.reserve(token_str_length-1);

    // Each transpose length will be equal to the length of the token.
    std::string transpose;
    transpose.reserve(token_str_length);

    // Go through the string, transposing (swapping) characters.
    for (unsigned int i = 0; i < token_str_length-1; ++i) {
        transpose = token_str;
        swap_str_chars(transpose, i, i+1);

        _transposes.push_back(Token(transpose));
    }

    return _transposes;
}

// The English alphabet.
const std::vector<char> alphabet = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

/**
 * Creates edits of the tokens as replacements.
 * get_replace_edits("joe") = "aoe", ... "zoe", ... "jae", ... "jze", ... "joa", ... "joz".
 */
replaces& TokenEditor::get_replace_edits (replaces&& _replaces, const Token& _to_edit) {
    std::string token_str = _to_edit.get_token_str();
    
    // The number of replaces is equal to the length of the string times 26.
    unsigned int token_str_length = token_str.length();
    _replaces.reserve(token_str_length*26);

    // Each replace length will be equal to the length of the token.
    std::string replace;
    replace.reserve(token_str_length);

    for (char& to_replace : replace) {
        replace = token_str;
        for (const char alphabet_char : alphabet) {
            to_replace = alphabet_char;
            _replaces.push_back(Token(replace));
        }
    }

    return _replaces;
}

/**
 * Creates edits of the token as inserts.
 * get_insert_edits("joe") = "ajoe", ... "zjoe", ... "jaoe", ... "jzoe", ... "joae", ... "joze", ...
 */
inserts& TokenEditor::get_insert_edits (inserts&& _inserts, const Token& _to_edit) {
    std::string token_str = _to_edit.get_token_str();

    // The number of inserts is equal to 26 times the (length of the token + 1).
    unsigned int token_str_length = token_str.length();
    _inserts.reserve((token_str_length+1)*26);

    // Each insert will be equal to the length of the token plus one.
    std::string insert;
    insert.reserve(token_str_length+1);

    for (unsigned int i = 0; i < token_str_length+1; ++i) {
        insert = token_str;
        for (const char alphabet_char : alphabet) {
            // The string we are inserting. It consists solely of the character.
            std::string alphabet_str(1, alphabet_char);
            
            insert.insert(i, alphabet_str);
            _inserts.push_back(Token(insert));

            // Reset the string by removing the character from the string.
            insert.erase(insert.begin()+i);
        }
    }

    return _inserts;
}

edits TokenEditor::get_edits (const Token& _to_edit, unsigned int _edit_distance=1) {
    // Used to store edits.
    deletes    delete_edits;
    transposes transpose_edits;
    replaces   replace_edits;
    inserts    insert_edits;
    
    edits edits_ret = {_to_edit};
    for (unsigned int i = 0; i < _edit_distance; ++i) {
        for (const Token& edit : edits_ret) {
            deletes    deletes_temp    = TokenEditor::get_delete_edits({}, edit);
            transposes transposes_temp = TokenEditor::get_transpose_edits({}, edit);
            replaces   replaces_temp   = TokenEditor::get_replace_edits({}, edit);
            inserts    inserts_temp    = TokenEditor::get_insert_edits({}, edit);

            delete_edits    = helper::merge<Token>({delete_edits, deletes_temp});
            transpose_edits = helper::merge<Token>({transpose_edits, transposes_temp});
            replace_edits   = helper::merge<Token>({replace_edits, replaces_temp});
            insert_edits    = helper::merge<Token>({insert_edits, inserts_temp});
            
        }

        edits_ret = helper::merge<Token>({
            edits_ret,
            delete_edits, transpose_edits,
            replace_edits, insert_edits
        });
    }

    return edits_ret;
}

/**
 * Computes the Damerau–Levenshtein edit distance between the two tokens.
 */
unsigned int TokenEditor::get_edit_distance (const Token& _orig, const Token& _edit) {
    return 0; // suppress warnings.
}