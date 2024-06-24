COMPILER = gcc
HEADERS = common.h symbol.h instruction.h
OBJECTS = linker.o
PROGRAM = linker

all: $(PROGRAM)

%.o: %.c $(HEADERS)
	$(COMPILER) -c -g $<

$(PROGRAM): $(OBJECTS)
	$(COMPILER) -o $@ $^

test: $(PROGRAM) test/main1.obj test/main2.obj
	./$< -s test/main1.obj test/main2.obj

clean:
	rm -f $(OBJECTS) $(PROGRAM)