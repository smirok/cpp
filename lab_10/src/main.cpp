#include <cstdio>

#include "Scheme.h"
#include "Rectangle.h"
#include "Circle.h"

int main() {
    // all setters for simple change figure parameters if we need 
    Scheme scheme(10);

    scheme.push_back_figure(new Rectangle(1, 5, 5, 10, 10));
    scheme.push_back_figure(new Circle(2, 3, 3, 3, "very nice circle"));

    scheme.print_all_figures();

    Figure *found = scheme.is_inside_figure(5, 5);
    if (found != nullptr) {
        found->print();
    } else {
        printf("not found\n");
    }

    scheme.zoom_figure(1, 2);
    scheme.print_all_figures();
    scheme.remove_figure(1);
    scheme.print_all_figures();

    return 0;
}
