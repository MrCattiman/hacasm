CC     = gcc
CPARAM = -Wall -pedantic

SRCDIR = src
BLDDIR = build
EXEDIR = /usr/bin

EXES := hacasm

clean:
	rm -rf $(BLDDIR)

all: $(BLDDIR)/ $(foreach lib,$(LIBS),$(lib).so) | $(EXES)
	@echo
	@echo Build done!

install: 
	$(foreach exe,$(EXES),cp $(BLDDIR)/$(exe) $(EXEDIR)/)
	@echo
	@echo Install done!

uninstall: 
	$(foreach exe,$(EXES),rm -f $(EXEDIR)/$(exe))

hacasm: $(SRCDIR)/hacasm.c
	$(CC) $(CPARAM) -o $(BLDDIR)/$@ $< -lhacal_asm
	chmod +x $(BLDDIR)/$@

%/:
	mkdir $@
