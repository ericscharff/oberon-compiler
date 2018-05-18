MODULE Out;

IMPORT OutSys;

VAR
  inited :BOOLEAN;

PROCEDURE Int*(i :INTEGER); END Int;
PROCEDURE Str*(s :ARRAY OF CHAR); END Str;
PROCEDURE InternalInit; BEGIN OutSys.X END InternalInit;

BEGIN
  InternalInit;
  inited := TRUE
END Out.
