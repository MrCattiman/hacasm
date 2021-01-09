CC     = gcc

SRCDIR = src
BLDDIR = build

all: assemble.out

%.out: $(SRCDIR)/%.c
	$(CC) $< $(BLDDIR)/$@

%.so: $(SRCDIR)/%.c
	$(CC) -shared -o $(BLDDIR)/$@ -fPIC $<
