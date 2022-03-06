# Examples

This directory contains sample programs that demonstrate the Oberon language and
extra features of the compiler. More examples (in the form of regression tests)
can be found in the `tests` directory.

## Cairo

`CairoTest.ob` uses the NATIVE features of the compiler to integrate with the
Cairo programming library. This depends on native method defined in `Cairo.ob`
and implemented in `cairo.c`.

To build, the extra C library must be passed to the compile build script, e.g.

```
EXTRA_CFLAGS=$(pkg-config --cflags --libs cairo) ../build/compile \
  -extra_runtime cairo.c CairoTest.ob
```

The resulting program (`../build/out.prg`) generates a few PNG images.

## PrettyPrint

`PrettyPrint.ob` is a rudimentary Oberon pretty printer, It accepts an Oberon
file as a command line argument, parses it, and outputs the pretty printed
outupt to stdout. e.g.

```
../build/compile PrettyPrint.ob
../built/out.prg Cairo.ob > Cairo-formatted.ob
```
