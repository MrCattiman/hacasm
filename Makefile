CC     = gcc

SRCDIR = src
BLDDIR = build

all: hacal_asmlib.so

%.out: $(SRCDIR)/%.c
	$(CC) $< $(BLDDIR)/$@

%.so: $(SRCDIR)/%.c
	$(CC) -shared -o $(BLDDIR)/$@ -fPIC $<
