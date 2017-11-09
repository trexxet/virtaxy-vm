CC = gcc
PYTHON = python3
TARGET = vmm

CSRC = main.c machine.c mem.c
CFLAGS = -g -std=gnu11 -Iinclude

all:
	cd ../common && make
	$(PYTHON) gen_machine.py
	$(CC) $(CSRC) $(CFLAGS) -o ../bin/$(TARGET)

clean:
	rm bin/vmm

