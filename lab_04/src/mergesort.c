#include "mergesort.h"
#include <stdio.h>
#include <stdlib.h>

void merge(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *))
{
    char *middle = (char *)array + (elements / 2) * element_size; // Берем середину
    char *right = (char *)array + elements * element_size;
    // выделяем память под формируемую последовательность
    char *buffer = (char *)malloc(elements * element_size);
    char *IteratorLeft = array;
    char *IteratorRight = middle;
    while ((char *)IteratorLeft < (char *)middle && (char *)IteratorRight < (char *)right)
    {
        if (comparator(IteratorLeft, IteratorRight) < 0)
        {
            memcpy(buffer, IteratorLeft, element_size);
            IteratorLeft += element_size;
        }
        else
        {
            memcpy(buffer, IteratorRight, element_size);
            IteratorRight += element_size;
        }
        buffer += element_size;
    }
    while ((char *)IteratorLeft < (char *)middle)
    {
        memcpy(buffer, IteratorLeft, element_size);
        IteratorLeft += element_size;
        buffer += element_size;
    }
    while ((char *)IteratorRight < (char *)right)
    {
        memcpy(buffer, IteratorRight, element_size);
        IteratorRight += element_size;
        buffer += element_size;
    }
    buffer -= elements * element_size;
    for (size_t i = 0; i < elements * element_size; i += element_size)
    {
        memcpy(array + i, buffer + i, element_size);
    }
    free(buffer);
}

void mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *))
{
    if (elements <= 1)
        return;
    mergesort((char *)array, elements / 2, element_size, comparator);
    mergesort((char *)array + (elements / 2) * element_size, elements - (elements / 2), element_size, comparator);
    merge(array, elements, element_size, comparator);
}