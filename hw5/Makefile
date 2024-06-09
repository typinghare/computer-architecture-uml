MASM = masm
PROM_MRD_DAT = prom_mrd.dat
ADDITION_OBJ = addition.obj

# Mic-1
MIC1 = ./mic1
STARTING_PC = 0
STARTING_SP = 4000

all: $(ADDITION_OBJ)

run: $(PROM_MRD_DAT) $(ADDITION_OBJ)
	$(MIC1) $^ $(STARTING_PC) $(STARTING_SP)

%.obj: %.asm
	./$(MASM) < $< > $@

clean:
	rm -f $(ADDITION_OBJ)