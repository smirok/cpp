#include <iostream>
#include "Circle.h"
#include <cstring>

Circle::Circle(int id, int x, int y, int radius, const char *label) :
        Figure(id, x, y), radius_(radius) {
    label_ = new char[100];
    set_label(label);
}

Circle::~Circle() {
    delete[] label_;
}

void Circle::print() const {
    std::cout << "Circle " << get_id() << ": "
              << "x = " << get_x() << " y = " << get_y()
              << " radius_ = " << get_radius() << " label_ = " << get_label() << "\n";
}

bool Circle::is_inside(int x, int y) const {
    return (
            get_sqr(abs(x - get_x())) +
            get_sqr(abs(y - get_y())) <= get_sqr(radius_)
    );
}

void Circle::zoom(int factor) {
    set_radius(radius_ * factor);
}

int Circle::get_sqr(int value) { return value * value; }

int Circle::get_radius() const { return radius_; }

char *Circle::get_label() const { return label_; }

void Circle::set_radius(int radius) {
    radius_ = radius;
}

void Circle::set_label(const char *label) {
    delete[] label_;
    label_ = new char[strlen(label) + 1];
    strcpy(label_, label);
}