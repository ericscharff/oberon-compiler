# Extensions to Oberon-07

## Bitwise logical operations

The compiler accepts three binary operations, `BITAND`, `BITOR`, and `BITXOR`
which behave much like `&`, `|`, and `^' in C - they take two INTEGERS and
return an INTEGER that represent performing bitwise Boolean operations on the
two integers (e.g., bit 7 combines bit 7 of each operand).

## Lowercase keywords

Most of the reserved words in Oberon (`MODULE`, `PROCEDURE`, etc.) can be
entered in lower case. Note, however, that identifiers are still case sensitive,
so `begin` and `BEGIN` both work, but `procedureName` and `ProcedureName` do
not. e.g.

```
module Test; import Out; begin Out.Str("Hello"): end Test.
```

Is valid code. This can be controlled by the `ignoreKeywordCase` global variable
in [Lex.ob](../compiler/Lex.ob).

When enabled, the builtin types and identifiers `nil`, `integer`, `real`,
`boolean`, `char`, and `set` are also allowed,

## Inline RETURN

In Oberon-07, `RETURN` is a statement that _must_ appear at the end of a
`PROCEDURE`. With inline RETURN, RETURN is a statement that can appear anywhere
within a procedure, and returns immediately from that procedure, e.g.

```
PROCEDURE UseX(x: INTEGER): INTEGER;
BEGIN
  IF x < 0 THEN RETURN -1 END;
  IF x > 10 THEN RETURN 1000 END;
  (* Code can guarantee x >= 0 and x <= 10 if it wants *)
  RETURN x + 1
END;
```

Note that a `RETURN` is still required at the end of a procedure, even if it can
not possibly be reached, e.g.

```
PROCEDURE UseX(x: INTEGER): INTEGER;
BEGIN
  IF x < 0 THEN RETURN -1 END;
  IF x >= 0 THEN RETURN 1 END;
  (* Not reachable, but required for semantic compatability *)
  RETURN x + 1
END;
```

`RETURN` is not allowed from a `PROCEDURE` that does not return a value.

## Native record fields.

A record field may be marked with the `NATIVE` keyword, e.g.

```
MODULE Net;
TYPE CSocket = RECORD _sock :NATIVE INTEGER; END;
END Net.
```

The native keyword has no effect in native code generation, but when performing
C Code generation, this creates a "native field." The generated C code for this
record looks like this:

```
typedef struct Net_CSocket {
  Net_CSocket_Native _sock;
} Net_CSocket;
```

It is assumed that the C code (in the preamble) declares the type
`Net_CSocket_Native`.

The intention is that if Oberon code needs to communicate with Native C code,
and that native C code needs access to state that needs to be maintained and
persisted with the record, this is a way to perform this.

Native fields should not be referenced in code, because when the C code is
generated, it will ultimately lead to a C compile time error (if the C type is
incompatible with the field type.)

NATIVE procedures have a similar syntax:

```
NATIVE (-101) DrawLine(x1, y1, x2, y2 :INTEGER);
```

The number in parenthesis is required, but is ignored by the C code generator.
It is important for the RISC code generator, because it allows generation of
"trap" instructions. Effectively, it allows the RISC code generator to emit
calls as if they were real procedures, e.g.,

```
<args passed in registers, first arg in R0>
BL -101
```

Then, the RISC interpreter can treat jumps to negative PC values as functions
that are implemented by the interpreter. This makes it easy for both C and RISC
code to use the standard modules like Out.

Note that the compiler does no checking of the value, but it is implied that the
trap numbers are negative, and that they are essentially globally unique (this
makes sense in the RISC implementation, but is not enforced by the compiler.)

If a native procedure needs to return a value, the value should be placed in R0.

## Inline variables

Variables may be defined within a statement block, e.g.

```
VAR x := 12;
```

The type of the variable is determined by the right hand side of the assignment.

Note that these variables are scoped to the entire function, unlike languages
like C where they are scoped to the block.

Variable length arrays (a.k.a. buffers)

A new type of array is allowed

```
ARRAY * OF <Type>
```

This represents a variable length array, similar to an ArrayList in other
languages.

A buffer may be passed anywhere an open array is expected, and LEN(buffer) works
just as it would with an open array. Similarly, buffer elements are referenced
just like arrays - buf[2] := ...

Before a buffer can be used, the user must call `NEW_ARRAY` on the buffer.
INIT_ARRAY takes an additional argument, which is the initial capacity. This is
how many elements can be added to the buffer before it must be grown (with a new
call to malloc/new). Note that this sets capacity, not length, which starts
at 0.

A buffer initially has 0 items. New elements may be added to the buffer with the
builtin PUSH. PUSH takes one or two arguments. The first argument is the buffer,
which must be assignable. The second (optional) argument is the thing that
should be put in the new buffer location.

Example:

```
VAR
  b :ARRAY * OF INTERGER;
  i :INTEGER:
BEGIN
  NEW_ARRAY(b, 5);
  PUSH(b, 1);
  PUSH(b, 2);
  PUSH(b, 3);
  i := 0;
  WHILE i < LEN(b) DO
    Out.Int(b[i]); Out.Ln;
    INC(i)
  END
END
```

would print 1, 2, 3
