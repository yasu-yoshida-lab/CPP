# Makefile
CC = g++
CFLAGS = -std=c++17
TARGET = shared_ptr

default:
	$(CC) $(CFLAGS) $(TARGET).cpp
	./a.out
	rm -r a.out

clean:
	rm -r a.out

.PHONY: clean
