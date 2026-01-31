The following tests are in the disabled directory to avoid running them
automatically.

## LangExtensions.ob

This tests the Oberon language extensions, like buffers. It can be tested
with the C transpiler, but currently not with the RISC compiler.

Usage:

```bash
$ ../../build/compile LangExtensions.ob
$ ../../build/LangExtensions
81
81
5	10	15	20	25	30	35	40	45	50	55	60	65	70	75	80	85	90	95	100
5	10	15	20	25	30	35	40	45	50	55	60	65	70	75	80	85	90	95	100
5	10	15	20	25	30	35	40	45	50	55	60	65	70	75	80	85	90	95	100
5040
10946
```

## NativeC.ob

This tests the integration between C and Oberon, like native functions and
calling to/from C code. It therefore makes sense with the C transpiler and not
with the RISC code generator. To run, the implementations of the C functions
need to be passed to the build process:

```bash
$ ../../build/compile -extra_runtime native_c.c NativeC.ob
$ ../../build/NativeC

About to call callback with i=11.
Called back from native with i=11
NativeCallback completed
Native code called, buf.nativeQ = 81, nativeR = 82.
```

## RunCompiler.ob

This runs the internal tests of the compiler. Strictly speaking, this isn't
espeically interesting, since the C version does this whenever `make regen` is
called. However, the RISC code can also run the compiler, but the RISC virtual
machine needs extra memory:

```bash
# Give the RISC VM extra memory
$ MEM_SIZE=362144 ../../build/rcompile RunCompiler.ob

# Go to the home directory (so the compiler can find it's own source)
$ cd ../..

# Run the RISC version of the compiler
$ ./build/RunCompiler
<string>:1:3:Hex digit must be followed by H or X
<string>:1:5:Character constant <string>:1:1:Invalid character
<string>:1:1:Unterminated string
<string>:1:1:Invalid character
<string>:1:1:Unterminated comment
<string>:1:1:BEGIN already defined
<string>:1:1:BITAND already defined
<string>:1:1:BITOR already defined
<string>:1:1:BITXOR already defined
<string>:1:1:ELSE undefined
PASS: String pool test
256 > 255
PASS: Lexer test
PASS: Decls test
PASS: Parser test
```
