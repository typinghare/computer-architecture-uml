# C and flex compiling
C_COMPILER = gcc
MASM = masm
FLEX_COMPILER = flex
LEXER = lex.yy.c

# Microcode compiling
MC_COMPILER = ./mcc
MC_SOURCE_FILE = microcode.mc
MC_PROM_DAT = prom.dat

# Test object files
RSHIFT_TEST_OBJ = rshift_test.obj
MULT_TEST_OBJ = mult_test.obj
DIV_TEST_OBJ = div_test.obj

# Mic-1
MIC1 = ./mic1
STARTING_PC = 0
STARTING_SP = 4000

all: $(MASM) $(MC_PROM_DAT) $(RSHIFT_TEST_OBJ) $(MULT_TEST_OBJ) $(DIV_TEST_OBJ)

%.o: %.c
	$(C_COMPILER) -c -g $<

$(LEXER): lex.yy.ll
	$(FLEX_COMPILER) $<

$(MASM): masm.o lex.yy.o
	$(C_COMPILER) -o $@ $^

$(MC_PROM_DAT): $(MC_SOURCE_FILE)
	$(MC_COMPILER) $^ > $(MC_PROM_DAT)

%.obj: %.asm
	./$(MASM) < $^ > $@

run-rshift-test: $(RSHIFT_TEST_OBJ)
	./$(MIC1) $(MC_PROM_DAT) $^ $(STARTING_PC) $(STARTING_SP)

run-mult-test: $(MULT_TEST_OBJ)
	./$(MIC1) $(MC_PROM_DAT) $^ $(STARTING_PC) $(STARTING_SP)

run-div-test: $(DIV_TEST_OBJ)
	./$(MIC1) $(MC_PROM_DAT) $^ $(STARTING_PC) $(STARTING_SP)

clean:
	rm -f *.o $(MASM) $(LEXER) $(MC_PROM_DAT) $(RSHIFT_TEST_OBJ) $(MULT_TEST_OBJ) $(DIV_TEST_OBJ)
