MODULE Files;

TYPE
  File*    = POINTER TO FileDesc;
  Buffer  = POINTER TO BufferRecord;
    BufferRecord =
      RECORD apos, lim: INTEGER;
        mod: BOOLEAN;
        next: Buffer;
      END ;

    Rider* =
      RECORD eof*: BOOLEAN;
        res*: INTEGER;
        file: File;
        apos, bpos: INTEGER;
        buf: Buffer
      END ;
    FileDesc =
      RECORD next: INTEGER; (*list of files invisible to the GC*)
        nofbufs, aleng, bleng: INTEGER;
        modH, registered: BOOLEAN;
        firstbuf: Buffer;
        date: INTEGER;
      END ;

  PROCEDURE Length*(f: File): INTEGER; BEGIN RETURN 0 END Length;
  PROCEDURE New*(name: ARRAY OF CHAR): File; BEGIN RETURN NIL END New;
  PROCEDURE Old*(name: ARRAY OF CHAR): File; BEGIN RETURN NIL END Old;
  PROCEDURE ReadByte*(VAR r: Rider; VAR x: BYTE); END ReadByte;
  PROCEDURE ReadInt*(VAR R: Rider; VAR x: INTEGER); END ReadInt;
  PROCEDURE ReadNum*(VAR R: Rider; VAR x: INTEGER); END ReadNum;
  PROCEDURE ReadString*(VAR R: Rider; VAR x: ARRAY OF CHAR); END ReadString;
  PROCEDURE Register*(f: File); END Register;
  PROCEDURE Set*(VAR r: Rider; f: File; pos: INTEGER); END Set;
  PROCEDURE Write*(VAR r: Rider; ch: CHAR); END Write;
  PROCEDURE WriteByte*(VAR r: Rider; x: BYTE); END WriteByte;
  PROCEDURE WriteInt*(VAR R: Rider; x: INTEGER); END WriteInt;
  PROCEDURE WriteNum*(VAR R: Rider; x: INTEGER); END WriteNum;
  PROCEDURE WriteString*(VAR R: Rider; x: ARRAY OF CHAR); END WriteString;

END Files.
