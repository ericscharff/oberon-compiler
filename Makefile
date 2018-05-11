CC=gcc
CFLAGS=-g -Wall -Wextra -Wpedantic $(shell pkg-config glib-2.0 --cflags)
LIBS=$(shell pkg-config glib-2.0 --libs)

run: oberon builtin.defs Test.Mod
	./oberon

oberon: main.c ast.c buf.c lex.c parse.c type.c resolve.c
	$(CC) $(CFLAGS) -o $(@) main.c $(LIBS)

clean:
	rm oberon
