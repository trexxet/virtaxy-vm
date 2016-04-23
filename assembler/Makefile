clean:
	rm -rf *.o vmm-asm 
all:
	python3 gen_command_opcodes.py
	python3 gen_command_assembly.py
	gcc -o vmm-asm main.c asm.c
