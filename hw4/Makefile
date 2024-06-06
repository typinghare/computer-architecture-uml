C_COMPILER = gcc
MASM = masm
FLEX_COMPILER = flex
LEXER = lex.yy.c

%.o: %.c
	$(C_COMPILER) -c -g $<

$(LEXER): lex.yy.ll
	$(FLEX_COMPILER) $<

$(MASM): masm.o lex.yy.o
	$(C_COMPILER) -o $@ $^

clean:
	rm *.o $(MASM) $(LEXER)