MODULE Lex;

CONST
  NumBuckets = 4096;
  PoolSize   = 64 * 1024;

TYPE
  PoolIndex*  = INTEGER;
  StringPool* = RECORD
    buf     :ARRAY PoolSize OF CHAR;
    last    :PoolIndex;
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

PROCEDURE StringInternRange(VAR sp :StringPool; s :ARRAY OF CHAR; offset, length :INTEGER) :PoolIndex;
VAR
  i    :INTEGER;
  hash :INTEGER;
  b    :INTEGER;
BEGIN
  ASSERT(sp.last + length < PoolSize);
  (* Copy and compute hash at the same time *)
  hash := 811C9DC5H;
  FOR i := 0 TO length DO
    hash := hash XOR ORD(s[offset + i]);
    hash := hash * 16777619;
    sp.buf[sp.last + i] := s[offset + i]
  END;
  hash := hash * 85EBCA6BH;
  hash := hash XOR (hash DIV 65536);
  b := hash MOD NumBuckets;
  RETURN b
END StringInternRange;

PROCEDURE StringIntern(VAR sp :StringPool; s :ARRAY OF CHAR) :PoolIndex;
BEGIN
  RETURN StringInternRange(sp, s, 0, StringLen(s))
END StringIntern;

PROCEDURE PoolTest;
VAR
  sp :StringPool;
  s  :ARRAY 25 OF CHAR;
BEGIN
  PoolInit(sp);
  ASSERT(11 = StringLen("Hello world"));
  s := "Hello world";
  ASSERT(11 = StringLen(s));
  ASSERT(StringIntern(sp, s) = 103);
  s := "Yello world";
  ASSERT(StringIntern(sp, s) = 1340)
END PoolTest;

BEGIN
  PoolTest
END Lex.
