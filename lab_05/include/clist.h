#ifndef CLIST_H_
#define CLIST_H_

#include <stdint.h>

typedef struct intrusiveNode
{
    struct intrusiveNode *next;
    struct intrusiveNode *prev;
} intrusiveNode;

typedef struct intrusiveList
{
    intrusiveNode head;
} intrusiveList;

void initList(intrusiveList *);

void addNode(intrusiveList *, intrusiveNode *);

// contract: node != &list->head
void removeNode(intrusiveList *, intrusiveNode *);

int getLength(intrusiveList *);

void apply(intrusiveList *list, void (*op)(intrusiveNode *node, void *data), void *data);

#endif
