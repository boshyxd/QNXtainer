CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = 

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

RUNTIME_SRC = $(wildcard $(SRC_DIR)/runtime/*.c)
CLI_SRC = $(SRC_DIR)/cli/main.c

RUNTIME_OBJ = $(patsubst $(SRC_DIR)/runtime/%.c,$(BUILD_DIR)/runtime/%.o,$(RUNTIME_SRC))
CLI_OBJ = $(BUILD_DIR)/cli/main.o

TARGET = $(BIN_DIR)/qnxtainer

all: directories $(TARGET)

directories:
	mkdir -p $(BUILD_DIR)/runtime $(BUILD_DIR)/cli $(BIN_DIR)

$(BUILD_DIR)/runtime/%.o: $(SRC_DIR)/runtime/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/cli/%.o: $(SRC_DIR)/cli/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(RUNTIME_OBJ) $(CLI_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean directories 