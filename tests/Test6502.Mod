(* Written with Oberon S3. Likely not working *)
MODULE Test6502;

IMPORT M6502, BIT, In, Out, Files;

VAR
	mem: ARRAY 65536 OF INTEGER;
	myCpu: M6502.CPU;
	running: BOOLEAN;

PROCEDURE DumpHex(x: LONGINT);
VAR nib: INTEGER;
BEGIN
	IF x < 0 THEN Out.String('#!ERROR')
	ELSIF x < 256 THEN
		Out.Char(CHR(32));
		nib := SHORT(x);  nib := nib DIV 16;
		IF nib < 10 THEN Out.Char(CHR(nib + 48)) ELSE Out.Char(CHR(nib + 55)) END;
		nib := BIT.IAND(SHORT(x), 15);
		IF nib < 10 THEN Out.Char(CHR(nib + 48)) ELSE Out.Char(CHR(nib + 55)) END
	ELSE
		Out.Hex(x)
	END
END DumpHex;

PROCEDURE DumpState*;
VAR b: INTEGER;
BEGIN
	Out.String('PC ='); DumpHex(myCpu.pc);
	Out.String(' A = '); DumpHex(myCpu.a);
	Out.String(' X = '); DumpHex(myCpu.x);
	Out.String(' Y = '); DumpHex(myCpu.y);
	Out.String(' SP = '); DumpHex(myCpu.sp);
	IF M6502.negativE IN myCpu.flags THEN Out.String(' N') ELSE Out.String(' n') END;
	IF M6502.overfloW IN myCpu.flags THEN Out.String('V') ELSE Out.String('v') END;
	IF M6502.reserveD IN myCpu.flags THEN Out.String('R') ELSE Out.String('r') END;
	IF M6502.decimaL IN myCpu.flags THEN Out.String('D') ELSE Out.String('d') END;
	IF M6502.interrupT IN myCpu.flags THEN Out.String('I') ELSE Out.String('i') END;
	IF M6502.zerO IN myCpu.flags THEN Out.String('Z') ELSE Out.String('z') END;
	IF M6502.carrY IN myCpu.flags THEN Out.String('C') ELSE Out.String('c') END;
	b := myCpu.readProc(myCpu.pc); Out.Ln; Out.String(' mem='); DumpHex(b);
	Out.Ln
END DumpState;

PROCEDURE ReadMemory(where: LONGINT) :INTEGER;
BEGIN
	IF (where < 0) OR (where > 65535) THEN
		Out.String('Read index out of range: '); Out.Int(where, 0); Out.Ln;
		running := FALSE;
		RETURN 0
	ELSE
		RETURN mem[where];
	END;
END ReadMemory;

PROCEDURE WriteMemory(where: LONGINT; what: INTEGER);
BEGIN
	IF (where < 0) OR (where > 65535) THEN
		Out.String('Write index out of range: '); Out.Int(where, 0); Out.Ln;
		running := FALSE;
		RETURN
	END;
	IF (what < 0) OR (what > 255) THEN
		Out.String('Write value out of range: '); Out.Int(what, 0); Out.Ln;
		RETURN
	END;
	mem[where] := what
END WriteMemory;

PROCEDURE JumpHandler(where: LONGINT);
BEGIN
	IF where < 0 THEN Out.String("HALT"); Out.Int(where, 0); running := FALSE; END;
	IF where = 65534 THEN
		Out.String('IRQ'); running := FALSE
	ELSIF where =  65490 THEN
		Out.Char(CHR(myCpu.a));
		M6502.DoRTS(myCpu, 0);
	END
END JumpHandler;

PROCEDURE LoadBin(name: ARRAY OF CHAR);
VAR f: Files.File; r: Files.Rider; loc: LONGINT; b: CHAR;
BEGIN
	loc := 49152;
	f := Files.Old(name);
	Files.Set(r, f, 0);
	WHILE ~ r.eof DO
		Files.Read(r, b);
		WriteMemory(loc, ORD(b));
		INC(loc)
	END;
	Files.Close(f)
END LoadBin;

PROCEDURE LoadMemory*;
VAR s: ARRAY 64 OF CHAR;
BEGIN
	In.Open; In.String(s); LoadBin(s)
END LoadMemory;

PROCEDURE Start*;
BEGIN
	running := TRUE; WriteMemory(510, 253); WriteMemory(511, 255);
	myCpu.a := 0; myCpu.x := 0; myCpu.y := 0; myCpu.sp := 253; myCpu.pc := 49152; myCpu.flags := {M6502.reserveD}; myCpu.readProc := ReadMemory;
	myCpu.writeProc := WriteMemory; DumpState
END Start;

PROCEDURE Step*;
BEGIN
	WHILE running DO
		M6502.Step(myCpu); (* DumpState; *) JumpHandler(myCpu.pc)
	END
END Step;

END Test6502.
