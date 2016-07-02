#ifndef ITERATORINTERFACE_H
#define ITERATORINTERFACE_H

#include <iterator>

template<typename T>
class IteratorInterface : public std::iterator<std::input_iterator_tag, T> {
};

#endif