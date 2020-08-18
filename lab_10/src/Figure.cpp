#include "Figure.h"

Figure::Figure(int id, int x, int y) : id_(id), x_(x), y_(y) {}

void Figure::move(int new_x, int new_y) {
    set_x(new_x);
    set_y(new_y);
}

void Figure::set_id(int id) {
    id_ = id;
}

void Figure::set_x(int x) {
    x_ = x;
}

void Figure::set_y(int y) {
    y_ = y;
}

int Figure::get_id() const {
    return id_;
}

int Figure::get_x() const {
    return x_;
}

int Figure::get_y() const {
    return y_;
}