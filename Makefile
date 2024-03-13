# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Wsign-conversion -Wconversion -pedantic -std=c99 #-mwindows
SRC_DIR = src
BUILD_DIR = build
TARGET = main

# Dependencies
DEPS = patcher.h

# Object files
OBJ = $(SRC_DIR)/main.o $(SRC_DIR)/patcher.o

.PHONY: all clean

all: $(BUILD_DIR)/$(TARGET).exe

$(BUILD_DIR)/$(TARGET).exe: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lcomctl32 -lgdi32

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) *.exe 
	rm -rf $(SRC_DIR)/*.o
