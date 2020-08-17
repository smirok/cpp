#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "point_list.h"

#define container_of(ptr, type, member) (type *)((char *)(ptr)-offsetof(type, member))

int match_point(intrusive_node *node, int32_t x, int32_t y) {
    point_node *p_node = get_point(node);
    return p_node->x == x && p_node->y == y;
}

void delete_point(intrusive_list *list, intrusive_node *node) {
    remove_node(list, node);
    free(get_point(node));
}

void remove_point(intrusive_list *list, int32_t x, int32_t y) {
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;

    while (node != head) {
        intrusive_node *next = node->next;

        if (match_point(node, x, y))
            delete_point(list, node);

        node = next;
    }
}

void add_point(intrusive_list *list, int32_t x, int32_t y) {
    point_node *p_node = malloc(sizeof(point_node));
    p_node->x = x;
    p_node->y = y;

    add_node(list, &p_node->node);
}

void remove_all_points(intrusive_list *list) {
    while (list->head.next != &list->head)
        delete_point(list, list->head.next);
}

void print(intrusive_node *node, void *format) {
    point_node *p_node = get_point(node);
    printf((char *) format, p_node->x, p_node->y);
}

void count(intrusive_node *node, void *cast_sum) {
    int32_t *sum = (int32_t *) cast_sum;
    (void) node;
    *sum = *sum + 1;
}

point_node *get_point(intrusive_node *node) {
    return container_of(node, point_node, node);
}