MODULE Test;

IMPORT Base1, ZZ := Base2, Base3;

CONST
  K1 = 1;
  K2 = 2;
  K3* = K1*K1 + K2*K2;

TYPE
  FromBase1 = Base1.A;
  FromBase2 = ZZ.A;
  FromBase2b = ZZ.B;
  FromBase3 = Base3.Thing;
  A1 = ARRAY 10 OF INTEGER;
  A2 = ARRAY 1, 2+3, 4*5 OF CHAR;

VAR
  a :INTEGER;
  s :SET;
  r1 :RECORD a :INTEGER END;
  r2 :Base1.Base1Rec;

PROCEDURE DoIt*(a, b, c :INTEGER);
BEGIN
  a := b + c
END DoIt;

BEGIN
  a := 12;
  a := 3 + 2;
  IF a > 10 THEN
    a := a*3
  ELSIF a > 20 THEN
    a := a*4
  ELSIF a > 30 THEN
    a := a*5
  ELSE
    WHILE a > 0 DO DEC(a) END
  END;
  WHILE a > 5 DO
    a := a + 1;
    WHILE a < 0 DO INC(a, 2, 3) END;
    a := a*a + a + a
  END;
  a := INC(a);
  r1.a := 3;
  r2.b := 4;
  s := {2, 3, 4..10, 12}
END Test.
