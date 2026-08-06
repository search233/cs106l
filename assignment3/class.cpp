#ifndef CLASS_CPP_
#define CLASS_CPP_

#include "class.h"

template <typename elementType>
stack<elementType>::stack() : vec(10, elementType()), topP(0) {}

template <typename elementType>
stack<elementType>::stack(std::size_t size) : vec(size * 2, elementType()), topP(0) {}

template <typename elementType>
bool stack<elementType>::isFull() const {
    return topP == vec.size();
}

template <typename elementType>
std::vector<elementType> stack<elementType>::get_vec() const {
    return vec;
}

template <typename elementType>
std::size_t stack<elementType>::get_topP() const {
    return topP;
}

template <typename elementType>
void stack<elementType>::set_vec(std::vector<elementType> other_vec) {
    vec = other_vec;
}

template <typename elementType>
void stack<elementType>::set_topP(std::size_t num) {
    topP = num;
}

#endif
