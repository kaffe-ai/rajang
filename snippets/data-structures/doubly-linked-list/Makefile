# Compiler and flags
CC = gcc
DEBUG ?= 1
EXE = app


# Directory structure
SRC_DIR = src
INCLUDE = include
OBJ_DIR = obj
BIN_DIR = bin

RELASE_DIR = $(BIN_DIR)/release
DEBUG_DIR = $(BIN_DIR)/debug

SRC := $(wildcard $(SRC_DIR)/*.c)
HEADERS :=
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

LDFLAGS += -lm

CFLAGS += -std=c2x -D_GNU_SOURCE

# Target executable name

ifeq ($(DEBUG), 0)
CFLAGS += -O3 -DNDEBUG
BUILD_DIR := $(RELASE_DIR)
TARGET := $(BUILD_DIR)/$(EXE)
else
CFLAGS += -Og -DDEBUG -g -Wall -Wextra -Wno-constant-logal-operand
BUILD_DIR := $(DEBUG_DIR)
TARGET := $(BUILD_DIR)/$(EXE)
endif


.PHONY: all exec
.PHONY: clean distclean
.PHONY: dirs

all: dirs exec
exec: $(TARGET)

$(TARGET): $(OBJ) $(HEADERS) Makefile
        $(CC) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
        $(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

dirs:
        @mkdir -p $(OBJ_DIR)
        @mkdir -p $(BUILD_DIR)

clean:
        rm -f $(OBJ)
        rm -rf $(RELEASE_DIR)
        rm -rf $(DEBUG_DIR)

distclean: clean
        rm -rf $(OBJ_DIR)
        rm -rf $(BIN_DIR)
