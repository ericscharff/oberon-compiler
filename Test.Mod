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

END Test.
