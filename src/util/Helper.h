#ifndef HELPER_H
#define HELPER_H

#include <vector>

namespace helper {

/**
 * Merges a bunch of vectors together into the first vector.
 */
template<typename T>
T& merge (std::vector<T>& _vector_list) {
    // We will merge all the vectors into the first vector.
    T& merge_into = _vector_list[0];

    // Get the total size of the vectors.
    unsigned int total_size = 0;
    for (const T& vec : _vector_list) {
        total_size += vec.size();
    }
    total_size -= merge_into.size();

    merge_into.reserve(total_size);
    for (T& vec : _vector_list) {
        if (vec == merge_into) {
            continue;
        }

        // Move the elements into the vector.
        auto begin_move_iter = std::make_move_iterator(vec.begin());
        auto end_move_iter   = std::make_move_iterator(vec.end());
        merge_into.insert(merge_into.end(), begin_move_iter, end_move_iter);
    }

    return merge_into;
}

template<typename T>
std::vector<T>& merge (std::vector< std::vector<T> >&& _vector_list) {
    return merge(_vector_list);
}

} /* namespace helper */

#endif /* HELPER_H */