# Simple Oberon compiler

This is a collection of compilers for the Oberon-07 programming language. It is
actually three different compilers:

*   A *bootstrapping compiler,* written in C. This C program takes Oberon source
    and transpiles it to C.
*   A *C code generator,* written in Oberon. The bootstrapping compiler was used
    to get the Oberon compiler up and running. This C transpiler takes Oberon
    code and translates it into C or C++. The generated code is fairly readable,
    and can interface seamlessly with C code.
*   A *RISC code generator,* written in Oberon. This is a "true" compiler in the
    sense that it takes Oberon source and produces a binary for a simple RISC
    machine. The binary can be used in conjunction with a C based emulator for
    this RISC processor.

The two Oberon compilers share most of their code, with the major difference
being the code generators (either producing C or producing RISC code.)

The compilers written in Oberon are self hosting - the Oberon compiler can
compile itself, and produce either C code (or a RISC) binary for a compiler that
can also compile itself. Theoretically, the C bootstrap compiler is no longer
necessary, since it would be possible to start "from scratch" from the generated
C code produced by Oberon of itself. The C bootstrap compiler isn't nearly as
well tested, and probably lacks features. It remains though to bootstrap the
Oberon compiler, as well as a historical artifact that was critical in getting a
self-hosting compiler. Most new features are added only to the Oberon
implementation.

Though the RISC binary could exclusively be used, the C virtual machine is not
particularly fast, and the RISC code is not optimized. Thus, typically the C
transpiled compiler is what is used for development.

The two Oberon compilers should adhere to and implement all of the features of
the Oberon-07 language. Both also contain some optional extensions to Oberon,
described in [doc/language-extensions.md](doc/language-extensions.md). Some
experimental new features include lower case keywords and buffers (variable
sized arrays, like Vectors/ArrayLists in other languages.)

# Usage

## Building the compiler

Running `make` will build the bootstrap compiler, and then the main compiler,
which is placed in the `build` directory. Once created, this compiler can be
used to compile the Oberon-based compiler. The Oberon compiler then compiles
itself, so as a form of a "triple test" one can compare the generated C code to
ensure that the compiler is still generating correct code. The test suite can be
run with `make test` and the triple-test with `make compiler-test`.

## Running the compiler

Once bootstrapped, the `build` directory contains a shell script called
`compile`. This shell script can be used to compile examples. For example:

```bash
# Build the compiler
$ make

# Build an example
$ cd tests
$ ../build/compile FibFact.ob
# Transpiles to ../build/out.c and then compiles to ../build/out.prg
# Run the example
$ ../build/out.prg
5040
10946

# or run all the tests
$ ./run-tests.sh

# Self hosting test: Use the compiler to build a RISC binary of the compiler,
# and then use the RISC binary / interpreter to compile itself
$ ./compiler-test.sh
```

The compiler will read and compile all modules upon which the main class
depends. It then performs tree-shaking, so that the resulting generated code
contain only functions and global variables that are actually reference. This
means that code can depend on arbitrarily large modules, but only used
functionality will be included in the resulting output.

When generating C code, the resulting code should be relatively clean and
portable. C++ generated code utilizes C++ features (RECORDS become classes, RTTI
is used to perform tests like type inclusion (e.g., "p IS Circle"). When
generating C code, the object oriented features are simulated through
appropriately inserted C code, and type descriptors that represent the type
hierarchy.

## Compiler flags

The compile shell script accepts two flags, `-cpp` to generate C++ code (see
above), and `-bounds` to generate bounds checks (to assert that any array
references are within the bounds of the array.)

# Known issues

*   The bootstrap compiler in C isn't wonderful. However, it only exists to make
    the compiler written in Oberon a reality.
*   There are some stubs that resemble standard Oakwood modules, like The module
    Texts and Files. However, these don't really work like their Project Oberon
    counterparts.
*   Not all language extensions are supported by the RISC code generator (in
    particular, buffers).
