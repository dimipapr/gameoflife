PROG_NAME = gameoflife
SOURCE_DIR = src
RELEASE_DIR = release
DEBUG_DIR = debug
RELEASE_TARGET = $(RELEASE_DIR)/$(PROG_NAME)
DEBUG_TARGET = $(DEBUG_DIR)/$(PROG_NAME)

CC=gcc
CFLAGS=-std=c99
CFLAGS+=-Wall -Werror -Wextra -Wfloat-equal -Wundef -Wshadow \
-Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings \
-Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum \
-Wconversion -Wunreachable-code
CFLAGS+=-I.$(SOURCE_DIR)

DEBUG_CFLAGS:=-DDEBUG -Og -g
RELEASE_CFLAGS:=-O

SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
DEBUG_OBJECTS = $(patsubst $(SOURCE_DIR)/%.c,$(DEBUG_DIR)/%.o,$(SOURCES))
RELEASE_OBJECTS = $(patsubst $(SOURCE_DIR)/%.c,$(RELEASE_DIR)/%.o,$(SOURCES))

all:$(DEBUG_TARGET) $(RELEASE_TARGET)

$(DEBUG_TARGET):$(DEBUG_OBJECTS)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) $(DEBUG_OBJECTS) -o $(DEBUG_TARGET)

$(RELEASE_TARGET):$(RELEASE_OBJECTS)
	$(CC) $(CFLAGS) $(RELEASE_OBJECTS) -o $(RELEASE_TARGET)

$(DEBUG_DIR)/%.o:$(SOURCE_DIR)/%.c
	@echo Running debuggy stuff
	$(CC) -c $(CFLAGS) $(DEBUG_CFLAGS) $^ -o $@

$(RELEASE_DIR)/%.o:$(SOURCE_DIR)/%.c
	@echo Running releassy stuff
	$(CC) -c $(CFLAGS) $(RELEASE_CFLAGS) $^ -o $@

clean:
	@rm -rf $(RELEASE_DIR)/*
	@rm -rf $(DEBUG_DIR)/*

configure:
	@mkdir -p $(RELEASE_DIR)
	@mkdir -p $(DEBUG_DIR)

run: $(DEBUG_TARGET)
	@$(DEBUG_TARGET)

run_release: $(RELEASE_TARGET)
	@$(RELEASE_TARGET)

.PHONY: clean run run_release configure all