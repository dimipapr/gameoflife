PROGRAM=gameoflife
SOURCE_DIR=src
RELEASE_DIR=release
DEBUG_DIR=debug
DEBUG_TARGET=$(DEBUG_DIR)/$(PROGRAM)
RELEASE_TARGET=$(RELEASE_DIR)/$(PROGRAM)

SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
HEADERS = $(wildcard $(SOURCE_DIR)/*.h)
DEBUG_OBJECTS = $(patsubst $(SOURCE_DIR)/%.c,$(DEBUG_DIR)/%.o,$(SOURCES))
RELEASE_OBJECTS = $(patsubst $(SOURCE_DIR)/%.c,$(RELEASE_DIR)/%.o,$(SOURCES))

CC=gcc
CFLAGS=-Wall -Wextra -Wfloat-equal -Wundef -Wshadow
CFLAGS+=-Wpointer-arith -Wcast-align -Wstrict-prototypes -Wswitch-default
CFLAGS+=-Wswitch-enum -Wconversion -Wunreachable-code
CFLAGS+=-Werror-implicit-function-declaration
CFLAGS+=-std=c99
CFLAGS+=-I.$(SOURCE_DIR)

#LIBS=-lc

RELEASE_CFLAGS=-O2
DEBUG_CFLAGS=-g -Og -DDEBUG

debug:$(DEBUG_TARGET)
	gdb $(DEBUG_TARGET)
run_debug:$(DEBUG_TARGET)
	./$(DEBUG_TARGET)
build_debug:$(DEBUG_TARGET)
$(DEBUG_TARGET):$(DEBUG_OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) $(LIBS) $^ -o $@
$(DEBUG_DIR)/%.o:$(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) $(LIBS) -c $< -o $@


run_release:$(RELEASE_TARGET)
	./$(RELEASE_TARGET)
build_release:$(RELEASE_TARGET)
$(RELEASE_TARGET):$(RELEASE_OBJECTS)
	$(CC) $(CFLAGS) $(RELEASE_CFLAGS) $(LIBS) $^ -o $@
$(RELEASE_DIR)/%.o:$(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(RELEASE_CFLAGS) $(LIBS) -c $< -o $@

create_structure:
	@mkdir -p release
	@mkdir -p debug

clean:
	@rm -rf $(RELEASE_DIR)/*
	@rm -rf $(DEBUG_DIR)/*

list:
	@grep '^[^#[:space:]].*:' Makefile

.PHONY: clean create_structure build_debug run_debug list build_release