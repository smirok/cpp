#include "clist.h"
#include <stdio.h>

void initList(intrusiveList *list) {
    intrusiveNode *head = &list->head;
    head->next = head;
    head->prev = head;
}

void addNode(intrusiveList *list, intrusiveNode *node) {
    intrusiveNode *last = list->head.prev;
    intrusiveNode *head = &list->head;

    node->next = head;
    node->prev = last;

    head->prev = node;
    last->next = node;
}

// contract: node != &list->head
void removeNode(intrusiveList *list, intrusiveNode *node) {
    (void) list;
    intrusiveNode *prev = node->prev;
    intrusiveNode *next = node->next;

    prev->next = next;
    next->prev = prev;
}

int getLength(intrusiveList *list) {
    int length = 0;
    intrusiveNode *head = &list->head;
    intrusiveNode *node = head->next;

    for (; node != head; node = node->next)
        ++length;

    return length;
}

void apply(intrusiveList *list, void (*op)(intrusiveNode *node, void *data), void *data){
    intrusiveNode *head = &list->head;
    intrusiveNode *node = head->next;
    for (; node != head;node = node->next){
        op(node, data);// op
    }
    //printf("\n");
}
