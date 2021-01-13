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

all: build/ $(foreach lib,$(LIBS),$(lib).so) | $(EXES)
	@echo
	@echo Build done!

install: 
ifeq ($(wildcard $(LIBDIR)),)
	mkdir $(LIBDIR)
endif
	$(foreach lib,$(LIBS),cp $(SRCDIR)/$(lib).h $(LIBDIR)/)
	$(foreach lib,$(LIBS),cp $(BLDDIR)/$(lib).so $(LIBDIR)/)
	ldconfig -n -v $(LIBDIR)
	$(foreach exe,$(EXES),cp $(BLDDIR)/$(exe) $(EXEDIR)/)
	@echo
	@echo Install done!

uninstall: 
	$(foreach exe,$(EXES),rm -f $(EXEDIR)/$(exe))
	rm -rfv $(LIBDIR)

hacasm: $(SRCDIR)/hacasm.c hacal_asmlib.so
	$(CC) $(CPARAM) -o $(BLDDIR)/$@ $< build/hacal_asmlib.so
	chmod +x $(BLDDIR)/$@

%.so: $(SRCDIR)/%.c
	$(CC) $(CPARAM) -shared -o $(BLDDIR)/$@ -fPIC $<

%.h: $(SRCDIR)/%.c
	cp $< $(BLDDIR)/$@

%/:
	mkdir $@
