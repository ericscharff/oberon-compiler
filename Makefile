CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -g

run: oberon
	./oberon

oberon: main.c lex.c
	$(CC) $(CFLAGS) -o $(@) main.c

clean:
	rm oberon
