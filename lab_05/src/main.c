#include "point_list.h"
#include "clist.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

const int TWENTY_FOUR_DEGREE = 1 << 24;

const int MAX_VALUE = 5000000;

void load_text(intrusive_list *list, char *file_name) {
    int x, y;
    FILE *fin = fopen(file_name, "r");
    assert(fin);
    while (fscanf(fin, "%d %d", &x, &y) == 2) {
        add_point(list, x, y);
    }
    fclose(fin);
}

void load_bin(intrusive_list *list, char *file_name) {
    FILE *fin = fopen(file_name, "rb");
    assert(fin);
    uint8_t translator_x[3];
    uint8_t translator_y[3];
    while (fread(translator_x, 3, 1, fin) != 0) {
        fread(translator_y, 3, 1, fin);
        int32_t curr_x = 0;
        int32_t curr_y = 0;
        for (int i = 0; i < 3; i++) {
            curr_x += translator_x[i] * (1 << 8 * i);
            curr_y += translator_y[i] * (1 << 8 * i);
        }
        if (curr_x > MAX_VALUE)
            curr_x = curr_x - TWENTY_FOUR_DEGREE;
        if (curr_y > MAX_VALUE)
            curr_y = curr_y - TWENTY_FOUR_DEGREE;
        printf("%d ", curr_x);
        add_point(list, curr_x, curr_y);
    }
    fclose(fin);
}

void save_text(intrusive_list *list, char *file_name) {
    FILE *fout = fopen(file_name, "w");
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;
    point_node *point;
    for (; node != head; node = node->next) {
        point = get_point(node);
        int32_t x_value = point->x;
        int32_t y_value = point->y;
        fprintf(fout, "%d %d", x_value, y_value);
        fprintf(fout, "\n");
    }
    fclose(fout);
}

void save_bin(intrusive_list *list, char *file_name) {
    FILE *fout = fopen(file_name, "wb");
    assert(fout);
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;
    point_node *point;
    uint8_t translator_x[3];
    uint8_t translator_y[3];
    for (; node != head; node = node->next) {
        point = get_point(node);
        int32_t x_value = point->x;
        int32_t y_value = point->y;
        if (x_value < 0)
            x_value = x_value + TWENTY_FOUR_DEGREE;
        if (y_value < 0)
            y_value = y_value + TWENTY_FOUR_DEGREE;
        for (int i = 2; i >= 0; i--) {
            translator_x[i] = x_value / (1 << 8 * i);
            x_value -= (x_value / (1 << 8 * i)) * (1 << 8 * i);
            translator_y[i] = y_value / (1 << 8 * i);
            y_value -= (y_value / (1 << 8 * i)) * (1 << 8 * i);
        }
        fwrite(translator_x, 3, 1, fout);
        fwrite(translator_y, 3, 1, fout);
    }
    fclose(fout);
}

int main(int argc, char *argv[]) {
    if (argc < 4 || argc > 5)
        return EXIT_FAILURE;

    intrusive_list list;
    init_list(&list);

    if (strcmp(argv[1], "loadtext") == 0) {
        load_text(&list, argv[2]);
    } else if (strcmp(argv[1], "loadbin") == 0) {
        load_bin(&list, argv[2]);
    }

    if (strcmp(argv[3], "savetext") == 0) {
        save_text(&list, argv[4]);
    } else if (strcmp(argv[3], "savebin") == 0) {
        save_bin(&list, argv[4]);
    }

    if (strcmp(argv[3], "print") == 0) {
        apply(&list, print, argv[4]);
        printf("\n");
    }

    if (strcmp(argv[3], "count") == 0) {
        int32_t sum = 0;
        apply(&list, count, &sum);
        printf("%d", sum);
        printf("\n");
    }
    remove_all_points(&list);

    return 0;
}