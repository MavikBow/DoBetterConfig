# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Wsign-conversion -Wconversion -pedantic -std=c99 -mwindows
LAUNCH_CFLAGS = -O2 -s

# Resource compiler (windres for GCC)
RC = windres

SRC_DIR = src
BUILD_DIR = build
RESRC_DIR = $(SRC_DIR)/resrc
TARGET = DoBetterConfig.exe

# Dependencies
DEPS = patcher.h myicon.h

# Object files
OBJ = $(SRC_DIR)/main.o $(SRC_DIR)/patcher.o
RES = $(RESRC_DIR)/myicon.res 
METADATA = $(RESRC_DIR)/metadata.res

.PHONY: all clean

all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET) 

launch: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET)_launch 

$(BUILD_DIR)/$(TARGET): $(OBJ) $(RES) $(METADATA)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/$(TARGET)_launch: $(OBJ) $(RES) $(METADATA)
	$(CC) $(CFLAGS) $(LAUNCH_CFLAGS) $^ -o $(BUILD_DIR)/$(TARGET) -s

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(METADATA): $(METADATA:.res=.rc)
	$(RC) $< -O coff -o $@

$(RESRC_DIR)/%.res: $(RESRC_DIR)/%.rc $(RESRC_DIR)/%.h $(RESRC_DIR)/*.ico
	$(RC) $< -O coff -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean: 
	cmd /c "del /Q /S *.o"
	cmd /c "del /Q /S *.res"
