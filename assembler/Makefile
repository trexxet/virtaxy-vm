CC = gcc
PYTHON = python3
TARGET = vmm-asm

CSRC = main.c asm.c
PYSRC = gen_command_opcodes.py gen_command_assembly.py
CFLAGS =  
LDLIBS =  

all:
	$(PYTHON) $(PYSRC)
	$(CC) $(CSRC) $(CFLAGS) -o $(TARGET) $(LDFLAGS)
clean:
	rm -rf *.o vmm-asm generated/ 
