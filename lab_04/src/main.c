#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "mergesort.h"

int int_comp(const void *left, const void *right) {
    return *((const int *) left) - *((const int *) right);
}

int char_comp(const void *left, const void *right) {
    return *((const char *) left) - *((const char *) right);
}

int str_comp(const void *left, const void *right) {
    return strcmp(*(char **) left, *(char **) right);
}

void mergesort_int(int len, char **data) {
    int *array = (int *) malloc((len) * sizeof(int));
    for (int i = 0; i < len; i++) {
        array[i] = atoi(data[i + 2]);
    }
    mergesort(array, len, sizeof(int), int_comp);
    for (int i = 0; i < len; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    free(array);
}

void mergesort_str(int len, char **data) {
    char **array = (char **) malloc((len) * sizeof(char *));
    for (int i = 0; i < len; i++) {
        array[i] = data[i + 2];
    }
    mergesort(array, len, sizeof(char *), str_comp);
    for (int i = 0; i < len; i++) {
        printf("%s ", array[i]);
    }
    printf("\n");
    free(array);
}

void mergesort_char(int len, char **data) {
    char *array = (char *) malloc((len) * sizeof(char));
    for (int i = 0; i < len; i++) {
        array[i] = *data[i + 2];
    }
    mergesort(array, len, sizeof(char), char_comp);
    for (int i = 0; i < len; i++) {
        printf("%c ", array[i]);
    }
    printf("\n");
    free(array);
}

int main(int argc, char *argv[]) {
    int length = argc - 2;
    char *data_type = argv[1];
    if (strcmp(data_type, "int") == 0)
        mergesort_int(length, argv);
    else if (strcmp(data_type, "str") == 0)
        mergesort_str(length, argv);
    else if (strcmp(data_type, "char") == 0)
        mergesort_char(length, argv);
    return 0;
}
