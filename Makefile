# Makefile for apex7-custom-clock
# Project: apex7-custom-clock
# Author: Bipin Adhikari
# Description: Build configuration for Windows

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
LDFLAGS = -lwinhttp
TARGET = apex7_clock.exe

# Source files
SOURCES = main.c \
          clock_handler.c \
          time_formatter.c \
          json_builder.c \
          http_client.c \
          file_reader.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo Build complete: $(TARGET)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Release build (hide console)
release: CFLAGS += -DRELEASE_BUILD -mwindows
release: clean $(TARGET)
	@echo Release build complete: $(TARGET)

# Clean build artifacts
clean:
	del /Q *.o $(TARGET) 2>nul || true

# Rebuild
rebuild: clean all

.PHONY: all clean rebuild release
