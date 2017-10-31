CC = gcc
PYTHON = python3
TARGET = vmm-asm

CSRC = main.c asm.c argtypes.c symtable.c
CFLAGS = -g -std=gnu11 -Iinclude

all:
	cd ../common && make
	$(PYTHON) gen_assembly.py
	$(CC) $(CSRC) $(CFLAGS) -o bin/$(TARGET)

clean:
	rm asm_generated.c bin/vmm-asm 

