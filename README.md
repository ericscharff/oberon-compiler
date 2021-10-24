# Simple Oberon compiler

This is a simple compiler for the Oberon-07 programming language. In its current
state, it translates Oberon to C, so technically it is a transpiler. The
eventual goal is for the compiler to emit code for some (probably virtual)
machine.

There are actually two compilers in this repository. The first is a
bootstrapping compiler (in the `c_bootstrap` directory), which is written in C.
This is actively maintained (if there are bugs) but mostly exists to compile the
main compiler, which is written in Oberon. This compiler is self-hosting (it can
compile itself).

# Usage

Running `make` will build the bootstrap compiler, and then the main compiler,
which is placed in the `build` directory. Once created, this compiler can be
used to compile the oberon-based compiler. The oberon compiler then compiles
itself, so as a form of a "triple test" one can compare the generated C code to
ensure that the compiler is still generating correct code.

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
```

The compiler will read and compile all modules upon which the main class
depends. It then performs tree-shaking, so that the resulting C file will
contain only functions used, and necessary pieces of imported modules. The
resulting C code should be relatively clean and portable. If the code uses the
type inclusion feature (e.g. `p IS Circle`), then the compiler generates C++
code because it uses RTTI to do the type inclusion test. If type tests are
never used in the code, straight C may be used. C++ code may be desirable
in some contexts anyway, in case you want to interface with other C++ code
(the type extenstions in Oberon correspond directly to C++ subclasses).

The compile shell script accepts two flags, `-cpp` to generate C++ code (see
above), and `-bounds` to generate bounds checks (to assert that any array
references are within the bounds of the array.)

# Known issues

*   The bootstrap compiler in C isn't wonderful. However, it only exists to make
    the compiler written in Oberon a reality.
*   There are some stubs that resemble standard Oakwood modules, like The module
    Texts and Files. However, these don't really work like their Project Oberon
    counterparts (yet).
