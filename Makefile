CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic

run: oberon
	./oberon

oberon: main.c lex.c
	$(CC) $(CFLAGS) -o $(@) main.c

clean:
	rm oberon
