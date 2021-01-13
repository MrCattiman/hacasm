CC     = gcc
CPARAM = -Wall -pedantic

SRCDIR = src
BLDDIR = build
LIBDIR = /usr/lib/HACAL
HEDDIR = /usr/include/HACAL
EXEDIR = /usr/bin

LIBS := hacal_asmlib
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
	$(CC) $(CPARAM) -o $(BLDDIR)/$@ $< -llibhacal_asm
	chmod +x $(BLDDIR)/$@

%.so: $(SRCDIR)/%.c
	$(CC) $(CPARAM) -shared -o $(BLDDIR)/$@ -fPIC $<

%.h: $(SRCDIR)/%.c
	cp $< $(BLDDIR)/$@

%/:
	mkdir $@
