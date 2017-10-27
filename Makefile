asm:
	cd assembler && make

asm-clean:
	cd assembler && make clean

all: asm

clean: asm-clean

