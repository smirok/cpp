#ifndef POINT_LIST_H_
#define POINT_LIST_H_

#include "clist.h"

typedef struct pointNode
{
    int x;
    int y;
    intrusiveNode node;
} pointNode;

void removePoint(intrusiveList *list, int32_t x, int32_t y);

void addPoint(intrusiveList *list, int32_t x, int32_t y);

void showAllPoints(intrusiveList *list);

void removeAllPoints(intrusiveList *list);

void print(intrusiveNode *node, void *castFormat);

void count(intrusiveNode *node, void *castSum);

pointNode *getPoint(intrusiveNode *node);

#endif
