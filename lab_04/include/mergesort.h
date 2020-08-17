#ifndef LAB_04_MERGESORT_H
#define LAB_04_MERGESORT_H

#include <stddef.h>

void mergesort(void *array, size_t elements,
               size_t element_size, int (*comparator)(const void *, const void *));

#endif //LAB_04_MERGESORT_H
