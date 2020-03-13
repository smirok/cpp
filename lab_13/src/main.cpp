#include <iostream>

#include "my_array.h"
#include <cstddef>
#include <array>

#define DO_CHECK(EXPR) check(EXPR, __FILE__, __LINE__)

void check(bool expr, const char *filename, size_t lineNum) {
    if (!expr) {
        std::cout << "Function failed :" << " in "
                  << filename << " in "
                  << lineNum << " line\n";
    }
}

using lab_13::my_array;

template<typename T, std::size_t N>
void test_core() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.empty();
    ca.empty();
    a.size();
    ca.size();

    a.at(0);
    ca.at(0);
    a[0];
    ca[0];
    (void)static_cast<const T &>(a[0]);
    (void)static_cast<const T &>(ca[0]);
}

template<typename T, std::size_t N>
void test_assign() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.fill(T());

    a[0] = T();
    a[0] = a[0];
    a[0] = ca[0];
}

template <typename T, std::size_t N>
void test_all(){
    lab_13::my_array<T,N> ar{};
    DO_CHECK(!ar.empty());
    DO_CHECK(ar.size());

    for (std::size_t i = 0; i < N; i++) {
        ar[i] = i;
        DO_CHECK(ar[i] == (int)i);
    }

    ar.fill(10);
    for (std::size_t i = 0; i < N; i++)
        DO_CHECK(ar[i] == 10);
}

class NonCopyable {
public:
    NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable);
};

void test_bool(){
    lab_13::my_array<bool,10> ar{};
    DO_CHECK(!ar.empty());
    DO_CHECK(ar.size());

    for (int i = 0; i < 10; i++) {
        ar[i] = true;
        DO_CHECK(ar[i] == true);
    }

    ar.fill(false);
    for (int i = 0; i < 10; i++)
        DO_CHECK(ar[i] == false);

    ar[8] = true;
    ar[3] = ar[8];
    DO_CHECK(ar[3] == true);

    bool x = ar[8];
    DO_CHECK(x);
}

int main() {
    test_core<int, 10>();
    test_core<bool, 10>();
    test_core<NonCopyable, 10>();

    test_assign<int, 10>();
    test_assign<bool, 10>();

    test_all<int,10>();
    test_bool();
}