#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ();
    explicit ABQ(const size_t capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept;

    // Getters
    [[nodiscard]] size_t getSize() const noexcept;
    [[nodiscard]] size_t getMaxCapacity() const noexcept;
    [[nodiscard]] T* getData() const noexcept;

    // Insertion
    void enqueue(const T& data);

    // Access
    T peek() const;

    // Deletion
    T dequeue();

private:
};

template <typename T>
ABQ<T>::ABQ() {
    capacity_ = 1;
    curr_size_ = 0;
    array_ = new T[1];
}

template <typename T>
ABQ<T>::~ABQ() noexcept {
    delete[] array_;
    array_ = nullptr;
}

template <typename T>
ABQ<T>::ABQ(const ABQ& other) {                         // Copy Constructor
    this->capacity_ = other.capacity_;
    this->curr_size_ = other.curr_size_;
    for (size_t i = 0; i < this->capacity; i++) {
        this->array_[i] = other.array_[i];
    }
}

template <typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ& rhs) {                         // Copy Assignment Operator
    this->capacity_ = rhs.capacity_;
    this->curr_size_ = rhs.curr_size_;
    for (size_t i = 0; i < this->capacity; i++) {
        this->array_[i] = rhs.array_[i];
    }
}

template <typename T>
ABQ<T>::ABQ(ABQ&& other) noexcept {
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
ABQ<T>& ABQ<T>::operator=(ABQ&& other) noexcept {
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
ABQ<T>::ABQ(const std::size_t capacity) {
    capacity_ = capacity;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template <typename T>
void ABQ<T>::enqueue(const T& e) {
    if (curr_size_ >= capacity_) {
        T* tempArray = new T[capacity_ * scale_factor_];
        for (size_t i = 0; i < capacity_; i++) {
            tempArray[i] = array_[i];
        }
        delete[] array_;                            // Delete old data
        array_ = std::move(tempArray);
        capacity_ *= 2;
    }
    array_[curr_size_] = e;
    curr_size_++;
}

template <typename T>
T ABQ<T>::dequeue() {
    if (curr_size_ == 0) {
        throw std::runtime_error("");
    }
    T temp = array_[0];                             // Front Index
    
    // Must shift everything now
    for (size_t i = 1; i < curr_size_; i++) {
        array_[i - 1] = array_[i];                   // Swap
    }
    curr_size_--;
    return temp;                                    // Return the dequeued value
}

template <typename T>
T ABQ<T>::peek() const {
    if (curr_size_ == 0) {
        throw std::runtime_error("");
    }
    return array_[0];
}

template <typename T>
size_t ABQ<T>::getSize() const noexcept {
    return curr_size_;
}
template <typename T>
size_t ABQ<T>::getMaxCapacity() const noexcept {
    return capacity_;
}

template <typename T>
T* ABQ<T>::getData() const noexcept {
    return array_;
}
