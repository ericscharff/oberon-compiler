MODULE FibFact;

IMPORT Out;

CONST
  Seven = 7;

TYPE
  R = RECORD a, b :INTEGER END;
  R2 = RECORD (R) c :INTEGER END;
  R3 = RECORD (R2) d :INTEGER END;
  PR = POINTER TO R;
  P3 = POINTER TO R3;
  TakeOneReturnOne = PROCEDURE (thing :INTEGER):INTEGER;
VAR
  lcv :INTEGER;
  z :R;
  z2 :R2;
  z3 :R3;
  pz :PR;
  pz3 :P3;
  c :CHAR;
  ac :ARRAY 25 OF CHAR;
  b :BYTE;
  pOne :TakeOneReturnOne;

PROCEDURE FactIter*(n :INTEGER) :INTEGER;
VAR
  i, r :INTEGER;
BEGIN
  Out.Str("FactIter");
  r := 1;
  i := 1;
  WHILE i <= n DO
    r := r * i;
    INC(i)
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
    DEC(n)
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

PROCEDURE Plus(VAR zzz :INTEGER); BEGIN zzz := zzz + 1 END Plus;

PROCEDURE PlusOne(VAR x :R); BEGIN Plus(x.a) END PlusOne;

PROCEDURE Tootle;
VAR
  lcv :INTEGER;
BEGIN
  FOR lcv := 1 TO 25 BY 2*1 DO
    Out.Int(z3.d)
  END;
  FOR lcv := 1 TO 25 DO
    Out.Int(z3.d)
  END
END Tootle;

BEGIN
  FactIter(7);
  FactRec(Seven);
  FibIter(12);
  FibRec(12);
  z.a := 10;
  z.b := -z.a + 1;
  PlusOne(z);
  z2.a := 101;
  z3.a := 101;
  z3.b := 101;
  z3.c := 101;
  z3.d := 101;
  FLT(z3.d);
  Tootle;
  INC(z.a, 3);
  NEW(pz3);
  pz := pz3;
  pz3.a := 35;
  z := z3;
  c := 041X;
  ac := "WOWZA";
  b := 1 + 1;
  pOne := FactIter;
  Out.Int(pOne(8));
  PlusOne(z3)
END FibFact.
