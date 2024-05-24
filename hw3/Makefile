C_COMPILER = gcc
M_ASSEMBLER = ./masm
MIC1 = ./mic1
ASM_FILE = rfib.asm
ASM_OBJECTS = rfib.obj
STARTING_ADDRESS = 0
STARTING_STACK_POINTER = 4000
C_OBJECTS = rfib.o
C_PROGRAM = rfib_c

$(ASM_OBJECTS): $(ASM_FILE)
	$(M_ASSEMBLER) < $(ASM_FILE) > $(ASM_OBJECTS)

%.o: %.c
	$(C_COMPILER) -c $<

all: $(ASM_OBJECTS)

run: $(ASM_OBJECTS)
	$(MIC1) prom.dat $(ASM_OBJECTS) $(STARTING_ADDRESS) $(STARTING_STACK_POINTER)

$(C_PROGRAM): $(C_OBJECTS)
	$(C_COMPILER) -o $@ $^

run-c: $(C_PROGRAM)
	./$(C_PROGRAM) && make clean-c

clean-c:
	rm -f *.o $(C_PROGRAM)

clean:
	rm -f $(ASM_OBJECTS)