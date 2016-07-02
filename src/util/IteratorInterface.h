#ifndef ITERATORINTERFACE_H
#define ITERATORINTERFACE_H

#include <iterator>
#include <vector>

template<typename T>
class IteratorInterface : public std::iterator<std::input_iterator_tag, T> {
public:
    // Add to the list we will iterate on.
    void add_to_iterable (const std::vector<T>&);
    void add_to_iterable (const T&);
private:
    // The list we will iterate on.
    std::vector<T> to_iterate;
};

#endif