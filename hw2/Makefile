COMPILER = gcc
DEPS = framework.h
OBJECTS = framework.o main.o
PROGRAM = main

%.o: %.c
	$(COMPILER) -c $<

$(PROGRAM): $(OBJECTS)
	$(COMPILER) -o $@ $^

# Compile the program
all: $(PROGRAM)

# Remove the program and all object files
clean:
	rm -f *.o $(PROGRAM)

# Compile the program and run it on the fly
run: $(PROGRAM)
	./$(PROGRAM)