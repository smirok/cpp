#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <iostream>
#include <memory>

namespace {
    const int INIT_CAPACITY = 1;
    const int INIT_SIZE = 0;
}

namespace my_vector {
    template<typename T, typename Allocator = std::allocator<T>>
    class my_vector {
    public:
        my_vector() noexcept;
        explicit my_vector(std::size_t n);
        my_vector(const my_vector &other);
        my_vector &operator=(const my_vector &other);
        ~my_vector() noexcept;

        my_vector(my_vector &&other) noexcept;
        my_vector &operator=(my_vector &&other) noexcept;

        size_t size() const noexcept;
        size_t capacity() const noexcept;
        bool empty() const noexcept;

        void resize(std::size_t n);
        void reserve(std::size_t n);

        T &operator[](std::size_t index);
        const T &operator[](std::size_t index) const;

        void push_back(const T &value);
        void push_back(T &&value);
        void pop_back();
        void clear();

        T *begin();
        T *end();

    private:
        struct vector_impl {
            size_t size_ = INIT_SIZE;
            size_t capacity_;
            T *array_ = nullptr;
            Allocator alloc;

            explicit vector_impl(size_t capacity = INIT_CAPACITY);
            vector_impl(const vector_impl &) = delete;
            vector_impl &operator=(const vector_impl &) = delete;
            ~vector_impl();

            void swap(vector_impl &other);
            void copy(const vector_impl &other) ;
        };

        vector_impl v;

        static size_t round_up_2(size_t size);
    };

}

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_