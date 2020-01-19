#include "Figure.h"

Figure::Figure(int id, int x, int y)
{
    set_id(id);
    set_x(x);
    set_y(y);
}

void Figure::move(int new_x, int new_y)
{
    set_x(new_x);
    set_y(new_y);
}

void Figure::set_id(int id_)
{
    this->id = id_;
}

void Figure::set_x(int x_)
{
    this->x = x_;
}

void Figure::set_y(int y_)
{
    this->y = y_;
}

int Figure::get_id() const
{
    return id;
}

int Figure::get_x() const
{
    return x;
}

int Figure::get_y() const
{
    return y;
}