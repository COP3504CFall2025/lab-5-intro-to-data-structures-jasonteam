#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS();

    // Insertion
    void push(const T& item) override;

    // Deletion
    T pop() override;

    // Access
    T peek() const override;

    //Getters
    std::size_t getSize() const noexcept override;
};

template <typename T>
LLS<T>::LLS() {

}

template <typename T>
void LLS<T>::push(const T& item) {
    list.addHead(item);
}

template <typename T>
T LLS<T>::pop() {
    if (list.getCount() == 0) {
        throw std::runtime_error("");
    }
    T tmp = list.getHead()->data;
    list.removeHead();
    return tmp;
}

template <typename T>
T LLS<T>::peek() const {
    return list.getHead()->data;
}

template <typename T>
std::size_t LLS<T>::getSize() const noexcept {
    return list.getCount();
}