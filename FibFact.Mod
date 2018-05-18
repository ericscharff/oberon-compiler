MODULE FibFact;

CONST
  Seven = 7;

PROCEDURE Out(s :ARRAY OF CHAR); END Out;

PROCEDURE FactIter*(n :INTEGER) :INTEGER;
VAR
  i, r :INTEGER;
BEGIN
  Out("FactIter");
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
  Out("FactRec");
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
  Out("FibIter");
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
  Out("FibRec");
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
END FibFact.
