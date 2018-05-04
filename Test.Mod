MODULE Test;

IMPORT Base1, ZZ := Base2, Base3;

TYPE
  FromBase1 = Base1.A;
  FromBase2 = ZZ.A;
  FromBase2b = ZZ.B;
  FromBase3 = Base3.Thing;

END Test.
