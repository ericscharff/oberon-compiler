BUILDDIR=build
CFLAGS=-g -std=c17 -Wall -Wextra -Wpedantic

BOOTSTRAP_SRCS=$(wildcard c_bootstrap/*.c)
COMPILER_SRCS=$(wildcard compiler/*.ob) compiler/runtime.c

$(BUILDDIR)/oberonr: $(BUILDDIR)/oberon $(COMPILER_SRCS)
	cd compiler; ../$(BUILDDIR)/oberon RCompiler.ob > ../$(BUILDDIR)/rcompiler.c
	$(CC) $(CFLAGS) -o $(@) $(BUILDDIR)/rcompiler.c

$(BUILDDIR)/oberon: $(BUILDDIR)/oberon1 $(COMPILER_SRCS)
	cd compiler; ../$(BUILDDIR)/oberon1 Compiler.ob > ../$(BUILDDIR)/compiler.c
	$(CC) $(CFLAGS) -o $(@) $(BUILDDIR)/compiler.c
	cd compiler; ../$(BUILDDIR)/compile Compiler.ob
	mv $(BUILDDIR)/out.prg $(BUILDDIR)/oberon

$(BUILDDIR)/oberon1: $(BUILDDIR)/oberon0 $(COMPILER_SRCS)
	cd $(BUILDDIR); ./oberon0
	$(CC) $(CFLAGS) $(BUILDDIR)/out.c -o $(@)

$(BUILDDIR)/oberon0: $(BOOTSTRAP_SRCS) $(COMPILER_SRCS)
	mkdir -p $(BUILDDIR)
	cp c_bootstrap/*.ob $(BUILDDIR)
	cp c_bootstrap/builtin.defs $(BUILDDIR)
	cp compiler/*.ob $(BUILDDIR)
	cp compiler/runtime.c compiler/compile compiler/rcompile $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(@) c_bootstrap/main.c

clean:
	rm -rf build

test: $(BUILDDIR)/oberonr
	cd tests && ./run-tests.sh

compiler-test: $(BUILDDIR)/oberonr
	cd tests && ./compiler-test.sh
