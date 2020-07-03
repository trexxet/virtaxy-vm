eval: eval.y eval.l eval.c eval.h test.c
	bison --defines=eval.tab.h -o eval.tab.c eval.y
	flex -o eval.lex.c eval.l
	gcc -g -DYYSTYPE=int64_t -DYYSTYPE_PR=PRId64 -o eval test.c eval.c eval.lex.c eval.tab.c

clean:
	rm -rf eval eval.tab* eval.lex*

