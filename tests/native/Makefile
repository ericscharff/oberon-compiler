out.prg: out.c runtime.c cairo.o
	$(CC) $(shell pkg-config --cflags --libs cairo) -o out.prg out.c cairo.o

runtime.c: ../../compiler/runtime.c cairo.c cairo_native.h
	cat ../../compiler/runtime.c cairo_native.h > runtime.c

out.c: Cairo.ob CairoTest.ob
	cp *.ob ../../build
	../../build/oberon CairoTest.ob > out.c

cairo.o: cairo.c
	$(CC) -c $(shell pkg-config --cflags --libs cairo) cairo.c

clean:
	rm -f runtime.c out.c out.prg cairo.o *.png
