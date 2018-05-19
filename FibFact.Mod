MODULE FibFact;

IMPORT Out;

CONST
  Seven = 7;

TYPE
  I = INTEGER;
  A = ARRAY 10 OF I;
  B = ARRAY 5, 15 OF REAL;
  P = PROCEDURE (a, b, c :INTEGER):REAL;
  R1 = RECORD f1 :INTEGER END;
  R2 = RECORD p :POINTER TO R1; a :INTEGER END;

VAR
  v1 :I;
  v2 :A;
  v3 :B;
  v4 :ARRAY 10 OF INTEGER;
  v5 :P;
  v6 :PROCEDURE;
  v7 :R2;

PROCEDURE FactIter*(n :INTEGER) :INTEGER;
VAR
  i, r :INTEGER;
BEGIN
  Out.Str("FactIter");
  r := 1;
  i := 1;
  WHILE i <= n DO
    r := r * i;
    i := i + 1
  END;
  RETURN r
END FactIter;

PROCEDURE FactRec*(n :INTEGER) :INTEGER;
VAR r :INTEGER;
BEGIN
  Out.Str("FactRec");
  IF n <= 1 THEN
    r := 1
  ELSE
    r := n * FactRec(n-1)
  END;
  RETURN r
END FactRec;

PROCEDURE FibIter*(n :INTEGER) :INTEGER;
VAR
  prev, newPrev, fib :INTEGER;
BEGIN
  Out.Str("FibIter");
  prev := 1;
  fib := 1;
  WHILE n > 1 DO
    newPrev := fib;
    fib := fib + prev;
    prev := newPrev;
    n := n - 1
  END
  RETURN fib
END FibIter;

PROCEDURE FibRec*(n :INTEGER) :INTEGER;
VAR r :INTEGER;
BEGIN
  Out.Str("FibRec");
  IF n < 2 THEN
    r := 1
  ELSE
    r := FibRec(n-1) + FibRec(n-2)
  END
  RETURN r
END FibRec;

BEGIN
  FactIter(7);
  FactRec(Seven);
  FibIter(12);
  FibRec(12);
  v1 := 289;
  v2[3] := v1;
  v3[11, 12] := 293.3;
  v4[0] := 10;
  v5 := NIL;
  v6 := NIL;
  v7.a := 0;
  v7.p.f1 := 0;
END FibFact.
