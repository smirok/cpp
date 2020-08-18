#ifndef SCHEME_H
#define SCHEME_H

#include "Figure.h"

class Scheme
{
public:
    explicit Scheme(int capacity);
    ~Scheme();

    void push_back_figure(Figure *fg);
    void remove_figure(int id); // элементы смещаются влево

    void print_all_figures();
    void zoom_figure(int id, int factor);
    Figure *is_inside_figure(int x, int y); // если внутри нескольких фигур, то возвращается любая из них
    void move(int id, int new_x, int new_y);

    Figure* find_by_id(int id);

private:
    int size;
    int capacity;
    Figure **figures_; // размер массива задается в конструкторе и больше не растет
};

#endif //SCHEME_H