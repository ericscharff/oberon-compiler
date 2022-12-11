BUILDDIR=build
CFLAGS=-g -std=c17 -Wall -Wextra -Wpedantic

COMPILER_SRCS=$(wildcard compiler/*.ob) compiler/runtime.c

$(BUILDDIR)/oberonr: $(BUILDDIR)/oberon $(COMPILER_SRCS)
	cd compiler; ../$(BUILDDIR)/oberon RCompiler.ob > ../$(BUILDDIR)/rcompiler.c
	$(CC) $(CFLAGS) -o $(@) $(BUILDDIR)/rcompiler.c

$(BUILDDIR)/oberon: $(BUILDDIR)/oberon1 $(COMPILER_SRCS)
	cd compiler; ../$(BUILDDIR)/oberon1 Compiler.ob > ../$(BUILDDIR)/compiler.c
	$(CC) $(CFLAGS) -o $(@) -Icompiler $(BUILDDIR)/compiler.c
	cd compiler; ../$(BUILDDIR)/compile Compiler.ob
	mv $(BUILDDIR)/out.prg $(BUILDDIR)/oberon

$(BUILDDIR)/oberon1: $(BUILDDIR)/oberon0 $(COMPILER_SRCS)
	cd compiler; ../$(BUILDDIR)/oberon0 Compiler.ob > ../$(BUILDDIR)/compiler.c
	$(CC) $(CFLAGS) -o $(@) -Icompiler $(BUILDDIR)/compiler.c

$(BUILDDIR)/oberon0: risc_runner/runner.c risc_bootstrap/risc_code.txt
	mkdir $(BUILDDIR)
	cp compiler/* $(BUILDDIR)
	$(CC) $(CFLAGS) -DMAX_MEM=624288 -Irisc_bootstrap -o $(@) risc_runner/runner.c

clean:
	rm -rf build

test: $(BUILDDIR)/oberonr
	cd tests/errors && ./run-fail-tests.sh
	cd tests && ./run-tests.sh

compiler-test: $(BUILDDIR)/oberonr
	cd tests && ./compiler-test.sh
