#pragma once

#include <iostream>
#include <vector>

#include <iterator>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>


class IntVector {
public:
    IntVector() : size_(0), capacity_(0), data_(nullptr) {}

    // explicit конструктор с размером 
    explicit IntVector(size_t size) :
        size_(size), capacity_(size_), data_(new int[capacity_]) {
        for (int i = 0; i < size_; ++i) {
            data_[i] = 0;
        }
    }

    // конструктор со списком инициализации 
    explicit IntVector(std::initializer_list<int> list) :
        size_(list.size()), capacity_(size_), data_(new int[capacity_]) {
        const int* ptr = list.begin();

        for (int i = 0; i < size_; ++i) {
            data_[i] = *ptr;
            ++ptr;
        }
    }

    // конструктор копирования 
    IntVector(const IntVector& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new int[capacity_];
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    /* конструктор перемещения */
    IntVector(IntVector&& other) :
        size_(std::exchange(other.size_, 0)),
        capacity_(std::exchange(other.capacity_, 0)),
        data_(std::exchange(other.data_, nullptr))
    { }

    // деструктор 
    ~IntVector() {
        size_ = 0;
        capacity_ = 0;
        delete[] data_;
    }

    // оператор присваивания copy&swap 
    IntVector& operator=(IntVector other) {
        this->Swap(other);
        return *this;
    }

    // const-метод Size 
    size_t Size() const {
        return size_;
    }

    // const-метод Capacity 
    size_t  Capacity() const {
        return capacity_;
    }

    // void-метод PushBack(int) 
    void PushBack(int value) {
        if (size_ == capacity_) {
            capacity_ = 2 * size_;
            if (capacity_ == 0) {
                capacity_ = 1;
            }

            int* tmp = new int[capacity_];
            std::copy(data_, data_ + size_, tmp);
            delete[] data_;
            data_ = tmp;
        }
        data_[size_++] = value;
    }

    // void-метод PopBack() 
    void PopBack() {
        --size_;
    }

    // void-метод Clear() 
    void Clear() {
        size_ = 0;
    }

    // void-метод Reserve() 
    void Reserve(int capacity) {
        if (capacity_ >= capacity) return;
        int* tmp = new int[capacity];
        std::copy(data_, data_ + size_, tmp);
        delete[] data_;
        data_ = tmp;

        capacity_ = capacity;
    }

    void Swap(IntVector& rhs) {
        std::swap(size_, rhs.size_);
        std::swap(capacity_, rhs.capacity_);
        std::swap(data_, rhs.data_);
    }

    // для доступа типа запись
    int& operator[](size_t ind) {
        return data_[ind];
    }

    // для доступа типа чтение
    int operator[](size_t ind) const {
        return data_[ind];
    }

private:
    size_t size_;
    size_t capacity_;
    int* data_;
};


