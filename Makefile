CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic $(shell pkg-config glib-2.0 --cflags)
LIBS=$(shell pkg-config glib-2.0 --libs)

run: oberon
	./oberon

oberon: main.c lex.c
	$(CC) $(CFLAGS) -o $(@) main.c $(LIBS)

clean:
	rm oberon
