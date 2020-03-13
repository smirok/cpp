#ifndef LAB_12_MY_VECTOR_IMPL_H
#define LAB_12_MY_VECTOR_IMPL_H

#include <memory>
#include "my_vector.h"


namespace my_vector {

    template<typename T, typename Allocator>
    my_vector<T, Allocator>::my_vector() noexcept {}

    template<typename T, typename Allocator>
    my_vector<T, Allocator>::my_vector(std::size_t n) : v(n) {
        using traits = std::allocator_traits<Allocator>;
        traits::deallocate(v.alloc, v.array_, v.capacity_);
        v.array_ = traits::allocate(v.alloc, v.capacity_);
        for (; v.size_ < n; v.size_++)
            traits::construct(v.alloc, v.array_ + v.size_, std::move(T()));
    }

    template<typename T, typename Allocator>
    my_vector<T, Allocator>::my_vector(const my_vector &other) : v(other.v.capacity_) {
        for (; v.size_ < other.v.size_; v.size_++) {
            v.array_[v.size_] = other.v.array_[v.size_];
        }
    }

    template<typename T, typename Allocator>
    my_vector <T, Allocator> &my_vector<T, Allocator>::operator=(const my_vector <T, Allocator> &other) {
        vector_impl temp(other.v.capacity_);
        temp.copy(other.v);
        v.swap(temp);
        return *this;
    }

    template<typename T, typename Allocator>
    my_vector<T, Allocator>::~my_vector() noexcept {}

    template<typename T, typename Allocator>
    my_vector<T, Allocator>::my_vector(my_vector &&other) noexcept {
        v.swap(other.v);
    }

    template<typename T, typename Allocator>
    my_vector <T, Allocator> &my_vector<T, Allocator>::operator=(my_vector <T, Allocator> &&other) noexcept {
        v.swap(other.v);
        return *this;
    }

    template<typename T, typename Allocator>
    std::size_t my_vector<T, Allocator>::size() const noexcept {
        return v.size_;
    }

    template<typename T, typename Allocator>
    std::size_t my_vector<T, Allocator>::capacity() const noexcept {
        return v.capacity_;
    }

    template<typename T, typename Allocator>
    bool my_vector<T, Allocator>::empty() const noexcept {
        return !v.size_;
    }

    template<typename T, typename Allocator>
    void my_vector<T, Allocator>::resize(std::size_t n) {
        using traits = std::allocator_traits<Allocator>;
        if (n < v.size_) {
            for (size_t i = v.size_; i > n; i--)
                traits::destroy(v.alloc, v.array_ + i - 1);
        }
        reserve(n);
        for (size_t j = v.size_; j < n; j++)
            traits::construct(v.alloc, v.array_ + j, std::move(T()));
        v.size_ = n;
    }

    template<typename T, typename Allocator>
    void my_vector<T, Allocator>::reserve(std::size_t n) {
        using traits = std::allocator_traits<Allocator>;
        if (n > v.capacity_) {
            vector_impl temp(n);
            for (; temp.size_ < v.size_; temp.size_++)
                traits::construct(temp.alloc, temp.array_ + temp.size_, v.array_[temp.size_]);
            v.swap(temp);
        }
    }

    template<typename T, typename Allocator>
    T &my_vector<T, Allocator>::operator[](std::size_t index) {
        return v.array_[index];
    }

    template<typename T, typename Allocator>
    const T &my_vector<T, Allocator>::operator[](std::size_t index) const {
        return v.array_[index];
    }

    template<typename T, typename Allocator>
    void my_vector<T, Allocator>::push_back(const T &value) {
        push_back(T(value));
    }

    template<typename T, typename Allocator>
    void my_vector<T, Allocator>::push_back(T &&value) {
        using traits = std::allocator_traits<Allocator>;
        reserve(v.size_ + 1);
        traits::construct(v.alloc, v.array_ + v.size_++, value);
    }

    template<typename T, typename Allocator>
    void my_vector<T, Allocator>::pop_back() {
        using traits = std::allocator_traits<Allocator>;
        traits::destroy(v.alloc, v.array_ + v.size_ - 1);
        v.size_--;
    }

    template<typename T, typename Allocator>
    void my_vector<T, Allocator>::clear() {
        using traits = std::allocator_traits<Allocator>;
        for (size_t i = v.size_; i > 0; i--)
            traits::destroy(v.alloc, v.array_ + i - 1);
        v.size_ = 0;
    }

    template<typename T, typename Allocator>
    T *my_vector<T, Allocator>::begin() {
        return v.array_;
    }

    template<typename T, typename Allocator>
    T *my_vector<T, Allocator>::end() {
        return v.array_ + v.size_;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const my_vector <T> &vect) {
        for (std::size_t i = 0; i < vect.size(); i++) {
            os << vect[i];
            if (i != vect.size() - 1)
                os << " ";
        }
        return os;
    }

    template<typename T, typename Allocator>
    size_t my_vector<T, Allocator>::round_up_2(size_t size) {
        size_t result = 1;
        while (result < size)
            result <<= 1;
        return result;
    }

    template<typename T, typename Allocator>
    my_vector<T, Allocator>::vector_impl::vector_impl(size_t capacity) {
        using traits = std::allocator_traits<Allocator>;
        capacity_ = round_up_2(capacity);
        array_ = traits::allocate(alloc, capacity_);
    }

    template<typename T, typename Allocator>
    my_vector<T, Allocator>::vector_impl::~vector_impl() {
        using traits = std::allocator_traits<Allocator>;
        for (; size_ > 0; size_--)
            traits::destroy(alloc, array_ + size_ - 1);
        traits::deallocate(alloc, array_, capacity_);
    }

    template<typename T, typename Allocator>
    void my_vector<T, Allocator>::vector_impl::swap(my_vector::vector_impl &other) {
        std::swap(array_, other.array_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    template<typename T, typename Allocator>
    void my_vector<T, Allocator>::vector_impl::copy(const my_vector::vector_impl &other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        using traits = std::allocator_traits<Allocator>;
        for (size_t i = 0; i < other.size_; i++)
            traits::construct(alloc, array_ + i, other.array_[i]);
    }
}

#endif //LAB_12_MY_VECTOR_IMPL_H