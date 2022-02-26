../build/out.prg: ../build/out.c ../build/runtime.c
	$(CC) -o ../build/out.prg ../build/out.c $(shell pkg-config --cflags --libs cairo)

../build/runtime.c: ../compiler/runtime.c cairo.c
	cat ../compiler/runtime.c cairo.c > ../build/runtime.c

../build/out.c: Cairo.ob CairoTest.ob
	cp *.ob ../build
	../build/oberon CairoTest.ob > ../build/out.c
