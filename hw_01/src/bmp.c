#include "bmp.h"
#include <string.h>
#include <stdio.h>

#define BYTES_PER_PIXEL 3

const uint8_t iter_size = 2;
const uint8_t iter_width = 18;
const uint8_t iter_height = 22;
const uint8_t iter_size_image = 34;
const uint8_t header_size = 54;

void header_change(bmp_file *bmp_file, int32_t new_width, int32_t new_height, int8_t *padding);

void load_bmp(bmp_file *bmp_file, char *fileName, int8_t *padding) {
    FILE *fin = fopen(fileName, "rb");
    assert(fin);
    bmp_file->buffer = (char *) malloc(sizeof(char) * header_size);
    assert(bmp_file->buffer);
    fread(bmp_file->buffer, sizeof(char), header_size, fin);

    memcpy(&(bmp_file->size), bmp_file->buffer + iter_size, 4);
    memcpy(&(bmp_file->width), bmp_file->buffer + iter_width, 4);
    memcpy(&(bmp_file->height), bmp_file->buffer + iter_height, 4);
    memcpy(&(bmp_file->size_image), bmp_file->buffer + iter_size_image, 4);

    *padding = (4 - ((bmp_file->width * BYTES_PER_PIXEL % 4))) % 4;

    bmp_file->matrix = (pixel *) malloc(bmp_file->height * (BYTES_PER_PIXEL * bmp_file->width));

    for (int i = 0; i < bmp_file->height; i++) {
        for (int j = 0; j < bmp_file->width; j++) {
            fread(&(bmp_file->matrix)[bmp_file->width * i + j], BYTES_PER_PIXEL, 1, fin);
        }
        fseek(fin, *padding, SEEK_CUR);
    }
    fclose(fin);
    assert(fin);
}

void crop(bmp_file *bmp_file, int32_t x, int32_t y, int32_t new_width, int32_t new_height) {
    pixel *new_matrix = (pixel *) malloc(new_height * (new_width * BYTES_PER_PIXEL));
    assert(new_matrix);

    for (int i = 0; i < new_height; i++)
        for (int j = 0; j < new_width; j++)
            new_matrix[(new_height - i - 1) * new_width + j] =
                    bmp_file->matrix[(bmp_file->height - y - i - 1) * (bmp_file->width) + x + j];

    free(bmp_file->matrix);
    bmp_file->matrix = new_matrix;
}

void rotate(bmp_file *bmp_file, int32_t new_width, int32_t new_height, int8_t *padding) {
    pixel *reversed_matrix = (pixel *) malloc(new_width * (new_height * BYTES_PER_PIXEL));
    assert(reversed_matrix);

    for (int i = 0; i < new_width; i++)
        for (int j = 0; j < new_height; j++)
            reversed_matrix[(new_width - i - 1) * new_height + j] = bmp_file->matrix[j * new_width + i];
    free(bmp_file->matrix);
    bmp_file->matrix = reversed_matrix;
    header_change(bmp_file, new_width, new_height, padding);
}

void save_bmp(bmp_file bmp_file, char *fileName, int8_t *padding) {
    FILE *fout = fopen(fileName, "wb");
    assert(fout);

    int8_t zero = 0;

    fwrite(bmp_file.buffer, sizeof(char), header_size, fout);

    for (int i = 0; i < bmp_file.height; i++) {
        for (int j = 0; j < bmp_file.width; j++)
            fwrite((&bmp_file.matrix[i * bmp_file.width + j]), BYTES_PER_PIXEL, 1, fout);

        for (int j = 0; j < *padding; j++)
            fwrite(&zero, sizeof(int8_t), 1, fout);
    }
    fclose(fout);
}

void header_change(bmp_file *bmp_file, int32_t new_width, int32_t new_height, int8_t *padding) {
    bmp_file->width = new_height;
    memcpy(bmp_file->buffer + iter_width, &bmp_file->width, 4);

    bmp_file->height = new_width;
    memcpy(bmp_file->buffer + iter_height, &bmp_file->height, 4);

    *padding = (4 - ((bmp_file->width * BYTES_PER_PIXEL % 4))) % 4;

    bmp_file->size = header_size + bmp_file->height * (bmp_file->width * BYTES_PER_PIXEL + (*padding) * sizeof(int8_t));
    memcpy(bmp_file->buffer + iter_size, &bmp_file->size, 4);

    bmp_file->size_image = bmp_file->height * (bmp_file->width * BYTES_PER_PIXEL + (*padding) * sizeof(int8_t));
    memcpy(bmp_file->buffer + iter_size_image, &bmp_file->size_image, 4);
}

void full_memory_free(bmp_file bmp_file) {
    free(bmp_file.matrix);
    free(bmp_file.buffer);
}
