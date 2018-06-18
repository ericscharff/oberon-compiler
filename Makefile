CC=gcc
BUILDDIR=build
CFLAGS=-g -Wall -Wextra -Wpedantic $(shell pkg-config glib-2.0 --cflags)
LIBS=$(shell pkg-config glib-2.0 --libs)

BOOTSTRAP_SRCS=$(wildcard c_bootstrap/*.c)
COMPILER_SRCS=$(wildcard compiler/*.ob)

$(BUILDDIR)/oberon: $(BUILDDIR)/oberon1 $(COMPILER_SRCS)
	cd compiler; ../$(BUILDDIR)/oberon1 Compiler.ob > ../$(BUILDDIR)/compiler.c
	$(CC) -g -Wall -Wextra -Wpedantic -o $(@) $(BUILDDIR)/compiler.c
	cd compiler; ../$(BUILDDIR)/compile Compiler.ob
	mv $(BUILDDIR)/out.prg $(BUILDDIR)/oberon

$(BUILDDIR)/oberon1: $(BUILDDIR)/oberon0 $(COMPILER_SRCS)
	OBERONPATH=c_bootstrap:compiler $(BUILDDIR)/oberon0
	mv out.c $(BUILDDIR)
	$(CC) -g -Wall -Wextra -Wpedantic $(BUILDDIR)/out.c -o $(@)

$(BUILDDIR)/oberon0: $(BOOTSTRAP_SRCS)
	mkdir -p $(BUILDDIR)
	cp compiler/runtime.c compiler/compile $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(@) -Ic_bootstrap c_bootstrap/main.c $(LIBS)

clean:
	rm -rf build
