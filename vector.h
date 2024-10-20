#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t size;

    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity) return;

        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]);
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    Vector() : data(nullptr), capacity(0), size(0) {}

    Vector(std::initializer_list<T> init_list) : Vector() {
        reserve(init_list.size());
        for (const auto& elem : init_list) {
            push_back(elem);
        }
    }

    Vector(const Vector& other) : Vector() {
        reserve(other.capacity);
        for (size_t i = 0; i < other.size; ++i) {
            push_back(other.data[i]);
        }
    }

    Vector(Vector&& other) noexcept: data(other.data), capacity(other.capacity), size(other.size) {
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            capacity = 0;
            size = 0;
            reserve(other.capacity);
            for (size_t i = 0; i < other.size; ++i) {
                push_back(other.data[i]);
            }
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            size = other.size;

            other.data = nullptr;
            other.capacity = 0;
            other.size = 0;
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    void push_back(T&& value) {
        if (size == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = std::move(value);
    }

    void pop_back() {
        if (size > 0) {
            --size;
        }
    }

    T& at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    size_t get_size() const {
        return size;
    }

    T* begin() { return data; }
    T* end() { return data + size; }

    const T* begin() const { return data; }
    const T* end() const { return data + size; }

    const T* cbegin() const { return data; }
    const T* cend() const { return data + size; }

    bool operator==(const Vector& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    auto begin_range() const { return data; }
    auto end_range() const { return data + size; }
};

#endif
