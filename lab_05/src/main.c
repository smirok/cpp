#include "point_list.h"
#include "clist.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

const int TWENTY_FOUR_DEGREE = 1 << 24;

const int MAX_VALUE = 5000000;

void loadText(intrusiveList *list, char *fileName)
{
    int xValue, yValue;
    FILE *fin = fopen(fileName, "r");
    assert(fin);
    while (fscanf(fin, "%d %d", &xValue, &yValue) == 2)
    {
        addPoint(list, xValue, yValue);
    }
    fclose(fin);
}

void loadBin(intrusiveList *list, char *fileName)
{
    FILE *fin = fopen(fileName, "rb");
    assert(fin);
    uint8_t translatorX[3];
    uint8_t translatorY[3];
    while (fread(translatorX, 3, 1, fin) != 0)
    {
        fread(translatorY, 3, 1, fin);
        int32_t currXValue = 0;
        int32_t currYValue = 0;
        for (int i = 0; i < 3; i++)
        {
            currXValue += translatorX[i] * (1 << 8 * i);
            currYValue += translatorY[i] * (1 << 8 * i);
        }
        if (currXValue > MAX_VALUE)
            currXValue = currXValue - TWENTY_FOUR_DEGREE;
        if (currYValue > MAX_VALUE)
            currYValue = currYValue - TWENTY_FOUR_DEGREE;
        addPoint(list, currXValue, currYValue);
    }
    fclose(fin);
}

void saveText(intrusiveList *list, char *fileName)
{
    FILE *fout = fopen(fileName, "w");
    intrusiveNode *head = &list->head;
    intrusiveNode *node = head->next;
    pointNode *point;
    for (; node != head; node = node->next)
    {
        point = getPoint(node);
        int32_t xValue = point->x;
        int32_t yValue = point->y;
        fprintf(fout, "%d %d", xValue, yValue);
        fprintf(fout, "\n");
    }
    fclose(fout);
}

void saveBin(intrusiveList *list, char *fileName)
{
    FILE *fout = fopen(fileName, "wb");
    assert(fout);
    intrusiveNode *head = &list->head;
    intrusiveNode *node = head->next;
    pointNode *point;
    uint8_t translatorX[3];
    uint8_t translatorY[3];
    for (; node != head; node = node->next)
    {
        point = getPoint(node);
        int32_t xValue = point->x;
        int32_t yValue = point->y;
        if (xValue < 0)
            xValue = xValue + TWENTY_FOUR_DEGREE;
        if (yValue < 0)
            yValue = yValue + TWENTY_FOUR_DEGREE;
        for (int i = 2; i >= 0; i--)
        {
            translatorX[i] = xValue / (1 << 8 * i);
            xValue -= (xValue / (1 << 8 * i)) * (1 << 8 * i);
            translatorY[i] = yValue / (1 << 8 * i);
            yValue -= (yValue / (1 << 8 * i)) * (1 << 8 * i);
        }
        fwrite(translatorX, 3, 1, fout);
        fwrite(translatorY, 3, 1, fout);
    }
    fclose(fout);
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    return EXIT_FAILURE;
    intrusiveList list;
    initList(&list);

    if (strcmp(argv[1], "loadtext") == 0)
    {
        loadText(&list, argv[2]);
    }
    else if (strcmp(argv[1], "loadbin") == 0)
    {
        loadBin(&list, argv[2]);
    }

    if (strcmp(argv[3], "savetext") == 0)
    {
        saveText(&list, argv[4]);
    }
    else if (strcmp(argv[3], "savebin") == 0)
    {
        saveBin(&list, argv[4]);
    }

    if (strcmp(argv[3], "print") == 0)
    {
        apply(&list, print, argv[4]);
        printf("\n");
    }

    if (strcmp(argv[3], "count") == 0)
    {
        int32_t sum = 0;
        apply(&list, count, &sum);
        printf("%d", sum);
        printf("\n");
    }
    removeAllPoints(&list);

    return 0;
}