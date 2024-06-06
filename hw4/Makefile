C_COMPILER = gcc
MASM = masm
FLEX_COMPILER = flex
LEXER = lex.yy.c
MC_COMPILER = mcc
MC_SOURCE_FILE = microcode.mc
MC_DAT = prom_new.dat

all: $(MASM)

%.o: %.c
	$(C_COMPILER) -c -g $<

$(LEXER): lex.yy.ll
	$(FLEX_COMPILER) $<

$(MASM): masm.o lex.yy.o
	$(C_COMPILER) -o $@ $^

$(MC_DAT): $(MC_SOURCE_FILE)
	$(MC_COMPILER) $^ > $(MC_DAT)

clean:
	rm -f *.o $(MASM) $(LEXER)
