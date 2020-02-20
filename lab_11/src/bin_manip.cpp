#include "bin_manip.h"
#include <string>
#include <cassert>

std::ostream &write_le_int32::operator()(std::ostream &out) const {
    out.write(reinterpret_cast<const char *>(&_data), sizeof(_data));
    return out;
}

std::ostream &operator<<(std::ostream &ofs, const write_le_int32 &obj) {
    return obj(ofs);
}

std::istream &read_le_int32::operator()(std::istream &in) const {
    in.read(reinterpret_cast<char *>(&_data), sizeof(_data));
    return in;
}

std::istream &operator>>(std::istream &in, const read_le_int32 &obj) {
    return obj(in);
}

std::ostream &write_bool::operator()(std::ostream &out) const {
    out.write(reinterpret_cast<const char *>(&_data), sizeof(_data));
    return out;
}

std::ostream &operator<<(std::ostream &ofs, const write_bool &obj) {
    return obj(ofs);
}

std::istream &read_bool::operator()(std::istream &in) const {
    in.read(reinterpret_cast<char *>(&_data), sizeof(_data));
    return in;
}

std::istream &operator>>(std::istream &in, const read_bool &obj) {
    return obj(in);
}

std::ostream &write_str::operator()(std::ostream &out) const {
    assert(_data.size() <= 100);
    for (char i : _data) {
        out << (unsigned char) i;
    }
    out << (unsigned char) 0;
    return out;
}

std::ostream &operator<<(std::ostream &ofs, const write_str &obj) {
    return obj(ofs);
}

std::istream &read_str::operator()(std::istream &in) const {
    unsigned char temp_char;
    _data = "";
    in >> temp_char;
    while (temp_char) {
        _data.push_back(temp_char);
        in >> temp_char;
    }
    assert(_data.size() <= 100);
    return in;
}

std::istream &operator>>(std::istream &in, const read_str &obj) {
    return obj(in);
}
