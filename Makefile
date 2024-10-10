# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2 -g

# Executable name
TARGET = mancala

# Source files
SRCS = mancala.c board.c constants.c minimax.c

# Object files (generated from source files)
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Linking the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)
