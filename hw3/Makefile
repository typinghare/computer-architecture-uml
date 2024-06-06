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
	$(M_ASSEMBLER) < $^ > $(ASM_OBJECTS)

%.o: %.c
	$(C_COMPILER) -c $<

all: $(ASM_OBJECTS)

run: $(ASM_OBJECTS)
	$(MIC1) prom.dat $^ $(STARTING_ADDRESS) $(STARTING_STACK_POINTER)

$(C_PROGRAM): $(C_OBJECTS)
	$(C_COMPILER) -o $@ $^

run-c: $(C_PROGRAM)
	./$(C_PROGRAM) && make clean-c

clean-c:
	rm -f *.o $(C_PROGRAM)

clean: clean-c
	rm -f $(ASM_OBJECTS) ifib.obj rfib_unoptimized.obj

run-unoptimized: rfib_unoptimized.asm
	$(M_ASSEMBLER) < $^ > rfib_unoptimized.obj
	$(MIC1) prom.dat rfib_unoptimized.obj $(STARTING_ADDRESS) $(STARTING_STACK_POINTER)