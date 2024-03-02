CC = gcc
CFLAGS = -Wall -Wextra -Wsign-conversion -Wconversion -pedantic -std=c99 -mwindows
SRC_DIR = src
BUILD_DIR = build
TARGET = main

.PHONY: all clean

all: $(BUILD_DIR)/$(TARGET).exe

$(BUILD_DIR)/$(TARGET).exe: $(SRC_DIR)/$(TARGET).c
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) *.exe
