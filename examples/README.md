# Examples

This directory contains sample programs that demonstrate the Oberon language and
extra features of the compiler. More examples (in the form of regression tests)
can be found in the `tests` directory.

## Apple1

`Apple1.ob` uses the 6502 emulator core (forked from the copy in the `tests/`
directory) to provide a working simulation of an Apple 1 computer. To build the
emulator, use

```
../build/compile -extra_runtime console.c Apple1.ob
```

The reason for the native library is to set terminal properties using termios.
The Apple 1 computer is fairly minimal, but it needs a non-blocking way to read
raw characters. The console support disables canonical mode and echo mode which
should be supported by POSIX systems. See [Apple1.md](Apple1.md) for
instructions on using the emulator.

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
output to stdout. e.g.

```
../build/compile PrettyPrint.ob
../built/out.prg Cairo.ob > Cairo-formatted.ob
```
