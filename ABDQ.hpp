#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ();
    explicit ABDQ(std::size_t capacity);
    ABDQ(const ABDQ& other);
    ABDQ(ABDQ&& other) noexcept;
    ABDQ& operator=(const ABDQ& other);
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ();

    // Insertion
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T& front() const override;
    const T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override;

    // Capacity Setters
    void ensureCapacity();
    void shrinkIfNeeded();
};

template <typename T>
ABDQ<T>::ABDQ() {
    size_ = 0;
    capacity_ = 4;
    front_ = 0;
    back_ = 0;
    data_ = new T[capacity_];
}

template <typename T>
ABDQ<T>::ABDQ(const size_t capacity) {
    size_ = 0;
    capacity_ = capacity;
    front_ = 0;
    back_ = 0;
    data_ = new T[capacity_];
}

template <typename T>
ABDQ<T>::~ABDQ() {
    delete[] data_;
    data_ = nullptr;
}

template <typename T>                       // Copy Constructor
ABDQ<T>::ABDQ(const ABDQ& other) {

}

template <typename T>                       // Copy Assignment Operator
ABDQ<T>& ABDQ<T>::operator=(const ABDQ& other) {

}

template <typename T>                       // Move Constructor
ABDQ<T>::ABDQ(ABDQ&& other) noexcept {

}

template <typename T>                       // Move Assignment Operator
ABDQ<T>& ABDQ<T>::operator=(ABDQ&& other) noexcept {

}

template <typename T>
void ABDQ<T>::ensureCapacity() {
    T tmpArr = new T[capacity_ * SCALE_FACTOR];            // Scale capacity
    for (size_t i = 0; i < size_; i++) {
        tmpArr[i] = data_[front_ + i];                      // Recenter the queue back to zero. will this make my life harder? maybe lol
    }
    delete[] data_;
    data_ = tmpArr;
    tmpArr = nullptr;

    front_ = 0;
    back_ = size_ - 1;
}

template <typename T>
void ABDQ<T>::shrinkIfNeeded() {
    if (size_ <= (capacity_ / SCALE_FACTOR) && (capacity_ % SCALE_FACTOR) == 0) { // Check if size is smaller than half the capacity and also check if capacity is even disvisible with no remainders
        T tmpArr = new T[capacity_ / SCALE_FACTOR];
        for (size_t i = 0; i < size_; i++) {
            tmpArr[i] = data_[front_ + i];                      // Recenter the queue back to zero. will this make my life harder? maybe lol
        }
        delete[] data_;
        data_ = tmpArr;
        tmpArr = nullptr;
        capacity_ /= SCALE_FACTOR;
        front_ = 0;
        back_ = size_ - 1;
    }
}

template <typename T>
void ABDQ<T>::pushFront(const T &item) {
    if (front_ == 0) {                   // If front of the deque is literally at the start of the array
        front_ = capacity_;          // Set front index to wrap around to the back of the array
    }
    front_--;
    data_[front_] = item;
}

template <typename T>
void ABDQ<T>::pushBack(const T &item) {
    if (back_ == capacity_ - 1) {        // If back of deque is literally the end of the array
        back_ = 0;                      // Set back index to wrap around to the start of the array
    }
    data_[back_] = item;
    back_++;
}

template <typename T>
T ABDQ<T>::popFront() {
    if (front_ == back_) {
        throw std::runtime_error("empty");
    }
    T val = data_[front_];
    if (front_ == capacity_ - 1) {        // If front of deque is literally at the end of the array
        front_ = -1;
    }
    front_++;
    return val;
}

template <typename T>
T ABDQ<T>::popBack() {
    if (front_ == back_) {
        throw std::runtime_error("empty");
    }
    T val = data_[back_];
    if (back_ == 0) {        // If back of deque is literally at the start of the array
        back_ = capacity_;
    }
    back_--;
    return val;
}

template <typename T>
const T& ABDQ<T>::front() const {
    if (front_ == back_) {
        throw std::runtime_error("empty");
    }
    return data_[front_];
}

template <typename T>
const T& ABDQ<T>::back() const {
    if (front_ == back_) {
        throw std::runtime_error("empty");
    }
    return data_[back_ - 1];
}

template <typename T>
std::size_t ABDQ<T>::getSize() const noexcept {
    return size_;
}
