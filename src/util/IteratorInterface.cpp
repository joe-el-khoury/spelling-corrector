#include "IteratorInterface.h"

/**
 * Add a vector to the already existing vector.
 */
template<typename T>
void IteratorInterface<T>::add_to_iterable (const std::vector<T>& _to_add) {
    // To prevent additional allocations.
    (this->iterable).reserve((this->iterable).size() + _to_add.size());

    std::move_iterator<T> move_iter_begin = std::make_move_iterator(_to_add.begin());
    std::move_iterator<T> move_iter_end   = std::make_move_iterator(_to_add.end());
    (this->iterable).insert((this->iterable).begin(), move_iter_begin, move_iter_end);
}

/**
 * Add one element to the vector we will iterate on.
 */
template<typename T>
void IteratorInterface<T>::add_to_iterable (const T& _to_add) {
    (this->iterable).push_back(_to_add);
}