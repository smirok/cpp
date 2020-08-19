#include <iostream>
#include <cstring>
#include <vector>

#include "my_vector.h"

#define DO_CHECK(EXPR) check(EXPR, __FILE__, __LINE__)

void check(bool expr, const char *filename, size_t lineNum) {
    if (!expr) {
        std::cout << "Function failed :" << " in "
                  << filename << " in "
                  << lineNum << " line\n";
    }
}

namespace product {

    class Product {
    public:
        Product() noexcept: name_(new char[1]), quantity_(0), price_(0) {
            name_[0] = 0;
        }

        Product(const char *name, int quantity, double price) :
                name_(new char[strlen(name) + 1]), quantity_(quantity), price_(price) {
            strcpy(name_, name);
        }

        Product(const Product &other) :
                name_(new char[strlen(other.name_) + 1]), quantity_(other.quantity_), price_(other.price_) {
            strcpy(name_, other.name_);
        }

        Product &operator=(const Product &other) {
            /*Product temp(other);
            swap(temp);*/
            // Почему copy-swap trick не работает ? Не понимаю :(
            if (this != &other) {
                name_ = new char[strlen(other.name_) + 1];
                strcpy(name_, other.name_);
                price_ = other.price_;
                quantity_ = other.quantity_;
            }
            return *this;
        }

        ~Product() {
            delete[] name_;
        }

        char *getName() const {
            return name_;
        }

        int getQuantity() const {
            return quantity_;
        }

        double getPrice() const {
            return price_;
        }

        void swap(Product &other) {
            std::swap(price_, other.price_);
            std::swap(quantity_, other.quantity_);
            std::swap(name_, other.name_);
        }

        bool operator==(const Product &p) const {
            int flag = 0;
            if (strcmp(p.name_, name_) == 0)
                flag = 1;
            return (flag && p.price_ == price_ && p.quantity_ == quantity_);
        }

    private:
        char *name_; // Указатель владеет C-style строкой, на которую указывает.
        int quantity_;
        double price_;
    };

    void print(const my_vector::my_vector<Product> &v) {
        std::cout << v << std::endl;
    }

    std::ostream &operator<<(std::ostream &os, const Product &p) {
        os << p.getName() << " ";
        os << p.getQuantity() << " ";
        os << p.getPrice();
        return os;
    }

}  // namespace product

template<typename T>
void test_my_vector(T fst, T snd) {

    my_vector::my_vector<T> v;

    DO_CHECK(v.size() == 0);
    DO_CHECK(v.capacity() == 1);
    DO_CHECK(v.empty());

    size_t old_size = v.size();
    v.reserve(5);
    DO_CHECK(v.capacity() >= 5);
    DO_CHECK(v.size() == old_size);

    v.push_back(fst);
    DO_CHECK(v[0] == fst);

    v.push_back(snd);
    DO_CHECK(v[1] == snd);

    old_size = v.size();

    v.push_back(fst);
    v.pop_back();
    DO_CHECK(v.size() == old_size);

    my_vector::my_vector<T> v2(v);
    DO_CHECK(v2[0] == v[0]);
    DO_CHECK(v2[1] == v[1]);
    DO_CHECK(v2.size() == v.size());
    DO_CHECK(v2.capacity() == v.capacity());

    my_vector::my_vector<T> v3;
    v3 = v;
    DO_CHECK(v3[0] == v[0]);
    DO_CHECK(v3[1] == v[1]);
    DO_CHECK(v3.size() == v.size());
    DO_CHECK(v3.capacity() == v.capacity());

    DO_CHECK(v.end() == v.begin() + v.size());

    const my_vector::my_vector<T> v4(5);
    T elem = v4[0];
    DO_CHECK(elem == v4[0]);

    v3.clear();
    DO_CHECK(v3.empty());

    my_vector::my_vector<T> vv;
    for (int i = 0; i < 1000; i++)
        vv.push_back(fst);

    DO_CHECK(vv.size() == 1000);
}

template<typename T>
void test_my_vector_default_constructible(T fst, T snd) {
    my_vector::my_vector<T> v;

    v.resize(2);
    v[0] = fst;
    v[1] = snd;
    DO_CHECK(v[0] == fst);
    DO_CHECK(v[1] == snd);
    DO_CHECK(v.capacity() >= v.size());
    DO_CHECK(!v.empty());
    v.resize(5);
    v[2] = fst;
    v[3] = fst;
    v[4] = fst;
    v.resize(3);

    my_vector::my_vector<T> v2(10);
    DO_CHECK(v2[0] == 0);

    my_vector::my_vector<T> v4(std::move(my_vector::my_vector<T>(6)));
    DO_CHECK(v4.size() == 6);

    my_vector::my_vector<T> v5;
    v5 = std::move(v4);
    DO_CHECK(v5.size() == 6);
}

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector_default_constructible<int>(5, 10);

    test_my_vector<product::Product>(product::Product("asdf", 4, 12.0),
                                     product::Product("qwe", -1, 7.5));
}