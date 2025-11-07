#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS();
    explicit ABS(const size_t capacity);
    ABS(const ABS& other);
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept;
    ABS& operator=(ABS&& rhs) noexcept;
    ~ABS() noexcept;

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override;

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept;

    // Push item onto the stack
    void push(const T& data) override;

    T peek() const override;

    T pop() override;

    void PrintForward() noexcept;

    void PrintReverse() noexcept;
    

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};

template <typename T>
ABS<T>::ABS() {
    capacity_ = 1;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template <typename T>
ABS<T>::~ABS() noexcept {
    delete[] array_;
    array_ = nullptr;                           // no dangler
}

// Copy Constructor
template <typename T>
ABS<T>::ABS(const ABS& other) {
    std::cout << "copy constructor called" << std::endl;
    this->capacity_ = other.capacity_;
    this->curr_size_ = other.curr_size_;
    this->array_ = new T[capacity_];
    
    for (size_t i = 0; i < this->curr_size_; i++) {   // Deep copy
        this->array_[i] = other.array_[i];
    }
}

// Copy Assignment Operator
template <typename T>
ABS<T>& ABS<T>::operator=(const ABS& rhs) {
    std::cout << "copy assignment op called" <<std::endl;
    this->capacity_ = rhs.capacity_;
    this->curr_size_ = rhs.curr_size_;
    this->array_ = new T[capacity_];
    
    for (size_t i = 0; i < this->curr_size_; i++) {   // Deep copy
        this->array_[i] = rhs.array_[i];
    }

    return *this;
}

// Move Constructor
template <typename T>
ABS<T>::ABS(ABS&& other) noexcept {
    std::cout << "move constructor called" << std::endl;
    this->capacity_ = other.capacity_;
    this->curr_size_ = other.curr_size_;

    delete[] this->array_;
    this->array_ = new T[capacity_];
    
    for (size_t i = 0; i < this->curr_size_; i++) {   // Deep copy
        this->array_[i] = other.array_[i];
    }

    other.capacity_ = 0;
    other.curr_size_ = 0;
    delete[] other.array_;
    other.array_ = nullptr;
}

// Move Assignment Operator
template <typename T>
ABS<T>& ABS<T>::operator=(ABS&& other) noexcept {
    std::cout << "move op called" <<std::endl;
    if (this == &other) {
        return *this;
    }

    this->capacity_ = other.capacity_;
    this->curr_size_ = other.curr_size_;

    delete[] this->array_;
    this->array_ = new T[capacity_];
    
    for (size_t i = 0; i < this->curr_size_; i++) {   // Deep copy
        this->array_[i] = other.array_[i];
    }

    other.capacity_ = 0;
    other.curr_size_ = 0;
    delete[] other.array_;
    other.array_ = nullptr;

    return *this;
}



template <typename T>
T* ABS<T>::getData() const noexcept {
    return curr_size_;
}

template<typename T>
void ABS<T>::push(const T& data) {
    if (curr_size_ >= capacity_) {              // If the capacity needs to be scaled
        T* tempArray_ = new T[capacity_ * scale_factor_];
        for (size_t i = 0; i < capacity_; i++) {   // Copy array elements to tempArray
            tempArray_[i] = array_[i];
        }
        delete[] array_;
        array_ = std::move(tempArray_);         // Move ownership of tempArray data to array
        tempArray_ = nullptr;                   // No dangling pointer pls
        capacity_ *= 2;                         // Make sure to change the capacity to the new capacity
    }
    array_[curr_size_] = data;
    curr_size_++;                               // Increment current size
}

template <typename T>
T ABS<T>::pop() {                               // totally removing an element here
    curr_size_--;
    return array_[curr_size_];
}

template <typename T>
T ABS<T>::peek() const {
    return array_[curr_size_ - 1];
}

template<typename T>
size_t ABS<T>::getSize() const noexcept {
    return curr_size_;
}

template<typename T>
size_t ABS<T>::getMaxCapacity() const noexcept {
    return capacity_;
}

template <typename T>
void ABS<T>::PrintForward() noexcept {
    for (size_t i = 0; i < curr_size_; i++) {
        std::cout << array_[i] << std::endl;
    }
}

template <typename T>
void ABS<T>::PrintReverse() noexcept {
    for (size_t i = curr_size_ - 1; i >= 0; i--) {
        std::cout << array_[i] << std::endl;
    }
}


