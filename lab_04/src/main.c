#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "mergesort.h"

int int_comp(const void *left, const void *right)
{
    return *((const int *)left) - *((const int *)right);
}

int char_comp(const void *left, const void *right)
{
    return *((const char *)left) - *((const char *)right);
}

int str_comp(const void *left, const void *right)
{
    return strcmp(*(char **)left, *(char **)right);
}

void mergesort_int(int argc, char *argv[])
{
    int *array = (int *)malloc((argc) * sizeof(int));
    for (int i = 2; i < argc; i++)
    {
        array[i - 2] = atoi(argv[i]);
    }
    mergesort(array, argc - 2, sizeof(int), int_comp);
    for (int i = 0; i < argc - 2; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    free(array);
}

void mergesort_str(int argc, char *argv[])
{
    char **array = (char **)malloc((argc - 1) * sizeof(char *));
    for (int i = 2; i < argc; i++)
    {
        array[i - 2] = argv[i];
    }
    mergesort(array, argc - 2, sizeof(char *), str_comp);
    for (int i = 0; i < argc - 2; i++)
    {
        printf("%s ", array[i]);
    }
    printf("\n");
    free(array);
}

void mergesort_char(int argc, char *argv[])
{
    char *array = (char *)malloc((argc - 1) * sizeof(char));
    for (int i = 2; i < argc; i++)
    {
        array[i - 2] = argv[i][0];
    }
    mergesort(array, argc - 2, sizeof(char), char_comp);
    for (int i = 0; i < argc - 2; i++)
    {
        printf("%c ", array[i]);
    }
    printf("\n");
    free(array);
}

int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "int") == 0)
        mergesort_int(argc, argv);
    else if (strcmp(argv[1], "str") == 0)
        mergesort_str(argc, argv);
    else if (strcmp(argv[1], "char") == 0)
        mergesort_char(argc, argv);
    return 0;
}
