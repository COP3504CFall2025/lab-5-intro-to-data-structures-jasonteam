#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ();

    // Core Insertion Operations
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Core Removal Operations
    T popFront() override;
    T popBack() override;

    // Element Accessors
    const T& front() const override;
    const T& back() const override;

    // Getter
    std::size_t getSize() const noexcept override;
};

template <typename T>
LLDQ<T>::LLDQ() {   }

template <typename T>
void LLDQ<T>::pushFront(const T& item) {
    list.addHead(item);
}

template <typename T>
void LLDQ<T>::pushBack(const T& item) {
    list.addTail(item);
}

template <typename T>
T LLDQ<T>::popFront() {
    if (list.getCount() == 0) {
        throw std::runtime_error("");
    }
    T tmp = list.getHead()->data;
    list.removeHead();
    return tmp;
}

template <typename T>
T LLDQ<T>::popBack() {
    if (list.getCount() == 0) {
        throw std::runtime_error("");
    }
    T tmp = list.getTail()->data;
    list.removeTail();
    return tmp;
}

template <typename T>
const T& LLDQ<T>::front() const {
    if (list.getCount() == 0) {
        throw std::runtime_error("");
    }
    return list.getHead()->data;
}

template <typename T>
const T& LLDQ<T>::back() const {
    if (list.getCount() == 0) {
        throw std::runtime_error("");
    }
    return list.getTail()->data;
}

template <typename T>
std::size_t LLDQ<T>::getSize() const noexcept {
    return list.getCount();
}



