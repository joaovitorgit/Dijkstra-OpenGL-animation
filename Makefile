CC = gcc
CFLAGS = -Wall -Wextra -std=c99
INCLUDES = -Iinclude
LIBS = -lglut -lGL -lGLU -lGLEW

# Source files
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

# Target executable
TARGET = dijkstra

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean build files
clean:
	rm -f $(SRCDIR)/*.o $(TARGET)

# Install dependencies (Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install build-essential freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev libglew-dev

# Install dependencies (macOS)
install-deps-mac:
	brew install freeglut glew

# Install dependencies (CentOS/RHEL)
install-deps-centos:
	sudo yum groupinstall "Development Tools"
	sudo yum install freeglut-devel mesa-libGL-devel mesa-libGLU-devel glew-devel

.PHONY: all clean install-deps install-deps-mac install-deps-centos
