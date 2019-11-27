#include "bmp.h"
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 8)
        return EXIT_FAILURE;

    if (strcmp(argv[1], "crop-rotate"))
        return EXIT_FAILURE;

    bmp_file bmp_file;
    int8_t padding;

    load_bmp(&bmp_file, argv[2], &padding);

    int32_t x = atoi(argv[4]);
    int32_t y = atoi(argv[5]);
    int32_t width = atoi(argv[6]);
    int32_t height = atoi(argv[7]);

    if (x < 0 || y < 0 || width < 1 || height < 1)
    {
        full_mem_del(bmp_file);
        return EXIT_FAILURE;
    }
    if (x >= bmp_file.width || y >= bmp_file.height)
    {
        full_mem_del(bmp_file);
        return EXIT_FAILURE;
    }
    if (x + width > bmp_file.width || y + height > bmp_file.height)
    {
        full_mem_del(bmp_file);
        return EXIT_FAILURE;
    }

    crop(&bmp_file, x, y, width, height);

    rotate(&bmp_file, width, height, &padding);

    save_bmp(bmp_file, argv[3], &padding);

    return EXIT_SUCCESS;
}