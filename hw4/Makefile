C_COMPILER = gcc
MASM = masm
FLEX_COMPILER = flex
LEXER = lex.yy.c
MC_COMPILER = ./mcc
MC_SOURCE_FILE = microcode.mc
MC_DAT = prom_new.dat
MIC1 = ./mic1

# Test object files
RSHIFT_TEST_OBJ = rshift_test.obj
MULT_TEST_OBJ = mult_test.obj
DIV_TEST_OBJ = div_test.obj

all: $(MASM) $(MC_DAT) $(RSHIFT_TEST_OBJ) $(MULT_TEST_OBJ) $(DIV_TEST_OBJ)

%.o: %.c
	$(C_COMPILER) -c -g $<

$(LEXER): lex.yy.ll
	$(FLEX_COMPILER) $<

$(MASM): masm.o lex.yy.o
	$(C_COMPILER) -o $@ $^

$(MC_DAT): $(MC_SOURCE_FILE)
	$(MC_COMPILER) $^ > $(MC_DAT)

%.obj: %.asm
	./$(MASM) < $^ > $@

run-rshift-test: $(RSHIFT_TEST_OBJ)
	./$(MIC1) $(MC_DAT) $^ 0 4000

run-mult-test: $(MULT_TEST_OBJ)
	./$(MIC1) $(MC_DAT) $^ 0 4000

run-div-test: $(DIV_TEST_OBJ)
	./$(MIC1) $(MC_DAT) $^ 0 4000

clean:
	rm -f *.o $(MASM) $(LEXER) $(MC_DAT) $(RSHIFT_TEST_OBJ) $(MULT_TEST_OBJ) $(DIV_TEST_OBJ)
