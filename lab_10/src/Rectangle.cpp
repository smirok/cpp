#include <iostream>
#include "Rectangle.h"

Rectangle::Rectangle(int id, int x, int y, int width, int height) :
        Figure(id, x, y), width_(width), height_(height) {}

void Rectangle::print() const {
    std::cout << "Rectangle " << get_id() << ": "
              << "x = " << get_x() << " y = " << get_y()
              << " width_ = " << get_width() << " height_ = " << get_height() << "\n";
}

bool Rectangle::is_inside(int x, int y) const {
    return 2 * abs(x - get_x()) <= get_width() &&
           2 * abs(y - get_y()) <= get_height();
}

void Rectangle::zoom(int factor) {
    set_width(width_ * factor);
    set_height(height_ * factor);
}

int Rectangle::get_height() const { return height_; }

int Rectangle::get_width() const { return width_; }

void Rectangle::set_height(int height) {
    height_ = height;
}

void Rectangle::set_width(int width) {
    width_ = width;
}