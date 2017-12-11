CC = gcc
PYTHON = python3
TARGET = vmm-asm

CSRC = main.c asm.c argtypes.c symtable.c tinyexpr.c
CFLAGS = -g -std=gnu11 -Iinclude -lm

all:
	cd ../common && make
	$(PYTHON) gen_assembly.py
	$(CC) $(CSRC) -o ../bin/$(TARGET) $(CFLAGS)

clean:
	rm asm_generated.c ../bin/vmm-asm 

