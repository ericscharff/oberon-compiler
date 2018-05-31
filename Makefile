CC=gcc
CFLAGS=-g -Wall -Wextra -Wpedantic $(shell pkg-config glib-2.0 --cflags)
LIBS=$(shell pkg-config glib-2.0 --libs)

run: out.prg
	./out.prg

out.prg: out.c runtime.c
	$(CC) -g -Wall -Wextra -Wpedantic -o $(@) out.c

out.c: oberon Parse.ob
	./oberon

oberon: main.c ast.c buf.c lex.c parse.c type.c resolve.c c_codegen.c
	$(CC) $(CFLAGS) -o $(@) main.c $(LIBS)

clean:
	rm -rf oberon out.c out.prg *.dSYM
