CC=gcc
BUILDDIR=build
CFLAGS=-g -Wall -Wextra -Wpedantic $(shell pkg-config glib-2.0 --cflags)
LIBS=$(shell pkg-config glib-2.0 --libs)

run: $(BUILDDIR)/oberon
	$(BUILDDIR)/oberon

$(BUILDDIR)/oberon: $(BUILDDIR)/oberon1
	$(BUILDDIR)/oberon1 > out.c
	$(CC) -g -Wall -Wextra -Wpedantic -o $(@) $(BUILDDIR)/out.c

$(BUILDDIR)/oberon1: $(BUILDDIR)/out.c runtime.c
	$(CC) -g -Wall -Wextra -Wpedantic -o $(@) $(BUILDDIR)/out.c

$(BUILDDIR)/out.c: $(BUILDDIR)/oberon0 AST.ob Compiler.ob CCodegen.ob Decls.ob Lex.ob Parse.ob
	$(BUILDDIR)/oberon0
	mv out.c $(BUILDDIR)

$(BUILDDIR)/oberon0: main.c ast.c buf.c lex.c parse.c type.c resolve.c c_codegen.c
	@mkdir $(BUILDDIR)
	cp runtime.c $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(@) main.c $(LIBS)

clean:
	rm -rf build
