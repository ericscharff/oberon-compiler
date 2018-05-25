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

PROCEDURE StrEq(a :ARRAY OF CHAR; ai :INTEGER; b :ARRAY OF CHAR; bi :INTEGER) :BOOLEAN;
VAR
  same :BOOLEAN;
BEGIN
  WHILE (a[ai] = b[bi]) & ((a[ai] # 0X) & (b[bi] # 0X)) DO
    INC(ai);
    INC(bi);
  END;
  RETURN (a[ai] = 0X) & (b[bi] = 0X)
END StrEq;

PROCEDURE StringInternRange(VAR sp :StringPool; s :ARRAY OF CHAR; offset, length :INTEGER) :PoolIndex;
VAR
  i    :INTEGER;
  hash :INTEGER;
  b    :INTEGER;
BEGIN
  ASSERT(sp.last + length < PoolSize);
  (* Copy and compute hash at the same time *)
  hash := 811C9DC5H;
  FOR i := 0 TO length-1 DO
    hash := hash XOR ORD(s[offset + i]);
    hash := hash * 16777619;
    sp.buf[sp.last + i] := s[offset + i]
  END;
  sp.buf[sp.last + length] := 0X;
  hash := hash * 85EBCA6BH;
  hash := hash XOR (hash DIV 65536);
  b := hash MOD NumBuckets;
  WHILE (sp.buckets[b] >= 0) & ~StrEq(sp.buf, sp.buckets[b], s, offset) DO
    INC(b);
    IF b = NumBuckets THEN b := 0; END;
  END;
  IF sp.buckets[b] < 0 THEN
    sp.buckets[b] := sp.last;
    INC(sp.last, length+1);
  END;
  RETURN sp.buckets[b]
END StringInternRange;

PROCEDURE StringIntern(VAR sp :StringPool; s :ARRAY OF CHAR) :PoolIndex;
BEGIN
  RETURN StringInternRange(sp, s, 0, StringLen(s))
END StringIntern;

PROCEDURE MakeDummy(i :INTEGER; s :ARRAY OF CHAR);
BEGIN
  s[0] := "i";
  s[1] := CHR((i MOD 10) + 48);
  i := i DIV 10;
  s[2] := CHR((i MOD 10) + 48);
  i := i DIV 10;
  s[3] := CHR((i MOD 10) + 48);
  i := i DIV 10;
  s[4] := CHR((i MOD 10) + 48);
  s[5] := 0X;
END MakeDummy;

PROCEDURE PoolTest;
VAR
  sp   :StringPool;
  s    :ARRAY 25 OF CHAR;
  i,j  :PoolIndex;
BEGIN
  PoolInit(sp);
  ASSERT(11 = StringLen("Hello world"));
  s := "Hello world";
  ASSERT(StrEq(s, 0, "Hello world", 0));
  ASSERT(~StrEq(s, 0, "Hello", 0));
  ASSERT(StrEq(s, 1, "Hello world", 1));
  ASSERT(11 = StringLen(s));
  ASSERT(StringIntern(sp, s) = 0);
  s := "Yello world";
  ASSERT(StringIntern(sp, s) = 12);
  i := StringInternRange(sp, "Hellooo", 1, 4);
  ASSERT(i = StringIntern(sp, "ello"));
  j := StringInternRange(sp, s, 0, 0);
  ASSERT(i # j);
  ASSERT(StringIntern(sp, "") = j);
  s[0] := "A";
  s[1] := 0X;
  ASSERT(StringIntern(sp, s) = StringIntern(sp, "A"));
  ASSERT(StringIntern(sp, s) # StringIntern(sp, "B"));

  PoolInit(sp);
  FOR i := 1 TO 1000 DO
    MakeDummy(i, s);
    StringIntern(sp, s);
  END;
  FOR i := 1 TO 1000 DO
    MakeDummy(i, s);
    ASSERT(StringIntern(sp, s) = (i-1)*6);
  END;
  ASSERT(sp.last = 6000);
END PoolTest;

BEGIN
  PoolTest
END Lex.
