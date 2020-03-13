#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <climits>

namespace lab_13 {

    template<typename T, std::size_t N>
    class my_array {
    public:
        const T &at(std::size_t index) const;

        T &at(std::size_t index);

        const T &operator[](std::size_t index) const;

        T &operator[](std::size_t index);

        constexpr bool empty() const;

        constexpr std::size_t size() const;

        void fill(const T &val);

    private:
        T arr[N];
    };

    template<typename T, std::size_t N>
    const T &my_array<T, N>::at(std::size_t index) const {
        if (index >= N)
            throw std::out_of_range("");
        return arr[index];
    }

    template<typename T, std::size_t N>
    T &my_array<T, N>::at(std::size_t index) {
        if (index >= N)
            throw std::out_of_range("");
        return arr[index];
    }

    template<typename T, std::size_t N>
    const T &my_array<T, N>::operator[](std::size_t index) const {
        return arr[index];
    }

    template<typename T, std::size_t N>
    T &my_array<T, N>::operator[](std::size_t index) {
        return arr[index];
    }


    template<typename T, std::size_t N>
    constexpr bool my_array<T, N>::empty() const {
        return !N;
    }

    template<typename T, std::size_t N>
    constexpr std::size_t my_array<T, N>::size() const {
        return N;
    }

    template<typename T, std::size_t N>
    void my_array<T, N>::fill(const T &val) {
        for (std::size_t i = 0; i < N; i++) {
            arr[i] = val;
        }
    }

}  // namespace lab_13

namespace lab_13 {
    template<std::size_t N>
    class my_array<bool, N> {
    private:
        class proxy {
        public:
            proxy(unsigned char &data, int bit_num) : data_(data), bit_num_(bit_num) {};

            operator bool() const noexcept {
                return data_ & (1 << bit_num_);
            }

            proxy operator=(bool b) noexcept {
                data_ &= ~(1 << bit_num_);
                data_ |= (b << bit_num_);
                return *this;
            }

            proxy operator=(proxy &source) noexcept {
                return *this = source;
            }

        private:
            unsigned char &data_;
            int8_t bit_num_;
        };

        unsigned char arr[(N / CHAR_BIT) + 1];
    public:
        bool at(std::size_t index) const {
            if (index >= N)
                throw std::out_of_range("");
            return arr[index / CHAR_BIT] & (1 << (index % CHAR_BIT));
        }

        proxy at(std::size_t index) {
            if (index >= N)
                throw std::out_of_range("");
            return proxy(arr[index / CHAR_BIT], index % CHAR_BIT);
        }

        bool operator[](std::size_t index) const {
            return arr[index / CHAR_BIT] & (1 << (index % CHAR_BIT));
        }

        proxy operator[](std::size_t index) {
            return proxy(arr[index / CHAR_BIT], index % CHAR_BIT);
        }

        constexpr bool empty() const {
            return !N;
        }

        constexpr std::size_t size() const {
            return N;
        }

        void fill(bool val) {
            for (std::size_t i = 0; i < N; i++) {
                arr[i / CHAR_BIT] &= ~(1 << (i % CHAR_BIT));
                arr[i / CHAR_BIT] |= (val << (i % CHAR_BIT));
            }
        }
    };
}

#endif  // MY_ARRAY_H_