CC = gcc
TARGET = vmm

CSRC = main.c machine.c mem.c
CFLAGS = -g -std=gnu11 -Iinclude

all:
	$(CC) $(CSRC) $(CFLAGS) -o ../bin/$(TARGET)

clean:
	rm ../bin/vmm

