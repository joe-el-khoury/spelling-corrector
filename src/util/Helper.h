#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <algorithm>

namespace helper {

/**
 * Merges a bunch of vectors together into the first vector.
 */
template<typename T>
T& merge (std::vector<T>& _vector_list) {
    // Merge all the vectors into the first vector.
    T& merge_into = _vector_list[0];

    // Get the total size of the vectors.
    unsigned int total_size = 0;
    for (const T& vec : _vector_list) {
        total_size += vec.size();
    }
    total_size -= merge_into.size();

    merge_into.reserve(total_size);
    std::for_each(_vector_list.begin()+1, _vector_list.end(),
        /**
         * Concatenate the vectors.
         */
        [&](const T& _vec) {
            auto begin_move_iter = std::make_move_iterator(_vec.begin());
            auto end_move_iter   = std::make_move_iterator(_vec.end());
            merge_into.insert(merge_into.end(), begin_move_iter, end_move_iter);
        }
    );

    return merge_into;
}

template<typename T>
std::vector<T>& merge (std::vector< std::vector<T> >&& _vector_list) {
    return merge(_vector_list);
}

} /* namespace helper */

#endif /* HELPER_H */