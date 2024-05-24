C_COMPILER = gcc
M_ASSEMBLER = ./masm
MIC1 = ./mic1
ASM_FILE = rfib.asm
OBJ_FILE = rfib.obj
STARTING_ADDRESS = 0
STARTING_STACK_POINTER = 4001
C_OBJECTS = rfib.o
C_PROGRAM = rfib_c

$(OBJ_FILE): $(ASM_FILE)
	$(M_ASSEMBLER) < $(ASM_FILE) > $(OBJ_FILE)

%.o: %.c
	$(C_COMPILER) -c $<

all: $(OBJ_FILE)

run: $(OBJ_FILE)
	$(MIC1) prom.dat $(OBJ_FILE) $(STARTING_ADDRESS) $(STARTING_STACK_POINTER)

$(C_PROGRAM): $(C_OBJECTS)
	$(C_COMPILER) -o $@ $^

run-c: $(C_PROGRAM)
	./$(C_PROGRAM)

clean:
	rm -f *.o $(C_PROGRAM)