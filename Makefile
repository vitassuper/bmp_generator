CC = gcc
CFLAGS = -Wall -Wextra -std=c11

BUILD_DIR = build
LIB = $(BUILD_DIR)/libbmp.a
OBJ = $(BUILD_DIR)/bmp_generator.o

all: $(BUILD_DIR) $(LIB) example

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIB): $(OBJ)
	ar rcs $@ $^

$(BUILD_DIR)/bmp_generator.o: bmp_generator.c
	$(CC) $(CFLAGS) -c $< -o $@

example: example.c $(LIB)
	$(CC) $(CFLAGS) $< -L$(BUILD_DIR) -lbmp -o $(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)
