#include <iostream>
#include "Circle.h"
#include <cstring>

Circle::Circle(int id, int x, int y, int radius, const char *label)
{
    set_id(id);
    set_x(x);
    set_y(y);
    set_radius(radius);
    this->label = new char[10];
    set_label(label);
}

Circle::~Circle()
{
    delete[] this->label;
}

void Circle::print() const
{
    std::cout << "Circle " << get_id() << ": "
              << "x = " << get_x() << " y = " << get_y()
              << " radius = " << get_radius() << " label = " << get_label() << "\n";
}

bool Circle::is_inside(int x, int y) const
{
    return (get_sqr(abs(x - get_x())) + get_sqr(abs(y - get_y())) <= get_sqr(radius));
}

void Circle::zoom(int factor)
{
    set_radius(radius * factor);
}

int Circle::get_sqr(int value) const { return value * value; }

int Circle::get_radius() const { return radius; }

char *Circle::get_label() const { return label; }

void Circle::set_radius(int radius_)
{
    this->radius = radius_;
}

void Circle::set_label(const char *label_)
{
    delete [] this->label;
    this->label = new char[strlen(label_) + 1];
    strcpy(this->label, label_);
}
