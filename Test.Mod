MODULE ORS;

IMPORT Out, Files;

CONST

  K1 = 3;
  K2 = 4;
  K3 = "Five";

TYPE

  T1 = INTEGER;
  T2* = SET;
  T3 = ARRAY 1 OF T2;
  T4 = RECORD a, b*, c :CHAR END;
  T5 = RECORD (T4) d:REAL; e:ARRAY K2 OF CHAR END;
  T6 = POINTER TO T5;
  T7 = PROCEDURE(a, b :T1; VAR c, d:T2): BYTE;

VAR
  v1, v2 :INTEGER;
  v3 :T2;
  v4 :T5;

PROCEDURE Wowza*(i, j :INTEGER);
VAR
  zzz :INTEGER;
  p :T6;
BEGIN
  i := j + 1;
  Wowza(p);
  p(T5).a.b := 4
END Wowza;

PROCEDURE Moo*(k, l :ARRAY OF INTEGER);
BEGIN
  k := l-1;
END Moo;

END ORS.
