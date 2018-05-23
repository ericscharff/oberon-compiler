MODULE Texts;

IMPORT Files;

CONST
    Name* = 1;          (*name s (length len)*)
    Char* = 6;          (*special character c*)
TYPE
  Piece = POINTER TO PieceDesc;
  PieceDesc = RECORD
    f: Files.File;
    off, len: INTEGER;
    col, voff: INTEGER;
    prev, next: Piece
  END;

  Text* = POINTER TO TextDesc;
  Notifier* = PROCEDURE (T: Text; op: INTEGER; beg, end: INTEGER);
  TextDesc* = RECORD
    len*: INTEGER;
    changed*: BOOLEAN;
    notify*: Notifier;
    trailer: Piece;
    pce: Piece;  (*cache*)
    org: INTEGER; (*cache*)
  END;

  Reader* = RECORD
    eot*: BOOLEAN;
    col*, voff*: INTEGER;
    ref: Piece;
    org: INTEGER;
    off: INTEGER;
    rider: Files.Rider
  END;

  Scanner* = RECORD (Reader)
    nextCh*: CHAR;
    line*, class*: INTEGER;
    i*: INTEGER;
    x*: REAL;
    y*: REAL;
    c*: CHAR;
    len*: INTEGER;
    s*: ARRAY 32 OF CHAR
  END;

  Buffer* = POINTER TO BufDesc;
  BufDesc* = RECORD
    len*: INTEGER;
    header, last: Piece
  END;

  Writer* = RECORD
    buf*: Buffer;
    col*, voff*: INTEGER;
    rider: Files.Rider
  END;

  PROCEDURE Append* (T: Text; B: Buffer); END Append;
  PROCEDURE Open* (T: Text; name: ARRAY OF CHAR); END Open;
  PROCEDURE OpenReader* (VAR R: Reader; T: Text; pos: INTEGER); END OpenReader;
  PROCEDURE OpenScanner* (VAR S: Scanner; T: Text; pos: INTEGER); END OpenScanner;
  PROCEDURE OpenWriter* (VAR W: Writer); END OpenWriter;
  PROCEDURE Pos* (VAR R: Reader): INTEGER; BEGIN RETURN 0 END Pos;
  PROCEDURE Read* (VAR R: Reader; VAR ch: CHAR); END Read;
  PROCEDURE Scan* (VAR S: Scanner); END Scan;
  PROCEDURE Write* (VAR W: Writer; ch: CHAR); END Write;
  PROCEDURE WriteHex* (VAR W: Writer; x: INTEGER); END WriteHex;
  PROCEDURE WriteInt* (VAR W: Writer; x, n: INTEGER); END WriteInt;
  PROCEDURE WriteLn* (VAR W: Writer); END WriteLn;
  PROCEDURE WriteString* (VAR W: Writer; s: ARRAY OF CHAR); END WriteString;

END Texts.
