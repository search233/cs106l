#ifndef CLASS_H_
#define CLASS_H_

#include <vector>
#include <cassert>


template <typename elementType>

class stack {

private:
    std::vector<elementType> vec;
    std::size_t topP;
    
    bool isFull() const;

public:
    stack();
    stack(std::size_t size);

    std::vector<elementType> get_vec() const;
    std::size_t get_topP() const;

    void set_vec(std::vector<elementType>);
    void set_topP(std::size_t num);

    
    const elementType getTop() const {
        assert(topP > 0);
        return vec[topP - 1];
    }
    
    const std::size_t getSize() const {
        return topP;
    }
    
    const bool isEmpty() const {
        return (topP == 0);
    }
    
    void push(const elementType& element) {
        if (isFull()) {
            vec.push_back(element);
        }
        else {
            vec[topP] = element;
        }
        topP = topP + 1;
    }
    
    void push(elementType&& element) {
        if (topP == vec.size()) {
            vec.push_back(element);
        }
        else {
            vec[topP] = element;
        }
        topP = topP + 1;
    }
    

    bool pop() {
        bool res = false;
    
        if (topP > 0) {
            res = true;
            topP = topP - 1;
        }
    
        return res;
    }
};

#include "class.cpp"

#endif
