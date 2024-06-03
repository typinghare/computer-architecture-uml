masm_nr: nand_rshift.o lex.yy.o
	gcc -o masm_nr nand_rshift.o lex.yy.o

%.o: %.c
	gcc -c -g $<

lex.yy.c: nand_rshift.ll
	flex nand_rshift.ll

clean:
	rm lex.yy.o lex.yy.c nand_rshift.o masm_nr
