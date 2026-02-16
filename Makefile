# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Target executable
TARGET = raycast

# Source files
SRCS = raycast.c v3math.c utils.c main.c
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile
%.o: %.c v3math.h utils.h raycast.h
	$(CC) $(CFLAGS) -c $<

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean