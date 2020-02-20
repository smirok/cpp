#ifndef LAB_11_BIN_MANIP_H
#define LAB_11_BIN_MANIP_H

#include <iostream>
#include <cstdint>
#include <cstring>
#include <utility>

class write_le_int32 {
public:
    explicit write_le_int32(int data) : _data(data) {};

    std::ostream &operator()(std::ostream &out) const;

    friend std::ostream &operator<<(std::ostream &ofs, const write_le_int32 &obj);

private:
    int32_t _data;
};

class read_le_int32 {
public:
    explicit read_le_int32(int32_t &data) : _data(data) {};

    std::istream &operator()(std::istream &in) const;

    friend std::istream &operator>>(std::istream &in, const read_le_int32 &obj);

private:
    int32_t &_data;
};

class write_bool {
public:
    explicit write_bool(bool data) : _data(data) {};

    std::ostream &operator()(std::ostream &out) const;

    friend std::ostream &operator<<(std::ostream &ofs, const write_bool &obj);

private:
    bool _data;
};

class read_bool {
public:
    explicit read_bool(bool &data) : _data(data) {};

    std::istream &operator()(std::istream &in) const;

    friend std::istream &operator>>(std::istream &in, const read_bool &obj);

private:
    bool &_data;
};

class write_str {
public:
    explicit write_str(std::string data) : _data(std::move(data)) {};

    std::ostream &operator()(std::ostream &out) const;

    friend std::ostream &operator<<(std::ostream &ofs, const write_str &obj);

private:
    std::string _data;
};

class read_str {
public:
    explicit read_str(std::string &data) : _data(data) {};

    std::istream &operator()(std::istream &in) const;

    friend std::istream &operator>>(std::istream &in, const read_str &obj);

private:
    std::string &_data;
};

#endif //LAB_11_BIN_MANIP_H
