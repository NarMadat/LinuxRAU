CC = gcc
CFLAGS = -Wall -Wextra -O2 -pthread
TARGET = main

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) $^ -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)