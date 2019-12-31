# Usage:
# make        - compile all binary
# make clean  - remove ALL binaries and objects

RM := rm
CC := gcc
CF_FLAGS := -Wall -g
MKDIR_P := mkdir -p

OSTYPE := $(shell uname)
BUILD_DIR := build_$(OSTYPE)

# Required Libraries during linking i.e., LINKERFLAGS
LIBRARIES :=

# Add header files folder here
INC_DIR := include
INCLUDES := $(addprefix -I, $(INC_DIR)/)

# Add library files here
LIB := IsBufNumeric.c
LIB += SndMsg2NxtQ.c

LIB_DIR := libsrc
OBJ_DIR := $(BUILD_DIR)/obj
OBJ_FILES := $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB))

# Add source files here
SRC := verifyNum.c

SRC_DIR := src
BIN_DIR := $(BUILD_DIR)/bin
BIN_FILES := $(patsubst %.c,$(BIN_DIR)/%,$(SRC))

# Add toolsrc files here
TOOLSRC := TestIsBufNumeric.c
TOOLSRC += TestSndMsg2NxtQ.c

TOOLSRC_DIR := toolsrc
TOOLBIN_DIR := $(BUILD_DIR)/toolbin
TOOLBIN_FILES := $(patsubst %.c,$(TOOLBIN_DIR)/%,$(TOOLSRC))

.PHONY: all build_message build clean

all: build_message build

build_message:
	@echo "Trying to build your Awesome project!"
	@echo "Creating Object & Binary files..."

build: build_dir $(OBJ_FILES) $(BIN_FILES) $(TOOLBIN_FILES)

build_dir:
	$(MKDIR_P) $(OBJ_DIR) $(BIN_DIR) $(TOOLBIN_DIR)

$(OBJ_FILES): $(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CF_FLAGS) $(INCLUDES) -o $@ -c $<

$(BIN_FILES): $(BIN_DIR)/%: $(SRC_DIR)/%.c $(OBJ_FILES)
	$(CC) $(CF_FLAGS) $(INCLUDES) $(LIBRARIES) -o $@ $< \
	$(OBJ_FILES)

$(TOOLBIN_FILES): $(TOOLBIN_DIR)/%: $(TOOLSRC_DIR)/%.c $(OBJ_FILES)
	$(CC) $(CF_FLAGS) $(INCLUDES) $(LIBRARIES) -o $@ $< \
	$(OBJ_FILES)

clean:
	@echo "Cleaning up..."
	$(RM) -rvf $(OBJ_FILES) $(BIN_FILES) $(TOOLBIN_FILES)
