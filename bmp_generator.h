#include <stdint.h>
#include <stdio.h>

/*
 * bitmap: 24-bit BGR pixels (byte order: B, G, R), rows padded to a multiple of
 * 4 bytes
 *
 * Return: 0 on success, 1 on failure
 */
uint8_t bmp_save_to_file(FILE *file, const uint16_t width, const uint16_t height,
                     const uint8_t *bitmap, const uint32_t bitmap_size);
