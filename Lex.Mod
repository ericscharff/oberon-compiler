MODULE Lex;

CONST
  NumBuckets = 4096;
  PoolSize = 64 * 1024;

TYPE
  PoolIndex* = INTEGER;
  StringPool* = RECORD
    buf :ARRAY PoolSize OF CHAR;
    last :PoolIndex;
    buckets :ARRAY NumBuckets OF PoolIndex;
  END;

PROCEDURE PoolInit(VAR sp :StringPool);
VAR
  i :INTEGER;
BEGIN
  sp.last := 0;
  FOR i := 0 TO NumBuckets-1 DO
    sp.buckets[i] := -1
  END
END PoolInit;

PROCEDURE StringLen(s :ARRAY OF CHAR) :INTEGER;
VAR
  l :INTEGER;
BEGIN
  l := 0;
  WHILE s[l] # 0X DO INC(l) END
  RETURN l
END StringLen;

PROCEDURE PoolTest;
VAR
  sp :StringPool;
BEGIN
  PoolInit(sp);
  ASSERT(11 = StringLen("Hello world"))
END PoolTest;

BEGIN
  PoolTest
END Lex.
