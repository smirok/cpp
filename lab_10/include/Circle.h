#pragma once

#include "Figure.h"

class Circle : public Figure
{
public:
    Circle(int id, int x, int y, int radius, const char *label);
    ~Circle() override;

    void print() const override;
    bool is_inside(int x, int y) const override;
    void zoom(int factor) override;

    int get_radius() const;
    char *get_label() const;

    void set_radius(int radius);
    void set_label(const char *label);

    int get_sqr(int value) const;

private:
    int radius;
    char *label;
};