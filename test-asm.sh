for f in examples/*
do
	bin/vmm-asm $f
done
rm a.vo
