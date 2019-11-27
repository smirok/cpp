#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "point_list.h"

#define container_of(ptr, type, member) (type *)((char *)(ptr)-offsetof(type, member))

pointNode *getPoint(intrusiveNode *node)
{
    return container_of(node, pointNode, node);
}

int matchPoint(intrusiveNode *node, int32_t x, int32_t y)
{
    pointNode *pNode = getPoint(node);
    return pNode->x == x && pNode->y == y;
}

void deletePoint(intrusiveList *list, intrusiveNode *node)
{
    removeNode(list, node);
    free(getPoint(node));
}

void printPoint(intrusiveNode *node)
{
    pointNode *pNode = getPoint(node);
    printf("(%d, %d)", pNode->x, pNode->y);
}

void printPointSecond(intrusiveNode *node, char *format)
{
    pointNode *pNode = getPoint(node);
    printf(format, pNode->x, pNode->y);
}

void removePoint(intrusiveList *list, int32_t x, int32_t y)
{
    intrusiveNode *head = &list->head;
    intrusiveNode *node = head->next;

    while (node != head)
    {
        intrusiveNode *next = node->next;

        if (matchPoint(node, x, y))
            deletePoint(list, node);

        node = next;
    }
}

void addPoint(intrusiveList *list, int32_t x, int32_t y)
{
    pointNode *pNode = malloc(sizeof(pointNode));
    pNode->x = x;
    pNode->y = y;

    addNode(list, &pNode->node);
}

void showAllPoints(intrusiveList *list)
{
    intrusiveNode *head = &list->head;
    intrusiveNode *node = head->next;

    printf("%d: ", getLength(list));

    for (int i = 0; node != head; i++, node = node->next)
    {
        if (i)
            printf(" ");
        printPoint(node);
    }

    printf("\n");
}

void removeAllPoints(intrusiveList *list)
{
    while (list->head.next != &list->head)
        deletePoint(list, list->head.next);
}

void print(intrusiveNode *node, void *castFormat)
{
    char *format = (char *) castFormat;
    pointNode *pNode = getPoint(node);
    printf(format, pNode->x, pNode->y);
}

void count(intrusiveNode *node, void *castSum)
{
    int32_t *sum = (int32_t *)castSum;
    (void) node;
    *sum = *sum + 1;
}
