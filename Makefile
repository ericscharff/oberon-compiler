CC=gcc
CFLAGS=-g -Wall -Wextra -Wpedantic $(shell pkg-config glib-2.0 --cflags)
LIBS=$(shell pkg-config glib-2.0 --libs)

run: oberon
	./oberon

oberon: out.c runtime.c
	$(CC) -g -Wall -Wextra -Wpedantic -o $(@) out.c

out.c: oberon0 AST.ob Compiler.ob CCodegen.ob Decls.ob Lex.ob Parse.ob
	./oberon0

oberon0: main.c ast.c buf.c lex.c parse.c type.c resolve.c c_codegen.c
	$(CC) $(CFLAGS) -o $(@) main.c $(LIBS)

clean:
	rm -rf oberon oberon0 out.c out.prg *.dSYM
