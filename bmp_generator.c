#include "bmp_generator.h"

#define FILE_HEADER_SIZE 14
#define DIB_HEADER_SIZE 12

#define HEADER_SIZE (FILE_HEADER_SIZE + DIB_HEADER_SIZE)

uint8_t bmp_save_to_file(FILE *file, const uint16_t width, const uint16_t height,
                     const uint8_t *bitmap, const uint32_t bitmap_size) {
  if (!file || !bitmap || bitmap_size > UINT32_MAX - HEADER_SIZE)
    return 1;

  uint32_t filesize = HEADER_SIZE + bitmap_size;

  uint8_t header[HEADER_SIZE] = {
      0x42, 0x4D,             // Magic number
      0x00, 0x00, 0x00, 0x00, // filesize
      0x00, 0x00,             // reserved
      0x00, 0x00,             // reserved
      0x00, 0x00, 0x00, 0x00, // start pixel address

      // DIB
      0x0C, 0x00, 0x00, 0x00, // DIB id
      0x01, 0x00,             // width
      0x01, 0x00,             // height
      0x01, 0x00,             // must be 1 for this DIB
      0x18, 0x00,             // 24 bit pixel
  };

  header[2] = filesize & 0xFF;
  header[3] = (filesize >> 8) & 0xFF;
  header[4] = (filesize >> 16) & 0xFF;
  header[5] = (filesize >> 24) & 0xFF;

  header[10] = HEADER_SIZE & 0xFF;
  header[11] = (HEADER_SIZE >> 8) & 0xFF;
  header[12] = (HEADER_SIZE >> 16) & 0xFF;
  header[13] = (HEADER_SIZE >> 24) & 0xFF;

  header[18] = width & 0xFF;
  header[19] = (width >> 8) & 0xFF;

  header[20] = height & 0xFF;
  header[21] = (height >> 8) & 0xFF;

  size_t bytes_written = 0;

  bytes_written = fwrite(header, sizeof(uint8_t), HEADER_SIZE, file);

  if (bytes_written != HEADER_SIZE) {
    return 1;
  }

  bytes_written = fwrite(bitmap, sizeof(uint8_t), bitmap_size, file);

  if (bytes_written != bitmap_size) {
    return 1;
  }

  return 0;
}
