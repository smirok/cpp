#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"

class Rectangle : public Figure
{
public:
    Rectangle(int id, int x, int y, int width, int height);
    ~Rectangle() override = default;

    void print() const override;
    bool is_inside(int x, int y) const override;
    void zoom(int factor) override;

    int get_width() const;
    int get_height() const;

    void set_width(int width);
    void set_height(int height);

private:
    int width_, height_;
};

#endif //RECTANGLE_H