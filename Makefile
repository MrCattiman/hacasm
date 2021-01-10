CC     = gcc

SRCDIR = src
BLDDIR = build
LIBDIR = /usr/lib/HACAL
HEDDIR = /usr/include/HACAL
EXEDIR = /usr/bin

LIBS := hacal_asmlib
EXES := hacasm

all: build/ $(foreach lib,$(LIBS),$(lib).so) | $(EXES)
	@echo
	@echo Build done!

install: 
ifeq ($(wildcard $(LIBDIR)),)
	mkdir $(LIBDIR)
endif
	cp $(BLDDIR)/*.h $(LIBDIR)/
	cp $(BLDDIR)/*.so $(LIBDIR)/
	ldconfig -n -v $(LIBDIR)
	make exeinstall
	@echo
	@echo Install done!

exeinstall: $(BLDDIR)/*.out
	cp $< $(EXEDIR)/$<

hacasm: $(SRCDIR)/hacasm.c hacal_asmlib.so
	$(CC) -o $(BLDDIR)/$@ $< build/hacal_asmlib.so
	chmod +x $(BLDDIR)/$@

%.so: $(SRCDIR)/%.c
	$(CC) -shared -o $(BLDDIR)/$@ -fPIC $<

%.h: $(SRCDIR)/%.c
	cp $< $(BLDDIR)/$@

%/:
	mkdir $@
