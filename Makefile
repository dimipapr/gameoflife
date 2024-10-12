PROGRAM=gameoflife
SOURCE_DIR=src
RELEASE_DIR=release
DEBUG_DIR=debug
DEBUG_TARGET=$(DEBUG_DIR)/$(PROGRAM)
RELEASE_TARGET=$(RELEASE_DIR)/$(PROGRAM)

SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
DEBUG_OBJECTS = $(patsubst $(SOURCE_DIR)/%.c,$(DEBUG_DIR)/%.o,$(SOURCES))
RELEASE_OBJECTS = $(patsubst $(SOURCE_DIR)/%.c,$(RELEASE_DIR)/%.o,$(SOURCES))

CC=gcc
CFLAGS=-Wall -Wextra -Wfloat-equal -Wundef -Wshadow \
-Wpointer-arith -Wcast-align -Wstrict-prototypes -Wswitch-default \
-Wswitch-enum -Wconversion -Wunreachable-code \
-Werror-implicit-function-declaration

RELEASE_CFLAGS=-O2
DEBUG_CFLAGS=-g -Og

debug:$(DEBUG_TARGET)
	gdb $(DEBUG_TARGET)
run_debug:$(DEBUG_TARGET)
	./$(DEBUG_TARGET)
build_debug:$(DEBUG_TARGET)
$(DEBUG_TARGET):$(DEBUG_OBJECTS)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) $^ -o $@
$(DEBUG_DIR)/%.o:$(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -c $< -o $@


run_release:$(RELEASE_TARGET)
	./$(RELEASE_TARGET)
build_release:$(RELEASE_TARGET)
$(RELEASE_TARGET):$(RELEASE_OBJECTS)
	$(CC) $(CFLAGS) $(RELEASE_CFLAGS) $^ -o $@
$(RELEASE_DIR)/%.o:$(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) $(RELEASE_CFLAGS) -c $< -o $@

create_structure:
	@mkdir -p release
	@mkdir -p debug

clean:
	@rm -rf $(RELEASE_DIR)/*
	@rm -rf $(DEBUG_DIR)/*

list:
	@grep '^[^#[:space:]].*:' Makefile

.PHONY: clean create_structure build_debug run_debug list build_release