out.prg: out.c runtime.c
	$(CC) -o out.prg out.c $(shell pkg-config --cflags --libs cairo)

runtime.c: ../compiler/runtime.c cairo.c
	cat ../compiler/runtime.c cairo.c > runtime.c

out.c: Cairo.ob CairoTest.ob
	cp *.ob ../build
	../build/oberon CairoTest.ob > out.c

clean:
	rm -f runtime.c out.c out.prg *.png
