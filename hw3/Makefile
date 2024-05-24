C_COMPILER = gcc
ASM_FILE = rfib.asm
OBJ_FILE = rfib.obj
STARTING_ADDRESS = 0
STARTING_STACK_POINTER = 2048
C_OBJECTS = rfib.o
C_PROGRAM = rfib_c

$(OBJ_FILE):
	./masm < $(ASM_FILE) > $(OBJ_FILE)

%.o: %.c
	$(C_COMPILER) -c $<

all: $(OBJ_FILE)

run: $(OBJ_FILE)
	./mic1 prom.dat $(OBJ_FILE) $(STARTING_ADDRESS) $(STARTING_STACK_POINTER)

$(C_PROGRAM): $(C_OBJECTS)
	$(C_COMPILER) -o $@ $^

run-c: $(C_PROGRAM)
	./$(C_PROGRAM)

clean:
	rm -f *.o $(C_PROGRAM)