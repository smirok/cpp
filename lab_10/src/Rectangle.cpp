#include <iostream>
#include "Rectangle.h"

Rectangle::Rectangle(int id, int x, int y, int width, int height)
{
    set_id(id);
    set_x(x);
    set_y(y);
    set_width(width);
    set_height(height);
}

void Rectangle::print() const
{
    std::cout << "Rectangle " << get_id() << ": "
              << "x = " << get_x() << " y = " << get_y()
              << " width = " << get_width() << " height = " << get_height() << "\n";
}

bool Rectangle::is_inside(int x, int y) const
{
    return abs(x - get_x()) <= (float)get_width() / 2 && abs(y - get_y()) <= (float)get_height() / 2;
}

void Rectangle::zoom(int factor)
{
    set_width(width * factor);
    set_height(height * factor);
}

int Rectangle::get_height() const { return height; }

int Rectangle::get_width() const { return width; }

void Rectangle::set_height(int height_)
{
    this->height = height_;
}

void Rectangle::set_width(int width_)
{
    this->width = width_;
}
