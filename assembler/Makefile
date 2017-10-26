CC = gcc
PYTHON = python3
TARGET = vmm-asm

CSRC = main.c asm.c symtable.c
CFLAGS = -g -std=gnu11 -Iinclude
LDLIBS =  

all:
	$(PYTHON) py/gen_opcodes.py
	$(PYTHON) py/gen_assembly.py
	$(PYTHON) py/gen_reg_asm.py
	$(CC) $(CSRC) $(CFLAGS) -o $(TARGET) $(LDLIBS)
clean:
	rm -rf *.o vmm-asm generated/*

