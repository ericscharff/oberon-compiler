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

PROCEDURE TestFor;
VAR
  lcv :INTEGER;
BEGIN
  FOR lcv := 1 TO 25 BY 2*1 DO
    Out.Int(z3.d)
  END;
  FOR lcv := 1 TO 25 DO
    Out.Int(z3.d)
  END
END TestFor;

PROCEDURE TestBinop;
VAR
  s1, s2, s3 :SET;
  str, str2 :ARRAY 25 OF CHAR;
  b :BOOLEAN;
BEGIN
  s1 := {2} + {3};
  s2 := {1, 3, 5};
  s3 := {2, 4, 6};
  b := 3 IN s2;
  s1 := s2 + s3;
  s1 := s2 - s3;
  s1 := s2 * s3;
  s1 := s2 / s3;
  str := "BETA";
  str2 := "BETA";
  b := "ALPHA" < str;
  b := "Aloha" >= str;
  b := "GAMMA" > str;
  b := str = str2;
  b := s1 # s2;
  b := s1 = s2;
  b := str # "Z"
END TestBinop;

PROCEDURE TestFact; END TestFact;

PROCEDURE TestMisc;

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
  TestFor;
  TestBinop;
  INC(z.a, 3);
  NEW(pz3);
  pz := pz3;
  pz3.a := 35;
  z := z3;
  ASSERT(pz = pz);
  c := 041X;
  ac := "WOWZA";
  b := 1 + 1;
  pOne := FactIter;
  Out.Int(pOne(8));
  PlusOne(z3)
END TestMisc;

PROCEDURE TestSet;
VAR
  i, j :INTEGER;
  st   :SET;
BEGIN
  st := {1, 2, 3};
  ASSERT(st = {1, 2, 3});
  i := 4;
  st := st + {i};
  ASSERT(st = {1 .. 4});
  j := 8;
  st := {i .. j};
  ASSERT(st = {4 .. 8});
END TestSet;

PROCEDURE TestCase;
VAR
  i :INTEGER;
  c :CHAR;
  r :INTEGER;
  s :CHAR;
BEGIN
  FOR i := -1 TO 10 DO
    CASE i OF
        0: r := 100;
      | 1: r := 200;
      | 2: r := 300; Out.Int(r)
      | 3, 4, 5: r := 400;
      | 6 .. 10: r := 500
    END;
  END;
  FOR i := 65 TO 65+26 DO
    c := CHR(i);
    CASE c OF
        "A": s := "a"
      | "E": s := "e"
      | "I", "O", "U": s := "z"
      | "J" .. "M": s := "Z"
    END
  END
END TestCase;

BEGIN
  TestBinop;
  TestFact;
  TestSet;
  TestMisc;
  TestCase
END FibFact.
