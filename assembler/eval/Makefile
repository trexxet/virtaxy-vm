eval: eval.y eval.l test.c
	bison --defines=eval.tab.h -o eval.tab.c eval.y
	flex -o eval.lex.c eval.l
	gcc -g -DYYSTYPE=int64_t -DYYSTYPE_PR=PRId64 -o eval test.c eval.lex.c eval.tab.c

clean:
	rm -rf eval eval.tab* eval.lex*

