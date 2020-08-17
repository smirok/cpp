#ifndef BMP_H_
#define BMP_H_

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

typedef struct pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} pixel;

typedef struct bmp_file {
    char *buffer;
    uint32_t size;
    int32_t width;
    int32_t height;
    uint32_t size_image;
    pixel *matrix;
} bmp_file;

void load_bmp(bmp_file *bmp_file, char *fileName, int8_t *padding);

void crop(bmp_file *bmp_file, int32_t, int32_t, int32_t, int32_t);

void rotate(bmp_file *bmp_file, int32_t w, int32_t h, int8_t *padding);

void save_bmp(bmp_file bmp_file, char *fileName, int8_t *padding);

void full_memory_free(bmp_file bmp_file);

#endif