# Bmp image generator

A minimal C library for generating BMP image files.

![Lenin is a mushroom](image.bmp)


## Building

```bash
make
```

Builds the static library and example binary into the `build/` directory.

```bash
make clean
```

Removes the `build/` directory and all compiled artifacts.

## Usage

Link against `libbmp.a` and include `bmp_generator.h`.

```c
#include "bmp_generator.h"

uint8_t result = bmp_save_to_file(file, width, height, pixels, bitmap_size);
if (result != 0) {
    fprintf(stderr, "Failed to write BMP\n");
}
```

## API

```c
uint8_t bmp_save_to_file(FILE *file, const uint16_t width, const uint16_t height,
                     const uint8_t *bitmap, const uint32_t bitmap_size);
```

Writes a 24-bit BMP image to an already-opened file.

| Parameter     | Description                                              |
|---------------|----------------------------------------------------------|
| `file`        | Opened file handle to write to                           |
| `width`       | Image width in pixels                                    |
| `height`      | Image height in pixels                                   |
| `bitmap`      | 24-bit BGR pixel data (byte order: B, G, R per pixel), rows padded to a multiple of 4 bytes |
| `bitmap_size` | Size of bitmap in bytes; must equal `height * ((width * 3 + 3) & ~3)` |

Returns `0` on success, `1` on failure.

## BMP Format Notes

- Pixel format: 24-bit BGR (not RGB)
- Each row must be padded to a multiple of 4 bytes
- Row stride: `(width * 3 + 3) & ~3`
- DIB header: BITMAPCOREHEADER (12 bytes)
