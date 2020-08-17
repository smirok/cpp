#ifndef CLIST_H_
#define CLIST_H_

#include <stdint.h>

typedef struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
} intrusive_node;

typedef struct intrusive_list {
    intrusive_node head;
} intrusive_list;

void init_list(intrusive_list *);

void add_node(intrusive_list *, intrusive_node *);

// contract: node != &list->head
void remove_node(intrusive_list *, intrusive_node *);

void apply(intrusive_list *list, void (*op)(intrusive_node *node, void *data), void *data);

#endif
