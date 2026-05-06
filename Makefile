CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = astar_project

all:
	$(CC) $(CFLAGS) main.c astar.c -o $(TARGET) -lm

clean:
	rm -f $(TARGET)