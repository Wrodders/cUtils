CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS =

INCLUDE_DIR = ./
TESTS_DIR = tests
BUILD_DIR = build

TEST_FILES = $(wildcard $(TESTS_DIR)/*.c)

OBJ_FILES = $(patsubst $(TESTS_DIR)/%.c,$(BUILD_DIR)/%.o,$(TEST_FILES))

EXECUTABLE = test_ring_buffer

.PHONY: all clean

all: $(BUILD_DIR) $(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)
