PROG_NAME = gameoflife
SOURCE_DIR = src
RELEASE_DIR = release
BUILD_DIR = build
TARGET = $(RELEASE_DIR)/$(PROG_NAME)

CC=gcc
CFLAGS=-std=c99
CFLAGS+=-Wall -Werror -Wextra -Wfloat-equal -Wundef -Wshadow \
-Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings \
-Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum \
-Wconversion -Wunreachable-code
CFLAGS+=-Og
CFLAGS+=-I.src

SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS = $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

all:$(TARGET)

$(TARGET):$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

$(BUILD_DIR)/%.o:$(SOURCE_DIR)/%.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	@rm -rf build/*
	@rm -rf release/*

test:
	@echo $(SOURCES)
	@echo $(OBJECTS)

run: $(TARGET)
	@$(RELEASE_DIR)/$(PROG_NAME)