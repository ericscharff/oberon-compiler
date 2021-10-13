typedef int oberon_typeid;
oberon_typeid oberon_typeinfos[1];
#include "runtime.c"

typedef struct AST_DeclDesc  *AST_Decl;
typedef struct AST_TypeDesc  *AST_Type;
typedef struct AST_ExprDesc  *AST_Expr;
typedef struct AST_StmtDesc  *AST_Stmt;
typedef struct Decls_ReachableDesc  *Decls_ReachableDecl;
typedef struct Decls_FwdDecl  *Decls_Forward;
typedef char CHAR;
typedef bool BOOLEAN;
typedef int INTEGER;
typedef struct Lex_StringPool {
  CHAR buf[65536];
  INTEGER last;
  INTEGER buckets[4096];
} Lex_StringPool;
typedef float REAL;
typedef struct Lex_Token {
  INTEGER kind;
  INTEGER sVal;
  INTEGER iVal;
  REAL rVal;
} Lex_Token;
typedef struct Lex_Lexer {
  Lex_StringPool sp;
  CHAR buf[65536];
  INTEGER fileName;
  INTEGER pos;
  Lex_Token t;
} Lex_Lexer;
typedef struct AST_QName {
  INTEGER moduleName;
  INTEGER name;
} AST_QName;
typedef struct AST_TypeDesc {
  INTEGER kind;
  AST_Type base;
  AST_Decl fields;
  INTEGER length;
  BOOLEAN needTypeInfo;
  AST_Decl decl;
  INTEGER typeId;
  BOOLEAN reachable;
} AST_TypeDesc;
typedef int SET;
typedef struct AST_ExprDesc {
  INTEGER kind;
  AST_Type typ;
  INTEGER op;
  AST_Expr lhs;
  AST_Expr rhs;
  AST_Expr next;
  AST_Decl decl;
  INTEGER iVal;
  REAL rVal;
  SET setVal;
  BOOLEAN assignable;
} AST_ExprDesc;
typedef struct AST_StmtDesc {
  INTEGER kind;
  AST_Expr cond;
  AST_Stmt body;
  AST_Stmt elsifs;
  AST_Stmt next;
} AST_StmtDesc;
typedef AST_Expr  (*AST_BuiltinResolver)(Lex_Lexer *, AST_Expr );
typedef struct AST_DeclDesc {
  INTEGER kind;
  AST_Decl next;
  AST_QName qname;
  AST_Type typ;
  AST_Expr expr;
  AST_Stmt body;
  BOOLEAN exported;
  INTEGER nesting;
  AST_Decl procVars;
  BOOLEAN isNative;
  AST_BuiltinResolver resolver;
  INTEGER state;
  INTEGER offset;
} AST_DeclDesc;
typedef struct Decls_ReachableDesc {
  AST_Decl d;
  Decls_ReachableDecl next;
} Decls_ReachableDesc;
typedef struct Decls_FwdDecl {
  AST_Type t;
  Decls_Forward next;
} Decls_FwdDecl;
typedef void (*Lex_LexCallback)(void);
typedef struct Parse_CachedImport {
  INTEGER name;
  AST_Decl decls;
} Parse_CachedImport;
CHAR Lex_TokenNames[71][10];
BOOLEAN Lex_fatal;
INTEGER AST_currentModuleName;
INTEGER AST_nextTypeId;
CHAR AST_TypeKindNames[14][10];
INTEGER DumpDecl_indent;
INTEGER DumpDecl_lastDecl;
INTEGER DumpDecl_lastType;
void (*DumpDecl_GenDecl)(Lex_Lexer *, AST_Decl );
AST_Decl DumpDecl_decls[5000];
AST_Type DumpDecl_types[5000];
void (*CCodegen_GenExpr)(Lex_Lexer *, AST_Expr );
BOOLEAN CCodegen_addBoundsChecks;
INTEGER CCodegen_indent;
BOOLEAN CCodegen_genCPlusPlus;
BOOLEAN CCodegen_dumpDecls;
INTEGER CCodegen_innerProcCount;
void (*Decls_VisitDecl)(AST_Decl );
INTEGER Decls_modInitName;
Decls_ReachableDecl Decls_reachableDecls;
Decls_ReachableDecl Decls_tailReachable;
INTEGER Decls_genSymNum;
AST_Decl Decls_globalScope;
INTEGER Parse_importCacheEnd;
AST_Expr  (*Parse_ParseExpression)(void);
Lex_Lexer Parse_l;
AST_Type Decls_nilType;
AST_Type Decls_integerType;
AST_Type Decls_realType;
AST_Type Decls_stringType;
AST_Type Decls_booleanType;
AST_Type Decls_setType;
AST_Decl Decls_scope;
AST_Stmt  (*Parse_ParseStatementSequence)(void);
BOOLEAN Parse_allowLanguageExtensions;
INTEGER Parse_nesting;
AST_Type  (*Parse_ParseType)(void);
INTEGER AST_recordToParent[1024];
Decls_Forward Decls_fwds;
void (*Parse_ParseDeclarationSequence)(void);
Lex_LexCallback Parse_importCallback;
AST_Type Decls_charType;
Parse_CachedImport Parse_importCache[128];
AST_Decl Parse_lastModuleDecls;
void Lex_InitTokenNames(void) {
  strncpy(Lex_TokenNames[0], "ARRAY", sizeof(Lex_TokenNames[0]));
  strncpy(Lex_TokenNames[1], "BEGIN", sizeof(Lex_TokenNames[1]));
  strncpy(Lex_TokenNames[2], "BITAND", sizeof(Lex_TokenNames[2]));
  strncpy(Lex_TokenNames[3], "BITOR", sizeof(Lex_TokenNames[3]));
  strncpy(Lex_TokenNames[4], "BITXOR", sizeof(Lex_TokenNames[4]));
  strncpy(Lex_TokenNames[5], "BY", sizeof(Lex_TokenNames[5]));
  strncpy(Lex_TokenNames[6], "CASE", sizeof(Lex_TokenNames[6]));
  strncpy(Lex_TokenNames[7], "CONST", sizeof(Lex_TokenNames[7]));
  strncpy(Lex_TokenNames[8], "DIV", sizeof(Lex_TokenNames[8]));
  strncpy(Lex_TokenNames[9], "DO", sizeof(Lex_TokenNames[9]));
  strncpy(Lex_TokenNames[10], "ELSE", sizeof(Lex_TokenNames[10]));
  strncpy(Lex_TokenNames[11], "ELSIF", sizeof(Lex_TokenNames[11]));
  strncpy(Lex_TokenNames[12], "END", sizeof(Lex_TokenNames[12]));
  strncpy(Lex_TokenNames[13], "FALSE", sizeof(Lex_TokenNames[13]));
  strncpy(Lex_TokenNames[14], "FOR", sizeof(Lex_TokenNames[14]));
  strncpy(Lex_TokenNames[15], "IF", sizeof(Lex_TokenNames[15]));
  strncpy(Lex_TokenNames[16], "IMPORT", sizeof(Lex_TokenNames[16]));
  strncpy(Lex_TokenNames[17], "IN", sizeof(Lex_TokenNames[17]));
  strncpy(Lex_TokenNames[18], "IS", sizeof(Lex_TokenNames[18]));
  strncpy(Lex_TokenNames[19], "MOD", sizeof(Lex_TokenNames[19]));
  strncpy(Lex_TokenNames[20], "MODULE", sizeof(Lex_TokenNames[20]));
  strncpy(Lex_TokenNames[21], "NATIVE", sizeof(Lex_TokenNames[21]));
  strncpy(Lex_TokenNames[22], "NIL", sizeof(Lex_TokenNames[22]));
  strncpy(Lex_TokenNames[23], "OF", sizeof(Lex_TokenNames[23]));
  strncpy(Lex_TokenNames[24], "OR", sizeof(Lex_TokenNames[24]));
  strncpy(Lex_TokenNames[25], "POINTER", sizeof(Lex_TokenNames[25]));
  strncpy(Lex_TokenNames[26], "PROCEDURE", sizeof(Lex_TokenNames[26]));
  strncpy(Lex_TokenNames[27], "RECORD", sizeof(Lex_TokenNames[27]));
  strncpy(Lex_TokenNames[28], "REPEAT", sizeof(Lex_TokenNames[28]));
  strncpy(Lex_TokenNames[29], "RETURN", sizeof(Lex_TokenNames[29]));
  strncpy(Lex_TokenNames[30], "THEN", sizeof(Lex_TokenNames[30]));
  strncpy(Lex_TokenNames[31], "TO", sizeof(Lex_TokenNames[31]));
  strncpy(Lex_TokenNames[32], "TRUE", sizeof(Lex_TokenNames[32]));
  strncpy(Lex_TokenNames[33], "TYPE", sizeof(Lex_TokenNames[33]));
  strncpy(Lex_TokenNames[34], "UNTIL", sizeof(Lex_TokenNames[34]));
  strncpy(Lex_TokenNames[35], "VAR", sizeof(Lex_TokenNames[35]));
  strncpy(Lex_TokenNames[36], "WHILE", sizeof(Lex_TokenNames[36]));
  strncpy(Lex_TokenNames[37], "IDENT", sizeof(Lex_TokenNames[37]));
  strncpy(Lex_TokenNames[38], "KEYWORD", sizeof(Lex_TokenNames[38]));
  strncpy(Lex_TokenNames[39], "STRING", sizeof(Lex_TokenNames[39]));
  strncpy(Lex_TokenNames[40], "INT", sizeof(Lex_TokenNames[40]));
  strncpy(Lex_TokenNames[41], "REAL", sizeof(Lex_TokenNames[41]));
  strncpy(Lex_TokenNames[42], "PLUS", sizeof(Lex_TokenNames[42]));
  strncpy(Lex_TokenNames[43], "MINUS", sizeof(Lex_TokenNames[43]));
  strncpy(Lex_TokenNames[44], "STAR", sizeof(Lex_TokenNames[44]));
  strncpy(Lex_TokenNames[45], "SLASH", sizeof(Lex_TokenNames[45]));
  strncpy(Lex_TokenNames[46], "TILDE", sizeof(Lex_TokenNames[46]));
  strncpy(Lex_TokenNames[47], "AMP", sizeof(Lex_TokenNames[47]));
  strncpy(Lex_TokenNames[48], "DOT", sizeof(Lex_TokenNames[48]));
  strncpy(Lex_TokenNames[49], "COMMA", sizeof(Lex_TokenNames[49]));
  strncpy(Lex_TokenNames[50], "SEMI", sizeof(Lex_TokenNames[50]));
  strncpy(Lex_TokenNames[51], "VBAR", sizeof(Lex_TokenNames[51]));
  strncpy(Lex_TokenNames[52], "LPAREN", sizeof(Lex_TokenNames[52]));
  strncpy(Lex_TokenNames[53], "RPAREN", sizeof(Lex_TokenNames[53]));
  strncpy(Lex_TokenNames[54], "LBRACK", sizeof(Lex_TokenNames[54]));
  strncpy(Lex_TokenNames[55], "RBRACK", sizeof(Lex_TokenNames[55]));
  strncpy(Lex_TokenNames[56], "LBRACE", sizeof(Lex_TokenNames[56]));
  strncpy(Lex_TokenNames[57], "RBRACE", sizeof(Lex_TokenNames[57]));
  strncpy(Lex_TokenNames[58], "ASSIGN", sizeof(Lex_TokenNames[58]));
  strncpy(Lex_TokenNames[59], "CARET", sizeof(Lex_TokenNames[59]));
  strncpy(Lex_TokenNames[60], "EQ", sizeof(Lex_TokenNames[60]));
  strncpy(Lex_TokenNames[61], "POUND", sizeof(Lex_TokenNames[61]));
  strncpy(Lex_TokenNames[62], "LT", sizeof(Lex_TokenNames[62]));
  strncpy(Lex_TokenNames[63], "GT", sizeof(Lex_TokenNames[63]));
  strncpy(Lex_TokenNames[64], "LTEQ", sizeof(Lex_TokenNames[64]));
  strncpy(Lex_TokenNames[65], "GTEQ", sizeof(Lex_TokenNames[65]));
  strncpy(Lex_TokenNames[66], "DOTDOT", sizeof(Lex_TokenNames[66]));
  strncpy(Lex_TokenNames[67], "COLON", sizeof(Lex_TokenNames[67]));
  strncpy(Lex_TokenNames[68], "AS_SET", sizeof(Lex_TokenNames[68]));
  strncpy(Lex_TokenNames[69], "DOTDOT", sizeof(Lex_TokenNames[69]));
  strncpy(Lex_TokenNames[70], "EOF", sizeof(Lex_TokenNames[70]));
}

void Lex__module_init_(void) {
  Lex_InitTokenNames();
  Lex_fatal = 1;
}

void AST_InitTypeKindNames(void) {
  strncpy(AST_TypeKindNames[1], "NIL", sizeof(AST_TypeKindNames[1]));
  strncpy(AST_TypeKindNames[2], "INTEGER", sizeof(AST_TypeKindNames[2]));
  strncpy(AST_TypeKindNames[3], "REAL", sizeof(AST_TypeKindNames[3]));
  strncpy(AST_TypeKindNames[4], "BOOLEAN", sizeof(AST_TypeKindNames[4]));
  strncpy(AST_TypeKindNames[5], "CHAR", sizeof(AST_TypeKindNames[5]));
  strncpy(AST_TypeKindNames[6], "SET", sizeof(AST_TypeKindNames[6]));
  strncpy(AST_TypeKindNames[7], "STRING", sizeof(AST_TypeKindNames[7]));
  strncpy(AST_TypeKindNames[8], "POINTER", sizeof(AST_TypeKindNames[8]));
  strncpy(AST_TypeKindNames[9], "ARRAY", sizeof(AST_TypeKindNames[9]));
  strncpy(AST_TypeKindNames[10], "ARRAY *", sizeof(AST_TypeKindNames[10]));
  strncpy(AST_TypeKindNames[11], "RECORD", sizeof(AST_TypeKindNames[11]));
  strncpy(AST_TypeKindNames[12], "PROCEDURE", sizeof(AST_TypeKindNames[12]));
  strncpy(AST_TypeKindNames[13], "IMPORT", sizeof(AST_TypeKindNames[13]));
}

void AST__module_init_(void) {
  AST_currentModuleName = 0;
  AST_nextTypeId = 0;
  AST_InitTypeKindNames();
}

void DumpDecl_GenStr(CHAR s[], size_t s__len) {
  (void)s__len;
  Out_Str(s, s__len);
}

void DumpDecl_GenI(void) {
  INTEGER i;
  for (i = 1; i <= DumpDecl_indent; i++) {
    DumpDecl_GenStr("  ", 3);
  }
}

void DumpDecl_GenInt(INTEGER i) {
  Out_Int(i);
}

void DumpDecl_GenLn(void) {
  Out_Ln();
}

void DumpDecl_GenDeclKind(INTEGER kind) {
  if (kind == 1001) {
    DumpDecl_GenStr("declEND", 8);
  } else if ((kind < 1) || (kind > 9)) {
    DumpDecl_GenStr("INVALID_DECL", 13);
  } else {
    switch (kind) {
      case 1:
        DumpDecl_GenStr("declImport", 11);
        break;
      case 2:
        DumpDecl_GenStr("declConst", 10);
        break;
      case 3:
        DumpDecl_GenStr("declType", 9);
        break;
      case 4:
        DumpDecl_GenStr("declVar", 8);
        break;
      case 5:
        DumpDecl_GenStr("declProcedure", 14);
        break;
      case 6:
        DumpDecl_GenStr("declParam", 10);
        break;
      case 7:
        DumpDecl_GenStr("declVarParam", 13);
        break;
      case 8:
        DumpDecl_GenStr("declField", 10);
        break;
      case 9:
        DumpDecl_GenStr("declBuiltin", 12);
        break;
    }
  }
  DumpDecl_GenLn();
}

void Lex_OutStr(struct Lex_Lexer  *l, INTEGER s) {
  Out_StrI((*l).sp.buf, 65536, s);
}

void DumpDecl_GenQName(struct Lex_Lexer  *l, struct AST_QName  *name) {
  if ((*name).moduleName > 0) {
    Lex_OutStr(&((*l)), (*name).moduleName);
    DumpDecl_GenStr(".", 2);
  }
  if ((*name).name > 0) {
    Lex_OutStr(&((*l)), (*name).name);
  }
}

void DumpDecl_GenType(struct Lex_Lexer  *l, AST_Type t) {
  INTEGER i;
  BOOLEAN found;
  AST_Decl f;
  i = 0;
  found = 0;
  DumpDecl_GenI();
  while ((i < DumpDecl_lastType) && !(found)) {
    if (DumpDecl_types[i] == t) {
      found = 1;
      DumpDecl_GenStr("Already generated type: ", 25);
      DumpDecl_GenInt(i);
      DumpDecl_GenLn();
    }
    i++;
  }
  if (!(found)) {
    ASSERT((i < 5000));
    DumpDecl_types[i] = t;
    DumpDecl_GenStr("Type #", 7);
    DumpDecl_GenInt(i);
    DumpDecl_GenLn();
    DumpDecl_lastType++;
    DumpDecl_GenI();
    DumpDecl_GenStr("kind: ", 7);
    if (((*t).kind < 1) || ((*t).kind > 14)) {
      DumpDecl_GenStr("INVALID_EXPR", 13);
    } else {
      switch ((*t).kind) {
        case 1:
          DumpDecl_GenStr("typeNil", 8);
          break;
        case 2:
          DumpDecl_GenStr("typeInteger", 12);
          break;
        case 3:
          DumpDecl_GenStr("typeReal", 9);
          break;
        case 4:
          DumpDecl_GenStr("typeBoolean", 12);
          break;
        case 5:
          DumpDecl_GenStr("typeChar", 9);
          break;
        case 6:
          DumpDecl_GenStr("typeSet", 8);
          break;
        case 7:
          DumpDecl_GenStr("typeString", 11);
          break;
        case 8:
          DumpDecl_GenStr("typePointer", 12);
          break;
        case 9:
          DumpDecl_GenStr("typeArray", 10);
          break;
        case 10:
          DumpDecl_GenStr("typeBuffer", 11);
          break;
        case 11:
          DumpDecl_GenStr("typeRecord", 11);
          break;
        case 12:
          DumpDecl_GenStr("typeProcedure", 14);
          break;
        case 13:
          DumpDecl_GenStr("typeImport", 11);
          break;
        case 14:
          DumpDecl_GenStr("typeEND", 8);
          break;
      }
    }
    DumpDecl_GenLn();
    if ((*t).base != 0) {
      DumpDecl_GenI();
      DumpDecl_GenStr("base:", 6);
      DumpDecl_GenLn();
      DumpDecl_indent++;
      DumpDecl_GenType(&((*l)), (*t).base);
      DumpDecl_indent--;
    }
    DumpDecl_GenI();
    DumpDecl_GenStr("length: ", 9);
    DumpDecl_GenInt((*t).length);
    DumpDecl_GenLn();
    DumpDecl_GenI();
    DumpDecl_GenStr("needTypeInfo: ", 15);
    if ((*t).needTypeInfo) {
      DumpDecl_GenStr("TRUE", 5);
    } else {
      DumpDecl_GenStr("FALSE", 6);
    }
    DumpDecl_GenLn();
    if ((*t).decl != 0) {
      DumpDecl_GenI();
      DumpDecl_GenStr("decl:", 6);
      DumpDecl_GenLn();
      DumpDecl_indent++;
      DumpDecl_GenDecl(&((*l)), (*t).decl);
      DumpDecl_indent--;
    }
    DumpDecl_GenI();
    DumpDecl_GenStr("typeId: ", 9);
    DumpDecl_GenInt((*t).typeId);
    DumpDecl_GenLn();
    DumpDecl_GenI();
    DumpDecl_GenStr("reachable: ", 12);
    if ((*t).reachable) {
      DumpDecl_GenStr("TRUE", 5);
    } else {
      DumpDecl_GenStr("FALSE", 6);
    }
    DumpDecl_GenLn();
    i = 0;
    f = (*t).fields;
    while (f != 0) {
      if ((*f).kind == 1001) {
        ASSERT(((*f).next == 0));
      }
      DumpDecl_GenI();
      DumpDecl_GenStr("Field #", 8);
      DumpDecl_GenInt(i);
      DumpDecl_GenLn();
      DumpDecl_GenDecl(&((*l)), f);
      i++;
      f = (*f).next;
    }
  }
}

void DumpDecl_GenExpr(struct Lex_Lexer  *l, AST_Expr e) {
  DumpDecl_GenI();
  DumpDecl_GenStr("kind: ", 7);
  if (((*e).kind < 1) || ((*e).kind > 12)) {
    DumpDecl_GenStr("INVALID_EXPR", 13);
  } else {
    switch ((*e).kind) {
      case 1:
        DumpDecl_GenStr("exprVal", 8);
        break;
      case 2:
        DumpDecl_GenStr("exprUnary", 10);
        break;
      case 3:
        DumpDecl_GenStr("exprBinary", 11);
        break;
      case 4:
        DumpDecl_GenStr("exprIdentRef", 13);
        break;
      case 5:
        DumpDecl_GenStr("exprProcCall", 13);
        break;
      case 6:
        DumpDecl_GenStr("exprFieldRef", 13);
        break;
      case 7:
        DumpDecl_GenStr("exprPointerDeref", 17);
        break;
      case 8:
        DumpDecl_GenStr("exprArrayRef", 13);
        break;
      case 9:
        DumpDecl_GenStr("exprBufferRef", 14);
        break;
      case 10:
        DumpDecl_GenStr("exprTypeGuard", 14);
        break;
      case 11:
        DumpDecl_GenStr("exprBuiltin", 12);
        break;
      case 12:
        DumpDecl_GenStr("exprAssign", 11);
        break;
    }
  }
  DumpDecl_GenLn();
  if (((*e).op > 0) && ((*e).op < 71)) {
    DumpDecl_GenI();
    DumpDecl_GenStr("op: ", 5);
    DumpDecl_GenInt((*e).op);
    DumpDecl_GenStr(" (", 3);
    DumpDecl_GenStr(Lex_TokenNames[(*e).op], 10);
    DumpDecl_GenStr(")", 2);
    DumpDecl_GenLn();
  }
  if ((*e).typ != 0) {
    DumpDecl_GenI();
    DumpDecl_GenStr("type:", 6);
    DumpDecl_GenLn();
    DumpDecl_indent++;
    DumpDecl_GenType(&((*l)), (*e).typ);
    DumpDecl_indent--;
  }
  if ((*e).lhs != 0) {
    DumpDecl_GenI();
    DumpDecl_GenStr("lhs:", 5);
    DumpDecl_GenLn();
    DumpDecl_indent++;
    DumpDecl_GenExpr(&((*l)), (*e).lhs);
    DumpDecl_indent--;
  }
  if ((*e).rhs != 0) {
    DumpDecl_GenI();
    DumpDecl_GenStr("rhs:", 5);
    DumpDecl_GenLn();
    DumpDecl_indent++;
    DumpDecl_GenExpr(&((*l)), (*e).rhs);
    DumpDecl_indent--;
  }
  if ((*e).next != 0) {
    DumpDecl_GenI();
    DumpDecl_GenStr("next:", 6);
    DumpDecl_GenLn();
    DumpDecl_indent++;
    DumpDecl_GenExpr(&((*l)), (*e).next);
    DumpDecl_indent--;
  }
  if ((*e).decl != 0) {
    DumpDecl_GenI();
    DumpDecl_GenStr("decl: ", 7);
    DumpDecl_GenLn();
    DumpDecl_indent++;
    DumpDecl_GenDecl(&((*l)), (*e).decl);
    DumpDecl_indent--;
  }
  if ((*e).iVal > 0) {
    DumpDecl_GenI();
    DumpDecl_GenStr("iVal: ", 7);
    DumpDecl_GenInt((*e).iVal);
    DumpDecl_GenLn();
  }
}

void DumpDecl_GenStmt(struct Lex_Lexer  *l, AST_Stmt s) {
  INTEGER i;
  AST_Stmt c;
  i = 0;
  c = s;
  while (c != 0) {
    DumpDecl_GenI();
    DumpDecl_GenStr("Statement ", 11);
    DumpDecl_GenInt(i);
    DumpDecl_GenLn();
    DumpDecl_GenI();
    DumpDecl_GenStr("kind: ", 7);
    if (((*c).kind < 1) || ((*c).kind > 11)) {
      DumpDecl_GenStr("INVALID_STMT", 13);
    } else {
      switch ((*c).kind) {
        case 1:
          DumpDecl_GenStr("stmtAssign", 11);
          break;
        case 2:
          DumpDecl_GenStr("stmtProcCall", 13);
          break;
        case 3:
          DumpDecl_GenStr("stmtIf", 7);
          break;
        case 4:
          DumpDecl_GenStr("stmtWhile", 10);
          break;
        case 5:
          DumpDecl_GenStr("stmtRepeat", 11);
          break;
        case 6:
          DumpDecl_GenStr("stmtFor", 8);
          break;
        case 7:
          DumpDecl_GenStr("stmtCase", 9);
          break;
        case 8:
          DumpDecl_GenStr("stmtCaseItem", 13);
          break;
        case 9:
          DumpDecl_GenStr("stmtElsIf", 10);
          break;
        case 10:
          DumpDecl_GenStr("stmtElse", 9);
          break;
        case 11:
          DumpDecl_GenStr("stmtEmpty", 10);
          break;
      }
    }
    DumpDecl_GenLn();
    if ((*c).cond != 0) {
      DumpDecl_GenI();
      DumpDecl_GenStr("cond:", 6);
      DumpDecl_GenLn();
      DumpDecl_indent++;
      DumpDecl_GenExpr(&((*l)), (*c).cond);
      DumpDecl_indent--;
    }
    if ((*c).elsifs != 0) {
      DumpDecl_GenI();
      DumpDecl_GenStr("elsifs:", 8);
      DumpDecl_GenLn();
      DumpDecl_indent++;
      DumpDecl_GenStmt(&((*l)), (*c).elsifs);
      DumpDecl_indent--;
    }
    i++;
    c = (*c).next;
  }
}

void DumpDecl_Generate(struct Lex_Lexer  *l, AST_Decl d) {
  INTEGER i;
  BOOLEAN found;
  AST_Decl pv;
  i = 0;
  found = 0;
  DumpDecl_GenI();
  while ((i < DumpDecl_lastDecl) && !(found)) {
    if (DumpDecl_decls[i] == d) {
      found = 1;
      DumpDecl_GenStr("Already generated decl: ", 25);
      DumpDecl_GenInt(i);
      DumpDecl_GenLn();
    }
    i++;
  }
  if (!(found)) {
    ASSERT((i < 5000));
    DumpDecl_decls[i] = d;
    DumpDecl_GenStr("Declaration #", 14);
    DumpDecl_GenInt(i);
    DumpDecl_GenLn();
    DumpDecl_GenI();
    DumpDecl_lastDecl++;
    DumpDecl_GenStr("kind: ", 7);
    DumpDecl_GenDeclKind((*d).kind);
    if ((*d).offset >= 0) {
      DumpDecl_GenI();
      DumpDecl_GenStr("offset: ", 9);
      DumpDecl_GenInt((*d).offset);
      DumpDecl_GenLn();
    }
    DumpDecl_GenI();
    DumpDecl_GenStr("name: ", 7);
    DumpDecl_GenQName(&((*l)), &((*d).qname));
    DumpDecl_GenLn();
    if ((*d).typ != 0) {
      DumpDecl_GenI();
      DumpDecl_GenStr("type:", 6);
      DumpDecl_GenLn();
      DumpDecl_indent++;
      DumpDecl_GenType(&((*l)), (*d).typ);
      DumpDecl_indent--;
    }
    if ((*d).procVars != 0) {
      ASSERT(((*d).kind == 5));
      DumpDecl_GenI();
      DumpDecl_GenStr("procVars:", 10);
      DumpDecl_GenLn();
      DumpDecl_indent++;
      i = 0;
      pv = (*d).procVars;
      while ((pv != 0) && ((*pv).kind != 1001)) {
        DumpDecl_GenI();
        DumpDecl_GenStr("procVar #", 10);
        DumpDecl_GenInt(i);
        DumpDecl_GenLn();
        DumpDecl_GenDecl(&((*l)), pv);
        pv = (*pv).next;
        i++;
      }
      DumpDecl_indent--;
    }
    DumpDecl_GenI();
    DumpDecl_GenStr("nesting: ", 10);
    DumpDecl_GenInt((*d).nesting);
    DumpDecl_GenLn();
    if ((*d).body != 0) {
      DumpDecl_GenI();
      DumpDecl_GenStr("body:", 6);
      DumpDecl_GenLn();
      DumpDecl_indent++;
      DumpDecl_GenStmt(&((*l)), (*d).body);
      DumpDecl_indent--;
    }
    if ((*d).expr != 0) {
      DumpDecl_GenI();
      DumpDecl_GenStr("expr:", 6);
      DumpDecl_GenLn();
      DumpDecl_indent++;
      DumpDecl_GenExpr(&((*l)), (*d).expr);
      DumpDecl_indent--;
    }
  }
}

void DumpDecl__module_init_(void) {
  DumpDecl_indent = 0;
  DumpDecl_lastDecl = 0;
  DumpDecl_lastType = 0;
  DumpDecl_GenDecl = DumpDecl_Generate;
}

void CCodegen_GenStr(CHAR s[], size_t s__len) {
  (void)s__len;
  Out_Str(s, s__len);
}

void CCodegen_GenInt(INTEGER i) {
  Out_Int(i);
}

void CCodegen_GenChar(INTEGER i) {
  CHAR c2[2];
  if ((((i == 39) || (i == 92)) || (i < 32)) || (i > 126)) {
    CCodegen_GenInt(i);
  } else {
    c2[1] = '\0';
    c2[0] = ((char)i);
    CCodegen_GenStr("'", 2);
    CCodegen_GenStr(c2, 2);
    CCodegen_GenStr("'", 2);
  }
}

void CCodegen_GenReal(REAL r) {
  Out_Real(r);
}

void Lex_OutStrEscaped(struct Lex_Lexer  *l, INTEGER s) {
  CHAR c;
  Out_Str("\"", 2);
  while ((*l).sp.buf[s] != '\0') {
    c = (*l).sp.buf[s];
    if (c == '\134') {
      Out_Str("\\\\", 3);
    } else if (c == '"') {
      Out_Str("\\", 2);
      Out_Str("\"", 2);
    } else if (c == '\12') {
      Out_Str("\\n", 3);
    } else if (c == '\11') {
      Out_Str("\\t", 3);
    } else {
      Out_Char(c);
    }
    s++;
  }
  Out_Str("\"", 2);
}

void CCodegen_GenVal(struct Lex_Lexer  *l, AST_Expr e) {
  ASSERT(((*e).typ != 0));
  if ((*(*e).typ).kind == 1) {
    CCodegen_GenStr("0 /*NULL*/", 11);
  } else if ((1 << (*(*e).typ).kind) & 20) {
    CCodegen_GenInt((*e).iVal);
  } else if ((*(*e).typ).kind == 5) {
    CCodegen_GenChar((*e).iVal);
  } else if ((*(*e).typ).kind == 6) {
    CCodegen_GenInt((*e).setVal);
  } else if ((*(*e).typ).kind == 3) {
    CCodegen_GenReal((*e).rVal);
  } else if ((*(*e).typ).kind == 7) {
    Lex_OutStrEscaped(&((*l)), (*e).iVal);
  } else {
    ASSERT(0);
  }
}

void CCodegen_GenUnaryExpr(struct Lex_Lexer  *l, AST_Expr e) {
  if ((*(*(*e).lhs).typ).kind == 6) {
    if ((*e).op == 43) {
      CCodegen_GenStr("~", 2);
      CCodegen_GenExpr(&((*l)), (*e).lhs);
    } else {
      ASSERT(0);
    }
  } else {
    switch ((*e).op) {
      case 43:
        CCodegen_GenStr("-(", 3);
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(")", 2);
        break;
      case 42:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        break;
      case 46:
        CCodegen_GenStr("!(", 3);
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(")", 2);
        break;
      case 68:
        CCodegen_GenStr("(1 << ", 7);
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(")", 2);
        break;
    }
  }
}

void CCodegen_GenBinaryExpr(struct Lex_Lexer  *l, AST_Expr e) {
  CCodegen_GenStr("(", 2);
  if ((1 << (*(*(*e).lhs).typ).kind) & 640) {
    CCodegen_GenStr("strcmp(", 8);
    CCodegen_GenExpr(&((*l)), (*e).lhs);
    CCodegen_GenStr(", ", 3);
    CCodegen_GenExpr(&((*l)), (*e).rhs);
    CCodegen_GenStr(")", 2);
    switch ((*e).op) {
      case 62:
        CCodegen_GenStr(" < 0", 5);
        break;
      case 63:
        CCodegen_GenStr(" > 0", 5);
        break;
      case 64:
        CCodegen_GenStr(" <= 0", 6);
        break;
      case 65:
        CCodegen_GenStr(" >= 0", 6);
        break;
      case 60:
        CCodegen_GenStr(" == 0", 6);
        break;
      case 61:
        CCodegen_GenStr(" != 0", 6);
        break;
      case 42:
      case 43:
      case 44:
      case 45:
      case 8:
      case 19:
      case 2:
      case 3:
      case 4:
      case 47:
      case 24:
      case 17:
      case 18:
      case 66:
        break;
    }
  } else if ((*(*(*e).lhs).typ).kind == 6) {
    switch ((*e).op) {
      case 42:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" | ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 43:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" & ~", 5);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 44:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" & ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 45:
      case 8:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" ^ ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 60:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" == ", 5);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 61:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" != ", 5);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 19:
      case 2:
      case 3:
      case 4:
      case 47:
      case 24:
      case 62:
      case 63:
      case 64:
      case 65:
      case 17:
      case 18:
      case 66:
        ASSERT(0);
        break;
    }
  } else {
    switch ((*e).op) {
      case 42:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" + ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 43:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" - ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 44:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" * ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 45:
      case 8:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" / ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 19:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" % ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 2:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" & ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 3:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" | ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 4:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" ^ ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 47:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" && ", 5);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 24:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" || ", 5);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 62:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" < ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 63:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" > ", 4);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 64:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" <= ", 5);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 65:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" >= ", 5);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 60:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" == ", 5);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 61:
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(" != ", 5);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 17:
        CCodegen_GenStr("(1 << ", 7);
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(") & ", 5);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        break;
      case 18:
        CCodegen_GenStr("does_type_extend(", 18);
        if ((*(*(*e).lhs).typ).kind == 8) {
          ASSERT(((*(*(*e).rhs).typ).kind == 8));
          CCodegen_GenExpr(&((*l)), (*e).lhs);
          CCodegen_GenStr("->_tid, ", 9);
          CCodegen_GenInt((*(*(*(*e).rhs).typ).base).typeId);
        } else {
          ASSERT(((*(*(*e).lhs).typ).kind == 11));
          ASSERT(((*(*(*e).rhs).typ).kind == 11));
          CCodegen_GenExpr(&((*l)), (*e).lhs);
          CCodegen_GenStr("._tid, ", 8);
          CCodegen_GenInt((*(*(*e).rhs).typ).typeId);
        }
        CCodegen_GenStr(")", 2);
        break;
      case 66:
        CCodegen_GenStr("make_set_range(", 16);
        CCodegen_GenExpr(&((*l)), (*e).lhs);
        CCodegen_GenStr(", ", 3);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        CCodegen_GenStr(")", 2);
        break;
    }
  }
  CCodegen_GenStr(")", 2);
}

void CCodegen_GenQName(struct Lex_Lexer  *l, struct AST_QName  *name) {
  if ((*name).moduleName > 0) {
    Lex_OutStr(&((*l)), (*name).moduleName);
    CCodegen_GenStr("_", 2);
  }
  if ((*name).name > 0) {
    Lex_OutStr(&((*l)), (*name).name);
  }
}

void CCodegen_GenIdentRefExpr(struct Lex_Lexer  *l, AST_Expr e) {
  AST_QName q;
  if (((*(*e).decl).kind == 5) || (((*(*e).decl).kind == 4) && ((*(*e).decl).nesting == 0))) {
    q.moduleName = (*(*e).decl).qname.moduleName;
  } else {
    q.moduleName = 0;
  }
  q.name = (*(*e).decl).qname.name;
  if ((((*(*e).decl).kind == 7) && !(((*(*e).typ).kind == 9))) || (((*(*e).decl).kind == 6) && ((*(*e).typ).kind == 11))) {
    CCodegen_GenStr("(*", 3);
    CCodegen_GenQName(&((*l)), &(q));
    CCodegen_GenStr(")", 2);
  } else {
    CCodegen_GenQName(&((*l)), &(q));
  }
}

BOOLEAN AST_IsOpenArray(AST_Type t) {
  return ((((*t).kind == 9) && ((*t).length == 0)));
}

INTEGER Lex_StringLenI(struct Lex_Lexer  *l, INTEGER s) {
  INTEGER len;
  len = 0;
  while ((*l).sp.buf[s] != '\0') {
    s++;
    len++;
  }
  return (len);
}

void CCodegen_GenLengthof(struct Lex_Lexer  *l, AST_Expr e) {
  AST_QName q;
  q.moduleName = 0;
  if ((*(*e).typ).kind == 7) {
    CCodegen_GenInt((Lex_StringLenI(&((*l)), (*e).iVal) + 1));
  } else if ((*(*e).typ).length > 0) {
    CCodegen_GenInt((*(*e).typ).length);
  } else if ((*(*e).typ).kind == 10) {
    CCodegen_GenExpr(&((*l)), e);
    CCodegen_GenStr(".len", 5);
  } else {
    ASSERT(((*e).kind == 4));
    q.name = (*(*e).decl).qname.name;
    CCodegen_GenQName(&((*l)), &(q));
    CCodegen_GenStr("__len", 6);
  }
}

void CCodegen_GenProcCallExpr(struct Lex_Lexer  *l, AST_Expr e) {
  AST_Decl formal;
  CCodegen_GenExpr(&((*l)), (*e).lhs);
  CCodegen_GenStr("(", 2);
  formal = (*(*(*e).lhs).typ).fields;
  e = (*e).rhs;
  while (e != 0) {
    if ((*(*e).typ).kind == 9) {
      CCodegen_GenExpr(&((*l)), e);
    } else if (((*(*e).typ).kind == 11) || ((*formal).kind == 7)) {
      CCodegen_GenStr("&(", 3);
      CCodegen_GenExpr(&((*l)), e);
      CCodegen_GenStr(")", 2);
    } else if (((*(*e).typ).kind == 10) && ((*(*formal).typ).kind == 9)) {
      CCodegen_GenExpr(&((*l)), e);
      CCodegen_GenStr(".buf", 5);
    } else {
      CCodegen_GenExpr(&((*l)), e);
    }
    if (AST_IsOpenArray((*formal).typ)) {
      CCodegen_GenStr(", ", 3);
      CCodegen_GenLengthof(&((*l)), e);
    }
    if ((*e).next != 0) {
      CCodegen_GenStr(", ", 3);
    }
    e = (*e).next;
    formal = (*formal).next;
  }
  CCodegen_GenStr(")", 2);
}

void CCodegen_GenFieldRefExpr(struct Lex_Lexer  *l, AST_Expr e) {
  CCodegen_GenExpr(&((*l)), (*e).lhs);
  CCodegen_GenStr(".", 2);
  Lex_OutStr(&((*l)), (*e).iVal);
}

void CCodegen_GenPointerDerefExpr(struct Lex_Lexer  *l, AST_Expr e) {
  CCodegen_GenStr("(*", 3);
  CCodegen_GenExpr(&((*l)), (*e).lhs);
  CCodegen_GenStr(")", 2);
}

void CCodegen_GenBufferRefExpr(struct Lex_Lexer  *l, AST_Expr e) {
  CCodegen_GenExpr(&((*l)), (*e).lhs);
  CCodegen_GenStr(".buf[", 6);
  if (CCodegen_addBoundsChecks) {
    CCodegen_GenStr("checkbounds(", 13);
    CCodegen_GenExpr(&((*l)), (*e).rhs);
    CCodegen_GenStr(", ", 3);
    CCodegen_GenLengthof(&((*l)), (*e).lhs);
    CCodegen_GenStr(")", 2);
  } else {
    CCodegen_GenExpr(&((*l)), (*e).rhs);
  }
  CCodegen_GenStr("]", 2);
}

void CCodegen_GenArrayRefExpr(struct Lex_Lexer  *l, AST_Expr e) {
  CCodegen_GenExpr(&((*l)), (*e).lhs);
  CCodegen_GenStr("[", 2);
  if (CCodegen_addBoundsChecks) {
    CCodegen_GenStr("checkbounds(", 13);
    CCodegen_GenExpr(&((*l)), (*e).rhs);
    CCodegen_GenStr(", ", 3);
    CCodegen_GenLengthof(&((*l)), (*e).lhs);
    CCodegen_GenStr(")", 2);
  } else {
    CCodegen_GenExpr(&((*l)), (*e).rhs);
  }
  CCodegen_GenStr("]", 2);
}

void CCodegen_GenTypeGuardExpr(struct Lex_Lexer  *l, AST_Expr e) {
  AST_QName q;
  if ((*(*(*e).lhs).typ).kind == 8) {
    CCodegen_GenStr("dynamic_cast<", 14);
    CCodegen_GenQName(&((*l)), &((*(*e).decl).qname));
    CCodegen_GenStr(">(", 3);
    CCodegen_GenExpr(&((*l)), (*e).lhs);
    CCodegen_GenStr(")", 2);
  } else {
    ASSERT(((*(*(*e).lhs).typ).kind == 11));
    ASSERT(((*(*e).lhs).kind == 4));
    ASSERT(((*(*(*e).lhs).decl).kind == 7));
    CCodegen_GenStr("(*dynamic_cast<", 16);
    CCodegen_GenQName(&((*l)), &((*(*e).decl).qname));
    CCodegen_GenStr("*>(", 4);
    q.moduleName = 0;
    q.name = (*(*(*e).lhs).decl).qname.name;
    CCodegen_GenQName(&((*l)), &(q));
    CCodegen_GenStr("))", 3);
  }
}

void CCodegen_GenLn(void) {
  Out_Ln();
}

void CCodegen_GenI(void) {
  INTEGER i;
  for (i = 1; i <= CCodegen_indent; i++) {
    CCodegen_GenStr("  ", 3);
  }
}

BOOLEAN AST_NeedsTypeInfo(AST_Type t) {
  BOOLEAN ti;
  ti = 0;
  do {
    ti = (*t).needTypeInfo;
    t = (*t).base;
  } while (!(ti || (t == 0)));
  return (ti);
}

void Lex_Error(struct Lex_Lexer  *l, CHAR s[], size_t s__len) {
  (void)s__len;
  Out_Str("Err!", 5);
  Lex_OutStr(&((*l)), (*l).fileName);
  Out_Str("!", 2);
  Out_Int((*l).pos);
  Out_Str("!", 2);
  Out_Str(s, s__len);
}

void Lex_Ln(void) {
  Out_Ln();
  if (Lex_fatal) {
    Out_Halt();
  }
}

void Lex_ErrorLn(struct Lex_Lexer  *l, CHAR s[], size_t s__len) {
  (void)s__len;
  Lex_Error(&((*l)), s, s__len);
  Lex_Ln();
}

void CCodegen_GenType(struct Lex_Lexer  *l, AST_Type t, struct AST_QName  *name, BOOLEAN skipDecl, BOOLEAN procDecl) {
  AST_Decl f;
  AST_Decl pf;
  AST_QName q;
  AST_Type p;
  q.moduleName = 0;
  q.name = 0;
  if (((*t).decl == 0) || skipDecl) {
    switch ((*t).kind) {
      case 2:
        CCodegen_GenStr("int ", 5);
        CCodegen_GenQName(&((*l)), &((*name)));
        break;
      case 3:
        CCodegen_GenStr("float ", 7);
        CCodegen_GenQName(&((*l)), &((*name)));
        break;
      case 4:
        CCodegen_GenStr("bool ", 6);
        CCodegen_GenQName(&((*l)), &((*name)));
        break;
      case 5:
        CCodegen_GenStr("char ", 6);
        CCodegen_GenQName(&((*l)), &((*name)));
        break;
      case 6:
        CCodegen_GenStr("int ", 5);
        CCodegen_GenQName(&((*l)), &((*name)));
        break;
      case 8:
        if ((*(*t).base).decl == 0) {
          CCodegen_GenType(&((*l)), (*t).base, &(q), 0, 0);
        } else {
          CCodegen_GenStr("struct ", 8);
          CCodegen_GenQName(&((*l)), &((*(*(*t).base).decl).qname));
        }
        CCodegen_GenStr(" *", 3);
        CCodegen_GenQName(&((*l)), &((*name)));
        break;
      case 9:
        p = t;
        while ((*p).kind == 9) {
          p = (*p).base;
        }
        CCodegen_GenType(&((*l)), p, &((*name)), 0, 0);
        p = t;
        while ((*p).kind == 9) {
          CCodegen_GenStr("[", 2);
          CCodegen_GenInt((*p).length);
          CCodegen_GenStr("]", 2);
          p = (*p).base;
        }
        break;
      case 10:
        CCodegen_GenStr("struct {", 9);
        CCodegen_GenLn();
        CCodegen_indent++;
        CCodegen_GenI();
        CCodegen_GenType(&((*l)), (*t).base, &(q), 0, 0);
        CCodegen_GenStr(" *buf; size_t cap; size_t len;", 31);
        CCodegen_GenLn();
        CCodegen_indent--;
        CCodegen_GenI();
        CCodegen_GenStr("} ", 3);
        CCodegen_GenQName(&((*l)), &((*name)));
        break;
      case 11:
        if (CCodegen_genCPlusPlus) {
          CCodegen_GenStr("struct ", 8);
          CCodegen_GenQName(&((*l)), &((*name)));
          if ((*t).base != 0) {
            ASSERT(((*(*t).base).decl != 0));
            CCodegen_GenStr(": public ", 10);
            CCodegen_GenQName(&((*l)), &((*(*(*t).base).decl).qname));
          }
          CCodegen_GenStr(" {", 3);
          CCodegen_GenLn();
          CCodegen_indent++;
          if (AST_NeedsTypeInfo(t)) {
            CCodegen_GenI();
            CCodegen_GenQName(&((*l)), &((*name)));
            CCodegen_GenStr("() { _tid = ", 13);
            CCodegen_GenInt((*t).typeId);
            CCodegen_GenStr("; }", 4);
            CCodegen_GenLn();
            if ((*t).base == 0) {
              CCodegen_GenI();
              CCodegen_GenStr("oberon_typeid _tid;", 20);
              CCodegen_GenLn();
              CCodegen_GenI();
              CCodegen_GenStr("virtual ~", 10);
              CCodegen_GenQName(&((*l)), &((*name)));
              CCodegen_GenStr("() = default;", 14);
              CCodegen_GenLn();
            }
          }
          f = (*t).fields;
          if ((*t).base == 0) {
            pf = (AST_Decl)(0);
          } else {
            pf = (*(*(*(*t).base).decl).typ).fields;
          }
          while (((((f != 0) && ((*f).kind != 1001)) && (pf != 0)) && ((*pf).kind != 1001)) && ((*f).qname.name == (*pf).qname.name)) {
            f = (*f).next;
            pf = (*pf).next;
          }
          while ((f != 0) && ((*f).kind != 1001)) {
            q.name = (*f).qname.name;
            CCodegen_GenI();
            if ((*f).isNative) {
              CCodegen_GenQName(&((*l)), &((*(*t).decl).qname));
              CCodegen_GenStr("_Native ", 9);
              CCodegen_GenQName(&((*l)), &(q));
            } else {
              CCodegen_GenType(&((*l)), (*f).typ, &(q), 0, 0);
            }
            CCodegen_GenStr(";", 2);
            CCodegen_GenLn();
            f = (*f).next;
          }
          CCodegen_indent--;
          CCodegen_GenI();
          CCodegen_GenStr("} ", 3);
          CCodegen_GenQName(&((*l)), &((*name)));
        } else {
          CCodegen_GenStr("struct ", 8);
          CCodegen_GenQName(&((*l)), &((*name)));
          CCodegen_GenStr(" {", 3);
          CCodegen_GenLn();
          CCodegen_indent++;
          if (AST_NeedsTypeInfo(t)) {
            Lex_ErrorLn(&((*l)), "C++ required when using IS or typeguard", 40);
          }
          f = (*t).fields;
          while ((f != 0) && ((*f).kind != 1001)) {
            q.name = (*f).qname.name;
            CCodegen_GenI();
            if ((*f).isNative) {
              CCodegen_GenQName(&((*l)), &((*(*t).decl).qname));
              CCodegen_GenStr("_Native ", 9);
              CCodegen_GenQName(&((*l)), &(q));
            } else {
              CCodegen_GenType(&((*l)), (*f).typ, &(q), 0, 0);
            }
            CCodegen_GenStr(";", 2);
            CCodegen_GenLn();
            f = (*f).next;
          }
          CCodegen_indent--;
          CCodegen_GenI();
          CCodegen_GenStr("} ", 3);
          CCodegen_GenQName(&((*l)), &((*name)));
        }
        break;
      case 12:
        if ((*(*t).base).kind == 1) {
          CCodegen_GenStr("void ", 6);
        } else {
          CCodegen_GenType(&((*l)), (*t).base, &(q), 0, 0);
        }
        if (procDecl) {
          CCodegen_GenQName(&((*l)), &((*name)));
        } else {
          CCodegen_GenStr(" (*", 4);
          CCodegen_GenQName(&((*l)), &((*name)));
          CCodegen_GenStr(")", 2);
        }
        CCodegen_GenStr("(", 2);
        if ((*t).fields == 0) {
          if (!(CCodegen_genCPlusPlus)) {
            CCodegen_GenStr("void", 5);
          }
        } else {
          f = (*t).fields;
          while ((*f).kind != 1001) {
            t = (*f).typ;
            if (procDecl) {
              q.name = (*f).qname.name;
            }
            if (((1 << (*t).kind) & 2560) && ((*f).kind != 7)) {
              CCodegen_GenStr("const ", 7);
            }
            if (((*t).kind == 11) || (((*f).kind == 7) && !(((*t).kind == 9)))) {
              q.name = 0;
              CCodegen_GenType(&((*l)), t, &(q), 0, 0);
              CCodegen_GenStr(" *", 3);
              if (procDecl) {
                q.name = (*f).qname.name;
                CCodegen_GenQName(&((*l)), &(q));
              }
            } else if (((*t).kind == 11) || AST_IsOpenArray(t)) {
              q.name = 0;
              CCodegen_GenType(&((*l)), (*t).base, &(q), 0, 0);
              CCodegen_GenStr(" *", 3);
              if (procDecl) {
                q.name = (*f).qname.name;
                CCodegen_GenQName(&((*l)), &(q));
              }
            } else {
              CCodegen_GenType(&((*l)), t, &(q), 0, 0);
            }
            if (AST_IsOpenArray(t)) {
              CCodegen_GenStr(", size_t", 9);
              if (procDecl) {
                CCodegen_GenStr(" ", 2);
                CCodegen_GenQName(&((*l)), &(q));
                CCodegen_GenStr("__len", 6);
              }
            }
            if ((*(*f).next).kind != 1001) {
              CCodegen_GenStr(", ", 3);
            }
            f = (*f).next;
          }
        }
        CCodegen_GenStr(")", 2);
        break;
    }
  } else {
    CCodegen_GenQName(&((*l)), &((*(*t).decl).qname));
    CCodegen_GenStr(" ", 2);
    CCodegen_GenQName(&((*l)), &((*name)));
  }
}

void CCodegen_GenBuiltinExpr(struct Lex_Lexer  *l, AST_Expr e) {
  AST_QName q;
  q.moduleName = 0;
  q.name = 0;
  ASSERT(((*e).iVal >= 1));
  ASSERT(((*e).iVal <= 15));
  switch ((*e).iVal) {
    case 1:
      CCodegen_GenStr("oberon_abs(", 12);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr(")", 2);
      break;
    case 2:
      CCodegen_GenStr("assert(", 8);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr(")", 2);
      break;
    case 3:
    case 10:
    case 5:
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      break;
    case 4:
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      if ((*(*e).rhs).next == 0) {
        CCodegen_GenStr("--", 3);
      } else {
        CCodegen_GenStr(" -= ", 5);
        CCodegen_GenExpr(&((*l)), (*(*e).rhs).next);
      }
      break;
    case 7:
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      if ((*(*e).rhs).next == 0) {
        CCodegen_GenStr("++", 3);
      } else {
        CCodegen_GenStr(" += ", 5);
        CCodegen_GenExpr(&((*l)), (*(*e).rhs).next);
      }
      break;
    case 6:
      CCodegen_GenStr("oberon_buf_init(", 17);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr(", ", 3);
      CCodegen_GenExpr(&((*l)), (*(*e).rhs).next);
      CCodegen_GenStr(", ", 3);
      CCodegen_GenType(&((*l)), (*(*(*e).rhs).typ).base, &(q), 0, 0);
      CCodegen_GenStr(")", 2);
      break;
    case 11:
      CCodegen_GenStr("oberon_buf_push(", 17);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr(", ", 3);
      CCodegen_GenExpr(&((*l)), (*(*e).rhs).next);
      CCodegen_GenStr(", ", 3);
      CCodegen_GenType(&((*l)), (*(*(*e).rhs).typ).base, &(q), 0, 0);
      CCodegen_GenStr(")", 2);
      break;
    case 8:
      CCodegen_GenLengthof(&((*l)), (*e).rhs);
      break;
    case 9:
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      if (CCodegen_genCPlusPlus) {
        CCodegen_GenStr(" = new ", 8);
        CCodegen_GenQName(&((*l)), &((*(*(*(*(*e).rhs).typ).base).decl).qname));
      } else {
        CCodegen_GenStr(" = malloc(sizeof(", 18);
        CCodegen_GenQName(&((*l)), &((*(*(*(*(*e).rhs).typ).base).decl).qname));
        CCodegen_GenStr("))", 3);
      }
      break;
    case 12:
      CCodegen_GenStr("scanf(", 7);
      CCodegen_GenStr("\"", 2);
      CCodegen_GenStr("%d", 3);
      CCodegen_GenStr("\"", 2);
      CCodegen_GenStr(", &(", 5);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr("))", 3);
      break;
    case 13:
      CCodegen_GenStr("printf(", 8);
      CCodegen_GenStr("\"", 2);
      CCodegen_GenStr("%4d", 4);
      CCodegen_GenStr("\"", 2);
      CCodegen_GenStr(", ", 3);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr(")", 2);
      break;
    case 14:
      CCodegen_GenStr("putchar(", 9);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr(")", 2);
      break;
    case 15:
      CCodegen_GenStr("putchar('\\n')", 14);
      break;
  }
}

void CCodegen_GenAssignExpr(struct Lex_Lexer  *l, AST_Expr e) {
  if ((*(*(*e).lhs).typ).kind == 9) {
    ASSERT(((*(*(*(*e).lhs).typ).base).kind == 5));
    CCodegen_GenStr("strncpy(", 9);
    CCodegen_GenExpr(&((*l)), (*e).lhs);
    CCodegen_GenStr(", ", 3);
    CCodegen_GenExpr(&((*l)), (*e).rhs);
    CCodegen_GenStr(", ", 3);
    CCodegen_GenLengthof(&((*l)), (*e).lhs);
    CCodegen_GenStr(")", 2);
  } else {
    CCodegen_GenExpr(&((*l)), (*e).lhs);
    CCodegen_GenStr(" = ", 4);
    CCodegen_GenExpr(&((*l)), (*e).rhs);
  }
}

void CCodegen_GenExpr0(struct Lex_Lexer  *l, AST_Expr e) {
  ASSERT((e != 0));
  ASSERT(((*e).kind >= 1));
  ASSERT(((*e).kind <= 12));
  switch ((*e).kind) {
    case 1:
      CCodegen_GenVal(&((*l)), e);
      break;
    case 2:
      CCodegen_GenUnaryExpr(&((*l)), e);
      break;
    case 3:
      CCodegen_GenBinaryExpr(&((*l)), e);
      break;
    case 4:
      CCodegen_GenIdentRefExpr(&((*l)), e);
      break;
    case 5:
      CCodegen_GenProcCallExpr(&((*l)), e);
      break;
    case 6:
      CCodegen_GenFieldRefExpr(&((*l)), e);
      break;
    case 7:
      CCodegen_GenPointerDerefExpr(&((*l)), e);
      break;
    case 9:
      CCodegen_GenBufferRefExpr(&((*l)), e);
      break;
    case 8:
      CCodegen_GenArrayRefExpr(&((*l)), e);
      break;
    case 10:
      CCodegen_GenTypeGuardExpr(&((*l)), e);
      break;
    case 11:
      CCodegen_GenBuiltinExpr(&((*l)), e);
      break;
    case 12:
      CCodegen_GenAssignExpr(&((*l)), e);
      break;
  }
}

void CCodegen__module_init_(void) {
  CCodegen_GenExpr = CCodegen_GenExpr0;
  CCodegen_addBoundsChecks = 0;
  CCodegen_genCPlusPlus = 0;
  CCodegen_dumpDecls = 0;
  CCodegen_indent = 0;
  CCodegen_innerProcCount = 0;
}

void Decls_VisitType(AST_Type t) {
  AST_Decl f;
  if ((t != 0) && !((*t).reachable)) {
    (*t).reachable = 1;
    Decls_VisitType((*t).base);
    f = (*t).fields;
    while ((f != 0) && ((*f).kind != 1001)) {
      Decls_VisitType((*f).typ);
      f = (*f).next;
    }
    if ((*t).decl != 0) {
      Decls_VisitDecl((*t).decl);
    }
  }
}

void Decls_VisitExpr(AST_Expr e) {
  while (e != 0) {
    Decls_VisitExpr((*e).lhs);
    Decls_VisitExpr((*e).rhs);
    Decls_VisitType((*e).typ);
    if ((*e).decl != 0) {
      Decls_VisitDecl((*e).decl);
    }
    e = (*e).next;
  }
}

void Decls_VisitStatement(AST_Stmt s) {
  while (s != 0) {
    Decls_VisitExpr((*s).cond);
    Decls_VisitStatement((*s).body);
    Decls_VisitStatement((*s).elsifs);
    s = (*s).next;
  }
}

void Decls_VisitDecl0(AST_Decl d) {
  AST_Decl p;
  Decls_ReachableDecl reachable;
  if ((*d).state == 0) {
    (*d).state = 1;
    if ((*d).qname.name == Decls_modInitName) {
      p = (*d).next;
      while ((*p).kind != 1001) {
        if ((*p).kind == 1) {
          Decls_VisitDecl((*(*p).typ).fields);
        }
        p = (*p).next;
      }
    }
    Decls_VisitType((*d).typ);
    Decls_VisitStatement((*d).body);
    Decls_VisitExpr((*d).expr);
    (*d).state = 2;
    reachable = malloc(sizeof(Decls_ReachableDesc));
    (*reachable).d = d;
    (*reachable).next = (Decls_ReachableDecl)(0);
    if (Decls_reachableDecls == 0) {
      Decls_reachableDecls = reachable;
    } else {
      (*Decls_tailReachable).next = reachable;
    }
    Decls_tailReachable = reachable;
  } else if ((*d).state == 1) {
    if ((*d).kind != 5) {
      ASSERT(0);
    }
  } else {
    ASSERT(((*d).state == 2));
  }
}

void Decls__module_init_(void) {
  Decls_VisitDecl = Decls_VisitDecl0;
  Decls_genSymNum = 0;
  Decls_reachableDecls = (Decls_ReachableDecl)(0);
  Decls_tailReachable = (Decls_ReachableDecl)(0);
  Decls_globalScope = (AST_Decl)(0);
}

BOOLEAN Parse_IsToken(INTEGER kind) {
  return ((Parse_l.t.kind == kind));
}

BOOLEAN Lex_StrEq(CHAR a[], size_t a__len, INTEGER ai, CHAR b[], size_t b__len, INTEGER bi, INTEGER len) {
  (void)a__len;
  (void)b__len;
  while ((len > 0) && (a[ai] == b[bi])) {
    ai++;
    bi++;
    len--;
  }
  return ((len == 0));
}

INTEGER Lex_StringInternRange(struct Lex_StringPool  *sp, CHAR s[], size_t s__len, INTEGER offset, INTEGER length) {
  (void)s__len;
  INTEGER i;
  INTEGER hash;
  INTEGER b;
  ASSERT((((*sp).last + length) < 65536));
  hash = -2128831035;
  i = 0;
  while ((i < length) && (s[(offset + i)] != '\0')) {
    hash = (hash ^ s[(offset + i)]);
    hash = (hash * 16777619);
    (*sp).buf[((*sp).last + i)] = s[(offset + i)];
    i++;
  }
  (*sp).buf[((*sp).last + i)] = '\0';
  hash = (hash * -2048144789);
  hash = (hash ^ (hash / 65536));
  b = (hash % 4096);
  while (((*sp).buckets[b] >= 0) && !(Lex_StrEq((*sp).buf, 65536, (*sp).buckets[b], s, s__len, offset, length))) {
    b++;
    if (b == 4096) {
      b = 0;
    }
  }
  if ((*sp).buckets[b] < 0) {
    (*sp).buckets[b] = (*sp).last;
    (*sp).last += (length + 1);
  }
  return ((*sp).buckets[b]);
}

void Lex_ScanIdent(struct Lex_Lexer  *l) {
  INTEGER start;
  BOOLEAN scan;
  INTEGER idx;
  start = (*l).pos;
  scan = 1;
  while (scan) {
    scan = 0;
    switch ((*l).buf[(*l).pos]) {
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
      case 'I':
      case 'J':
      case 'K':
      case 'L':
      case 'M':
      case 'N':
      case 'O':
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
      case 'T':
      case 'U':
      case 'V':
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
      case 'g':
      case 'h':
      case 'i':
      case 'j':
      case 'k':
      case 'l':
      case 'm':
      case 'n':
      case 'o':
      case 'p':
      case 'q':
      case 'r':
      case 's':
      case 't':
      case 'u':
      case 'v':
      case 'w':
      case 'x':
      case 'y':
      case 'z':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '_':
        scan = 1;
        (*l).pos++;
        break;
    }
  }
  idx = Lex_StringInternRange(&((*l).sp), (*l).buf, 65536, start, ((*l).pos - start));
  if (idx <= 360) {
    (*l).t.kind = (idx / 10);
  } else {
    (*l).t.kind = 37;
    (*l).t.sVal = idx;
  }
}

void Lex_Next(struct Lex_Lexer  *l, CHAR  *c) {
  (*l).pos++;
  (*c) = (*l).buf[(*l).pos];
}

REAL Lex_Ten(INTEGER e) {
  REAL r;
  ASSERT((e >= 0));
  r = 1;
  while (e > 0) {
    r = (r * 10);
    e--;
  }
  return (r);
}

REAL Lex_StrToReal(CHAR s[], size_t s__len, INTEGER idx) {
  (void)s__len;
  INTEGER digits;
  INTEGER e;
  INTEGER exp;
  INTEGER sgn;
  REAL r;
  digits = 0;
  e = 0;
  exp = 0;
  sgn = 1;
  do {
    digits = ((digits * 10) + (s[idx] - '0'));
    idx++;
  } while (!(s[idx] == '.'));
  idx++;
  while ((s[idx] >= '0') && (s[idx] <= '9')) {
    e--;
    digits = ((digits * 10) + (s[idx] - '0'));
    idx++;
  }
  if ((s[idx] == 'e') || (s[idx] == 'E')) {
    idx++;
    if (s[idx] == '-') {
      sgn = -1;
      idx++;
    }
    while ((s[idx] >= '0') && (s[idx] <= '9')) {
      exp = ((exp * 10) + (s[idx] - '0'));
      idx++;
    }
    exp = (exp * sgn);
    e = (e + exp);
  }
  if (e > 0) {
    r = (FLT(digits) * Lex_Ten(e));
  } else {
    r = (FLT(digits) / Lex_Ten(-(e)));
  }
  return (r);
}

void Out_PrintLn(CHAR s[], size_t s__len) {
  (void)s__len;
  Out_Str(s, s__len);
  Out_Ln();
}

INTEGER Lex_StringLen(CHAR s[], size_t s__len) {
  (void)s__len;
  INTEGER l;
  l = 0;
  while (s[l] != '\0') {
    l++;
  }
  return (l);
}

INTEGER Lex_StringIntern(struct Lex_StringPool  *sp, CHAR s[], size_t s__len) {
  (void)s__len;
  return (Lex_StringInternRange(&((*sp)), s, s__len, 0, Lex_StringLen(s, s__len)));
}

void Lex_ScanNumber(struct Lex_Lexer  *l) {
  CHAR ch;
  INTEGER start;
  INTEGER base;
  BOOLEAN needHorX;
  CHAR s[2];
  start = (*l).pos;
  (*l).t.kind = 40;
  base = 10;
  needHorX = 0;
  Lex_Next(&((*l)), &(ch));
  while ((((ch >= '0') && (ch <= '9')) || ((ch >= 'A') && (ch <= 'F'))) || ((ch >= 'a') && (ch <= 'f'))) {
    if (((ch >= 'A') && (ch <= 'F')) || ((ch >= 'a') && (ch <= 'f'))) {
      needHorX = 1;
    }
    Lex_Next(&((*l)), &(ch));
  }
  if ((ch == 'X') || (ch == 'x')) {
    (*l).t.kind = 39;
    base = 16;
    needHorX = 0;
    Lex_Next(&((*l)), &(ch));
  } else if ((ch == 'H') || (ch == 'h')) {
    base = 16;
    needHorX = 0;
    Lex_Next(&((*l)), &(ch));
  } else if ((ch == '.') && ((*l).buf[((*l).pos + 1)] != '.')) {
    Lex_Next(&((*l)), &(ch));
    while ((ch >= '0') && (ch <= '9')) {
      Lex_Next(&((*l)), &(ch));
    }
    if ((ch == 'e') || (ch == 'E')) {
      Lex_Next(&((*l)), &(ch));
    }
    if (ch == '-') {
      Lex_Next(&((*l)), &(ch));
    }
    while ((ch >= '0') && (ch <= '9')) {
      Lex_Next(&((*l)), &(ch));
    }
    (*l).t.kind = 41;
  } else if (needHorX) {
    Lex_ErrorLn(&((*l)), "Hex digit must be followed by H or X", 37);
  }
  (*l).t.iVal = 0;
  if ((*l).t.kind == 41) {
    (*l).t.rVal = Lex_StrToReal((*l).buf, 65536, start);
  } else {
    while (start != (*l).pos) {
      ch = (*l).buf[start];
      if ((ch >= '0') && (ch <= '9')) {
        (*l).t.iVal = (((*l).t.iVal * base) + (ch - '0'));
      } else if ((ch >= 'A') && (ch <= 'F')) {
        (*l).t.iVal = (((*l).t.iVal * base) + ((ch - 'A') + 10));
      } else if ((ch >= 'a') && (ch <= 'f')) {
        (*l).t.iVal = (((*l).t.iVal * base) + ((ch - 'a') + 10));
      } else if ((((ch == 'H') || (ch == 'h')) || (ch == 'X')) || (ch == 'x')) {
      } else {
        ASSERT(0);
      }
      start++;
    }
  }
  if ((*l).t.kind == 39) {
    if ((*l).t.iVal > 255) {
      Lex_Error(&((*l)), "Character constant ", 20);
      Out_Int((*l).t.iVal);
      Out_PrintLn(" > 255", 7);
    } else {
      s[0] = ((char)(*l).t.iVal);
      s[1] = '\0';
      (*l).t.sVal = Lex_StringIntern(&((*l).sp), s, 2);
    }
  }
}

void Lex_ScanString(struct Lex_Lexer  *l) {
  CHAR ch;
  INTEGER start;
  start = (*l).pos;
  do {
    Lex_Next(&((*l)), &(ch));
  } while (!((ch == '\0') || (ch == '"')));
  if (ch == '"') {
    (*l).t.kind = 39;
    (*l).t.sVal = Lex_StringInternRange(&((*l).sp), (*l).buf, 65536, (start + 1), (((*l).pos - start) - 1));
    Lex_Next(&((*l)), &(ch));
  } else {
    (*l).pos = start;
    Lex_ErrorLn(&((*l)), "Unterminated string", 20);
    (*l).buf[(*l).pos] = '\0';
  }
}

void Lex_ScanComment(struct Lex_Lexer  *l) {
  INTEGER start;
  start = (*l).pos;
  ASSERT((((*l).buf[(*l).pos] == '(') && ((*l).buf[((*l).pos + 1)] == '*')));
  (*l).pos += 2;
  do {
    if (((*l).buf[(*l).pos] == '(') && ((*l).buf[((*l).pos + 1)] == '*')) {
      Lex_ScanComment(&((*l)));
    } else {
      (*l).pos++;
    }
  } while (!(((*l).buf[(*l).pos] == '\0') || (((*l).buf[(*l).pos] == '*') && ((*l).buf[((*l).pos + 1)] == ')'))));
  if ((*l).buf[(*l).pos] == '\0') {
    (*l).pos = start;
    Lex_ErrorLn(&((*l)), "Unterminated comment", 21);
    (*l).buf[(*l).pos] = '\0';
  } else {
    (*l).pos += 2;
  }
}

void Lex_NextToken(struct Lex_Lexer  *l) {
  (*l).t.kind = 71;
  do {
    switch ((*l).buf[(*l).pos]) {
      case '\0':
        (*l).t.kind = 70;
        break;
      case '\11':
      case '\12':
      case '\13':
      case '\14':
      case '\15':
      case '\40':
        (*l).pos++;
        (*l).t.kind = -1;
        break;
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
      case 'I':
      case 'J':
      case 'K':
      case 'L':
      case 'M':
      case 'N':
      case 'O':
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
      case 'T':
      case 'U':
      case 'V':
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
      case 'g':
      case 'h':
      case 'i':
      case 'j':
      case 'k':
      case 'l':
      case 'm':
      case 'n':
      case 'o':
      case 'p':
      case 'q':
      case 'r':
      case 's':
      case 't':
      case 'u':
      case 'v':
      case 'w':
      case 'x':
      case 'y':
      case 'z':
      case '_':
        Lex_ScanIdent(&((*l)));
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        Lex_ScanNumber(&((*l)));
        break;
      case '"':
        Lex_ScanString(&((*l)));
        break;
      case '+':
        (*l).t.kind = 42;
        (*l).pos++;
        break;
      case '-':
        (*l).t.kind = 43;
        (*l).pos++;
        break;
      case '*':
        (*l).t.kind = 44;
        (*l).pos++;
        break;
      case '/':
        (*l).t.kind = 45;
        (*l).pos++;
        break;
      case '~':
        (*l).t.kind = 46;
        (*l).pos++;
        break;
      case '&':
        (*l).t.kind = 47;
        (*l).pos++;
        break;
      case '.':
        (*l).t.kind = 48;
        (*l).pos++;
        if ((*l).buf[(*l).pos] == '.') {
          (*l).pos++;
          (*l).t.kind = 66;
        }
        break;
      case ',':
        (*l).t.kind = 49;
        (*l).pos++;
        break;
      case ';':
        (*l).t.kind = 50;
        (*l).pos++;
        break;
      case '|':
        (*l).t.kind = 51;
        (*l).pos++;
        break;
      case '(':
        if ((*l).buf[((*l).pos + 1)] == '*') {
          Lex_ScanComment(&((*l)));
          (*l).t.kind = -1;
        } else {
          (*l).t.kind = 52;
          (*l).pos++;
        }
        break;
      case ')':
        (*l).t.kind = 53;
        (*l).pos++;
        break;
      case '[':
        (*l).t.kind = 54;
        (*l).pos++;
        break;
      case ']':
        (*l).t.kind = 55;
        (*l).pos++;
        break;
      case '{':
        (*l).t.kind = 56;
        (*l).pos++;
        break;
      case '}':
        (*l).t.kind = 57;
        (*l).pos++;
        break;
      case ':':
        (*l).t.kind = 67;
        (*l).pos++;
        if ((*l).buf[(*l).pos] == '=') {
          (*l).pos++;
          (*l).t.kind = 58;
        }
        break;
      case '^':
        (*l).t.kind = 59;
        (*l).pos++;
        break;
      case '=':
        (*l).t.kind = 60;
        (*l).pos++;
        break;
      case '#':
        (*l).t.kind = 61;
        (*l).pos++;
        break;
      case '<':
        (*l).t.kind = 62;
        (*l).pos++;
        if ((*l).buf[(*l).pos] == '=') {
          (*l).pos++;
          (*l).t.kind = 64;
        }
        break;
      case '>':
        (*l).t.kind = 63;
        (*l).pos++;
        if ((*l).buf[(*l).pos] == '=') {
          (*l).pos++;
          (*l).t.kind = 65;
        }
        break;
    }
  } while (!((*l).t.kind >= 0));
  if ((*l).t.kind == 71) {
    Lex_ErrorLn(&((*l)), "Invalid character", 18);
  }
}

BOOLEAN Parse_MatchToken(INTEGER kind) {
  BOOLEAN found;
  if (Parse_IsToken(kind)) {
    Lex_NextToken(&(Parse_l));
    found = 1;
  } else {
    found = 0;
  }
  return (found);
}

void AST_NewExpr(AST_Expr  *e, INTEGER kind, AST_Type typ) {
  (*e) = malloc(sizeof(AST_ExprDesc));
  (*(*e)).kind = kind;
  (*(*e)).typ = typ;
  (*(*e)).lhs = (AST_Expr)(0);
  (*(*e)).rhs = (AST_Expr)(0);
  (*(*e)).next = (AST_Expr)(0);
  (*(*e)).decl = (AST_Decl)(0);
  (*(*e)).assignable = 0;
}

AST_Expr AST_NewExprNil(AST_Type typ) {
  AST_Expr e;
  AST_NewExpr(&(e), 1, typ);
  (*e).iVal = 0;
  return (e);
}

AST_Expr AST_NewExprInteger(INTEGER iVal, AST_Type typ) {
  AST_Expr e;
  AST_NewExpr(&(e), 1, typ);
  (*e).iVal = iVal;
  return (e);
}

AST_Expr AST_NewExprReal(REAL rVal, AST_Type typ) {
  AST_Expr e;
  AST_NewExpr(&(e), 1, typ);
  (*e).rVal = rVal;
  return (e);
}

AST_Expr AST_NewExprString(INTEGER sVal, AST_Type typ) {
  AST_Expr e;
  AST_NewExpr(&(e), 1, typ);
  (*e).iVal = sVal;
  return (e);
}

AST_Expr AST_NewExprBoolean(INTEGER bVal, AST_Type typ) {
  AST_Expr e;
  AST_NewExpr(&(e), 1, typ);
  (*e).iVal = bVal;
  return (e);
}

void Lex_Str(CHAR s[], size_t s__len) {
  (void)s__len;
  Out_Str(s, s__len);
}

void Lex_PrintLn(CHAR s[], size_t s__len) {
  (void)s__len;
  Out_Str(s, s__len);
  Lex_Ln();
}

void Parse_ExpectToken(INTEGER kind) {
  if (Parse_IsToken(kind)) {
    Lex_NextToken(&(Parse_l));
  } else {
    Lex_Error(&(Parse_l), "Expected ", 10);
    Lex_Str(Lex_TokenNames[kind], 10);
    Lex_Str(", got ", 7);
    Lex_PrintLn(Lex_TokenNames[Parse_l.t.kind], 10);
  }
}

AST_Expr AST_NewExprSet(AST_Type typ) {
  AST_Expr e;
  AST_NewExpr(&(e), 1, typ);
  (*e).setVal = 0;
  return (e);
}

void AST_OutTypeName(struct Lex_Lexer  *l, AST_Type t) {
  if ((*t).decl == 0) {
    Lex_Str(AST_TypeKindNames[(*t).kind], 10);
  } else {
    if (((*(*t).decl).qname.moduleName > 0) && ((*(*t).decl).qname.moduleName != AST_currentModuleName)) {
      Lex_OutStr(&((*l)), (*(*t).decl).qname.moduleName);
      Lex_Str(".", 2);
    }
    Lex_OutStr(&((*l)), (*(*t).decl).qname.name);
  }
}

void AST_ExpectType(struct Lex_Lexer  *l, AST_Expr e, INTEGER kind) {
  ASSERT((e != 0));
  ASSERT(((*e).typ != 0));
  if ((*(*e).typ).kind != kind) {
    Lex_Error(&((*l)), "Expected ", 10);
    Lex_Str(AST_TypeKindNames[kind], 10);
    Lex_Str(", got ", 7);
    AST_OutTypeName(&((*l)), (*e).typ);
    Lex_Ln();
  }
}

BOOLEAN AST_IsConst(AST_Expr e) {
  return (((*e).kind == 1));
}

AST_Expr AST_NewExprSetRange(struct Lex_Lexer  *l, AST_Expr lhs, AST_Expr rhs, AST_Type setType) {
  AST_Expr e;
  AST_ExpectType(&((*l)), lhs, 2);
  AST_ExpectType(&((*l)), rhs, 2);
  if (AST_IsConst(lhs) && AST_IsConst(rhs)) {
    e = AST_NewExprSet(setType);
    (*e).setVal = make_set_range((*lhs).iVal, (*rhs).iVal);
  } else {
    AST_NewExpr(&(e), 3, setType);
    (*e).op = 66;
    (*e).lhs = lhs;
    (*e).rhs = rhs;
  }
  return (e);
}

void Lex_Int(INTEGER i) {
  Out_Int(i);
}

AST_Expr AST_NewExprSetElement(struct Lex_Lexer  *l, AST_Expr elt, AST_Type setType) {
  AST_Expr e;
  e = AST_NewExprSet(setType);
  (*e).setVal = 0;
  AST_ExpectType(&((*l)), elt, 2);
  if (AST_IsConst(elt)) {
    if (((*elt).iVal < 0) || ((*elt).iVal > 31)) {
      Lex_Error(&((*l)), "Value ", 7);
      Lex_Int((*elt).iVal);
      Lex_PrintLn(" out OF range of SET 0..31", 27);
    } else {
      e = AST_NewExprSet(setType);
      (*e).setVal = (1 <<(*elt).iVal);
    }
  } else {
    AST_NewExpr(&(e), 2, setType);
    (*e).op = 68;
    (*e).lhs = elt;
  }
  return (e);
}

AST_Expr Parse_ParseSetElement(void) {
  AST_Expr e;
  e = Parse_ParseExpression();
  if (Parse_MatchToken(66)) {
    e = AST_NewExprSetRange(&(Parse_l), e, Parse_ParseExpression(), Decls_setType);
  } else {
    e = AST_NewExprSetElement(&(Parse_l), e, Decls_setType);
  }
  return (e);
}

AST_Expr AST_NewExprSetUnion(struct Lex_Lexer  *l, AST_Expr lhs, AST_Expr rhs) {
  AST_Expr e;
  AST_ExpectType(&((*l)), lhs, 6);
  AST_ExpectType(&((*l)), rhs, 6);
  if (AST_IsConst(lhs) && AST_IsConst(rhs)) {
    e = AST_NewExprSet((*lhs).typ);
    (*e).setVal = ((*lhs).setVal | (*rhs).setVal);
  } else {
    AST_NewExpr(&(e), 3, (*lhs).typ);
    (*e).op = 42;
    (*e).lhs = lhs;
    (*e).rhs = rhs;
  }
  return (e);
}

AST_Expr Parse_ParseSet(void) {
  AST_Expr e;
  Parse_ExpectToken(56);
  if (Parse_IsToken(57)) {
    e = AST_NewExprSet(Decls_setType);
  } else {
    e = Parse_ParseSetElement();
    while (Parse_MatchToken(49)) {
      e = AST_NewExprSetUnion(&(Parse_l), e, Parse_ParseSetElement());
    }
  }
  Parse_ExpectToken(57);
  return (e);
}

BOOLEAN AST_IsImported(AST_Decl d) {
  ASSERT((d != 0));
  while ((d != 0) && ((*d).kind != 1001)) {
    d = (*d).next;
  }
  ASSERT((d != 0));
  ASSERT(((*d).kind == 1001));
  return (((*d).qname.moduleName != AST_currentModuleName));
}

AST_Expr AST_NewExprIdentRef(AST_Decl d) {
  AST_Expr e;
  ASSERT((d != 0));
  ASSERT(((*d).typ != 0));
  AST_NewExpr(&(e), 4, (*d).typ);
  (*e).decl = d;
  if (((((*d).kind == 4) && !(AST_IsImported(d))) || (((*d).kind == 6) && !(((1 << (*(*d).typ).kind) & 3584)))) || ((*d).kind == 7)) {
    (*e).assignable = 1;
  } else {
    (*e).assignable = 0;
  }
  if ((*d).kind == 2) {
    ASSERT(((*d).typ == (*(*d).expr).typ));
    ASSERT(((*(*d).expr).kind == 1));
    (*e).kind = 1;
    (*e).iVal = (*(*d).expr).iVal;
    (*e).rVal = (*(*d).expr).rVal;
    (*e).setVal = (*(*d).expr).setVal;
  }
  return (e);
}

INTEGER Parse_ExpectIdentifier(void) {
  INTEGER s;
  s = Parse_l.t.sVal;
  Parse_ExpectToken(37);
  return (s);
}

AST_Decl Decls_LookupDecl0(INTEGER name) {
  AST_Decl p;
  p = Decls_scope;
  while ((p != 0) && ((*p).qname.name != name)) {
    p = (*p).next;
  }
  return (p);
}

AST_Decl Decls_LookupDecl(struct Lex_Lexer  *l, INTEGER name) {
  AST_Decl p;
  p = Decls_LookupDecl0(name);
  if (p == 0) {
    Lex_Error(&((*l)), "", 1);
    Lex_OutStr(&((*l)), name);
    Lex_PrintLn(" undefined", 11);
  }
  return (p);
}

BOOLEAN Parse_IsImportedModule(INTEGER ident) {
  AST_Decl d;
  d = Decls_LookupDecl(&(Parse_l), ident);
  return (((d != 0) && ((*d).kind == 1)));
}

AST_Decl Decls_LookupImport(struct Lex_Lexer  *l, INTEGER moduleName, INTEGER name) {
  AST_Decl p;
  AST_Decl d;
  d = Decls_LookupDecl(&((*l)), moduleName);
  ASSERT(((*d).kind == 1));
  p = (*(*d).typ).fields;
  while ((p != 0) && ((*p).qname.name != name)) {
    p = (*p).next;
  }
  if (p == 0) {
    Lex_Error(&((*l)), "", 1);
    Lex_OutStr(&((*l)), moduleName);
    Lex_Str(".", 2);
    Lex_OutStr(&((*l)), name);
    Lex_PrintLn(" undefined", 11);
  } else if (!((*p).exported)) {
    Lex_Error(&((*l)), "", 1);
    Lex_OutStr(&((*l)), moduleName);
    Lex_Str(".", 2);
    Lex_OutStr(&((*l)), name);
    Lex_PrintLn(" is not exported", 17);
  }
  return (p);
}

AST_Decl Parse_ParseQualident(void) {
  INTEGER moduleName;
  INTEGER ident;
  AST_Decl d;
  ident = Parse_ExpectIdentifier();
  if (Parse_IsImportedModule(ident)) {
    moduleName = ident;
    Parse_ExpectToken(48);
    ident = Parse_ExpectIdentifier();
    d = Decls_LookupImport(&(Parse_l), moduleName, ident);
  } else {
    d = Decls_LookupDecl(&(Parse_l), ident);
  }
  return (d);
}

BOOLEAN Parse_IsTypeGuard(AST_Expr e) {
  return ((((*(*e).typ).kind == 8) || ((((*(*e).typ).kind == 11) && ((*e).kind == 4)) && ((*(*e).decl).kind == 7))));
}

AST_Expr AST_NewExprPointerDeref(struct Lex_Lexer  *l, AST_Expr base) {
  AST_Expr e;
  AST_NewExpr(&(e), 7, (*base).typ);
  (*e).lhs = base;
  (*e).assignable = (*base).assignable;
  if ((*(*base).typ).kind == 8) {
    (*e).typ = (*(*base).typ).base;
  } else {
    Lex_ErrorLn(&((*l)), "not a POINTER", 14);
  }
  return (e);
}

AST_Expr AST_NewExprFieldRef(struct Lex_Lexer  *l, AST_Expr base, INTEGER name) {
  AST_Expr e;
  AST_Decl d;
  e = base;
  if ((*(*base).typ).kind == 8) {
    base = AST_NewExprPointerDeref(&((*l)), base);
  }
  if ((*(*base).typ).kind == 11) {
    d = (*(*base).typ).fields;
    while (((d != 0) && ((*d).kind != 1001)) && ((*d).qname.name != name)) {
      d = (*d).next;
    }
    if ((*d).qname.name == name) {
      if (AST_IsImported(d) && !((*d).exported)) {
        Lex_Error(&((*l)), "Field ", 7);
        Lex_OutStr(&((*l)), name);
        Lex_PrintLn(" is private", 12);
      }
      AST_NewExpr(&(e), 6, (*d).typ);
      (*e).lhs = base;
      (*e).iVal = name;
      (*e).decl = d;
      (*e).assignable = (*base).assignable;
    } else {
      Lex_Error(&((*l)), "Field ", 7);
      Lex_OutStr(&((*l)), name);
      Lex_PrintLn(" not found", 11);
    }
  } else {
    Lex_ErrorLn(&((*l)), "Not a RECORD", 13);
  }
  return (e);
}

AST_Expr AST_NewExprArrayRef(struct Lex_Lexer  *l, AST_Expr base, AST_Expr index) {
  AST_Expr e;
  e = base;
  if ((1 << (*(*base).typ).kind) & 1536) {
    if ((*(*index).typ).kind == 2) {
      if ((((*index).kind == 1) && ((*(*base).typ).length > 0)) && (((*index).iVal < 0) || ((*index).iVal >= (*(*base).typ).length))) {
        Lex_Error(&((*l)), "Array index ", 13);
        Lex_Int((*index).iVal);
        Lex_Str(" out OF range for ARRAY OF length ", 35);
        Lex_Int((*(*base).typ).length);
        Lex_Ln();
      } else {
        if ((*(*base).typ).kind == 10) {
          AST_NewExpr(&(e), 9, (*(*base).typ).base);
        } else {
          AST_NewExpr(&(e), 8, (*(*base).typ).base);
        }
        (*e).lhs = base;
        (*e).rhs = index;
        (*e).assignable = (*base).assignable;
      }
    } else {
      Lex_Error(&((*l)), "ARRAY index must be an INTEGER, got ", 37);
      AST_OutTypeName(&((*l)), (*index).typ);
      Lex_Ln();
    }
  } else {
    Lex_ErrorLn(&((*l)), "Not an ARRAY", 13);
  }
  return (e);
}

BOOLEAN AST_Extends(AST_Type a, AST_Type b) {
  if ((((a != 0) && (b != 0)) && ((*a).kind == 11)) && ((*b).kind == 11)) {
    while ((a != 0) && (a != b)) {
      a = (*a).base;
    }
  }
  return ((((a != 0) && (b != 0)) && (a == b)));
}

void AST_SetGenTypeInfo(AST_Type t) {
  if ((*t).kind == 8) {
    t = (*t).base;
  }
  while (t != 0) {
    (*t).needTypeInfo = 1;
    t = (*t).base;
  }
}

AST_Expr AST_NewExprTypeGuard(struct Lex_Lexer  *l, AST_Expr base, AST_Decl newType) {
  AST_Expr e;
  e = base;
  if (((*newType).kind == 3) && ((1 << (*(*newType).typ).kind) & 2304)) {
    if (((((*(*base).typ).kind == 8) && ((*(*newType).typ).kind == 8)) && AST_Extends((*(*newType).typ).base, (*(*base).typ).base)) || ((((*(*base).typ).kind == 11) && ((*(*newType).typ).kind == 11)) && AST_Extends((*newType).typ, (*base).typ))) {
      AST_NewExpr(&(e), 10, (*newType).typ);
      (*e).lhs = base;
      (*e).decl = newType;
      (*e).assignable = (*base).assignable;
      AST_SetGenTypeInfo((*newType).typ);
    } else {
      Lex_ErrorLn(&((*l)), "Guarded and base type are unrelated", 36);
    }
  } else {
    Lex_Error(&((*l)), "Declaration ", 13);
    Lex_OutStr(&((*l)), (*newType).qname.name);
    Lex_PrintLn(" must be a POINTER or RECORD type", 34);
  }
  return (e);
}

AST_Expr Parse_ParseDesignator(void) {
  AST_Expr e;
  e = AST_NewExprIdentRef(Parse_ParseQualident());
  while (((Parse_IsToken(48) || Parse_IsToken(54)) || Parse_IsToken(59)) || (Parse_IsTypeGuard(e) && Parse_IsToken(52))) {
    if (Parse_MatchToken(48)) {
      e = AST_NewExprFieldRef(&(Parse_l), e, Parse_ExpectIdentifier());
    } else if (Parse_MatchToken(54)) {
      e = AST_NewExprArrayRef(&(Parse_l), e, Parse_ParseExpression());
      while (Parse_MatchToken(49)) {
        e = AST_NewExprArrayRef(&(Parse_l), e, Parse_ParseExpression());
      }
      Parse_ExpectToken(55);
    } else if (Parse_MatchToken(59)) {
      e = AST_NewExprPointerDeref(&(Parse_l), e);
    } else if (Parse_IsTypeGuard(e) && Parse_MatchToken(52)) {
      e = AST_NewExprTypeGuard(&(Parse_l), e, Parse_ParseQualident());
      Parse_ExpectToken(53);
    } else {
      ASSERT(0);
    }
  }
  return (e);
}

BOOLEAN Lex_IsOneChar(struct Lex_Lexer  *l, INTEGER s) {
  return ((((*l).sp.buf[s] == '\0') || ((*l).sp.buf[(s + 1)] == '\0')));
}

BOOLEAN AST_AssignmentCompatable(struct Lex_Lexer  *l, AST_Type a, AST_Type b, INTEGER aSval, INTEGER bSval) {
  BOOLEAN procCompatable;
  AST_Decl aParam;
  AST_Decl bParam;
  INTEGER len;
  procCompatable = 0;
  if (((*a).kind == 12) && ((*b).kind == 12)) {
    procCompatable = (((*a).base == (*b).base) && ((*a).length == (*b).length));
    if (procCompatable && ((*a).length > 0)) {
      len = (*a).length;
      aParam = (*a).fields;
      bParam = (*b).fields;
      while (((len > 0) && ((*aParam).kind != 1001)) && ((*bParam).kind != 1001)) {
        procCompatable = (procCompatable && AST_AssignmentCompatable(&((*l)), (*aParam).typ, (*bParam).typ, 0, 0));
        aParam = (*aParam).next;
        bParam = (*bParam).next;
        len--;
      }
      procCompatable = (((procCompatable && (len == 0)) && ((*aParam).kind == 1001)) && ((*bParam).kind == 1001));
    }
  }
  return ((((((((((((a == b) || (((*a).kind == 7) && ((*b).kind == 7))) || ((((*a).kind == 5) && ((*b).kind == 7)) && Lex_IsOneChar(&((*l)), bSval))) || ((((*b).kind == 5) && ((*a).kind == 7)) && Lex_IsOneChar(&((*l)), aSval))) || (((*a).kind == 1) && ((*b).kind == 8))) || (((*a).kind == 1) && ((*b).kind == 12))) || ((((*a).kind == 8) && ((*b).kind == 8)) && AST_Extends((*a).base, (*b).base))) || ((((*a).kind == 11) && ((*b).kind == 11)) && AST_Extends(a, b))) || ((((*a).kind == 12) && ((*b).kind == 12)) && procCompatable)) || (((((*a).kind == 9) && ((*(*a).base).kind == 5)) && ((*b).kind == 9)) && ((*(*b).base).kind == 5))) || ((((*a).kind == 7) && ((*b).kind == 9)) && ((*(*b).base).kind == 5))));
}

void AST_ExpectArgMatch(struct Lex_Lexer  *l, INTEGER arg, AST_Expr actual, AST_Decl formal) {
  if ((AST_IsOpenArray((*formal).typ) && ((*(*actual).typ).kind == 9)) && ((*(*actual).typ).base == (*(*formal).typ).base)) {
  } else if ((AST_IsOpenArray((*formal).typ) && ((*(*actual).typ).kind == 10)) && ((*(*actual).typ).base == (*(*formal).typ).base)) {
  } else if (((*formal).kind == 7) && !((*actual).assignable)) {
    Lex_Error(&((*l)), "For argument ", 14);
    Lex_Int(arg);
    Lex_PrintLn(", param is not assignable (expected VAR param)", 47);
  } else if (!(AST_AssignmentCompatable(&((*l)), (*actual).typ, (*formal).typ, (*actual).iVal, (*actual).iVal))) {
    Lex_Error(&((*l)), "For argument ", 14);
    Lex_Int(arg);
    Lex_Str(", expected ", 12);
    AST_OutTypeName(&((*l)), (*formal).typ);
    Lex_Str(", got ", 7);
    AST_OutTypeName(&((*l)), (*actual).typ);
    Lex_Ln();
  }
}

INTEGER Lex_FirstChar(struct Lex_Lexer  *l, INTEGER s) {
  return ((*l).sp.buf[s]);
}

void AST_CoerceToChar(struct Lex_Lexer  *l, AST_Expr e, AST_Type charType) {
  ASSERT(AST_IsConst(e));
  ASSERT(((*(*e).typ).kind == 7));
  ASSERT(Lex_IsOneChar(&((*l)), (*e).iVal));
  (*e).typ = charType;
  (*e).iVal = Lex_FirstChar(&((*l)), (*e).iVal);
}

AST_Expr AST_NewExprProcCall(struct Lex_Lexer  *l, AST_Expr proc, AST_Expr args) {
  AST_Expr e;
  AST_Expr arg;
  INTEGER i;
  INTEGER count;
  AST_Decl formal;
  e = proc;
  if ((*(*proc).typ).kind == 12) {
    i = 0;
    count = (*(*proc).typ).length;
    AST_NewExpr(&(e), 5, (*(*proc).typ).base);
    (*e).lhs = proc;
    (*e).rhs = args;
    arg = args;
    while (arg != 0) {
      i++;
      arg = (*arg).next;
    }
    if (i == count) {
      i = 1;
      arg = args;
      formal = (*(*proc).typ).fields;
      while (count > 0) {
        AST_ExpectArgMatch(&((*l)), i, arg, formal);
        if (AST_IsConst(arg) && ((*(*formal).typ).kind == 5)) {
          AST_CoerceToChar(&((*l)), arg, (*formal).typ);
        }
        count--;
        i++;
        formal = (*formal).next;
        arg = (*arg).next;
      }
    } else {
      Lex_Error(&((*l)), "Expected ", 10);
      Lex_Int(count);
      Lex_Str(" parameters, got ", 18);
      Lex_Int(i);
      Lex_Ln();
    }
  } else if (((*proc).kind == 4) && ((*(*proc).decl).kind == 9)) {
    e = (*(*proc).decl).resolver(&((*l)), args);
  } else {
    Lex_ErrorLn(&((*l)), "designator is not a PROCEDURE", 30);
  }
  return (e);
}

AST_Expr Parse_ParseActualParameters(void) {
  AST_Expr head;
  AST_Expr tail;
  head = (AST_Expr)(0);
  Parse_ExpectToken(52);
  if (!(Parse_IsToken(53))) {
    head = Parse_ParseExpression();
    tail = head;
    while (Parse_MatchToken(49)) {
      (*tail).next = Parse_ParseExpression();
      tail = (*tail).next;
    }
  }
  Parse_ExpectToken(53);
  return (head);
}

AST_Expr AST_NewExprUnary(struct Lex_Lexer  *l, INTEGER op, AST_Expr lhs) {
  AST_Expr e;
  AST_NewExpr(&(e), 2, (*lhs).typ);
  (*e).op = op;
  (*e).lhs = lhs;
  switch (op) {
    case 42:
      if ((1 << (*(*lhs).typ).kind) & 76) {
        e = lhs;
      } else {
        Lex_ErrorLn(&((*l)), "Expected INTEGER, REAL, or SET", 31);
      }
      break;
    case 43:
      if ((1 << (*(*lhs).typ).kind) & 76) {
        if (AST_IsConst(lhs)) {
          (*e).kind = 1;
          (*e).iVal = -((*lhs).iVal);
          (*e).rVal = -((*lhs).rVal);
          (*e).setVal = ~((*lhs).setVal);
        }
      } else {
        Lex_ErrorLn(&((*l)), "Expected INTEGER, REAL, or SET", 31);
      }
      break;
    case 46:
      if ((*(*lhs).typ).kind == 4) {
        if (AST_IsConst(lhs)) {
        }
      } else {
        Lex_ErrorLn(&((*l)), "Expected BOOLEAN", 17);
      }
      break;
  }
  return (e);
}

AST_Expr Parse_ParseFactor(void) {
  AST_Expr e;
  e = AST_NewExprNil(Decls_nilType);
  if (Parse_IsToken(40)) {
    e = AST_NewExprInteger(Parse_l.t.iVal, Decls_integerType);
    Parse_MatchToken(40);
  } else if (Parse_IsToken(41)) {
    e = AST_NewExprReal(Parse_l.t.rVal, Decls_realType);
    Parse_MatchToken(41);
  } else if (Parse_IsToken(39)) {
    e = AST_NewExprString(Parse_l.t.sVal, Decls_stringType);
    Parse_MatchToken(39);
  } else if (Parse_MatchToken(22)) {
    e = AST_NewExprNil(Decls_nilType);
  } else if (Parse_MatchToken(32)) {
    e = AST_NewExprBoolean(1, Decls_booleanType);
  } else if (Parse_MatchToken(13)) {
    e = AST_NewExprBoolean(0, Decls_booleanType);
  } else if (Parse_IsToken(56)) {
    e = Parse_ParseSet();
  } else if (Parse_IsToken(37)) {
    e = Parse_ParseDesignator();
    if (Parse_IsToken(52)) {
      e = AST_NewExprProcCall(&(Parse_l), e, Parse_ParseActualParameters());
    }
  } else if (Parse_MatchToken(52)) {
    e = Parse_ParseExpression();
    Parse_ExpectToken(53);
  } else if (Parse_MatchToken(46)) {
    e = AST_NewExprUnary(&(Parse_l), 46, Parse_ParseFactor());
  } else {
    Lex_ErrorLn(&(Parse_l), "Factor expected", 16);
  }
  return (e);
}

BOOLEAN Parse_IsMulOperator(void) {
  return ((((((((Parse_IsToken(44) || Parse_IsToken(45)) || Parse_IsToken(8)) || Parse_IsToken(19)) || Parse_IsToken(47)) || Parse_IsToken(2)) || Parse_IsToken(3)) || Parse_IsToken(4)));
}

BOOLEAN AST_ExprCompatable(struct Lex_Lexer  *l, INTEGER op, AST_Expr lhs, AST_Expr rhs) {
  BOOLEAN good;
  if (AST_AssignmentCompatable(&((*l)), (*lhs).typ, (*rhs).typ, (*lhs).iVal, (*rhs).iVal) || AST_AssignmentCompatable(&((*l)), (*rhs).typ, (*lhs).typ, (*rhs).iVal, (*lhs).iVal)) {
    good = 1;
  } else {
    good = 0;
    Lex_Error(&((*l)), "Type mismatch for op [", 23);
    Lex_Str(Lex_TokenNames[op], 10);
    Lex_Str("] got ", 7);
    AST_OutTypeName(&((*l)), (*lhs).typ);
    Lex_Str(" and ", 6);
    AST_OutTypeName(&((*l)), (*rhs).typ);
    Lex_Ln();
  }
  return (good);
}

BOOLEAN AST_IsStringType(AST_Type t) {
  return ((((*t).kind == 7) || (((*t).kind == 9) && ((*(*t).base).kind == 5))));
}

AST_Expr AST_NewExprBinary(struct Lex_Lexer  *l, INTEGER op, AST_Expr lhs, AST_Expr rhs, AST_Type booleanType) {
  AST_Expr e;
  AST_NewExpr(&(e), 3, (*lhs).typ);
  (*e).op = op;
  (*e).lhs = lhs;
  (*e).rhs = rhs;
  switch (op) {
    case 42:
    case 43:
    case 44:
    case 45:
      if (AST_ExprCompatable(&((*l)), op, lhs, rhs) && ((1 << (*(*lhs).typ).kind) & 76)) {
        if (AST_IsConst(lhs) && AST_IsConst(rhs)) {
          (*e).kind = 1;
          if (op == 42) {
            (*e).iVal = ((*lhs).iVal + (*rhs).iVal);
            (*e).rVal = ((*lhs).rVal + (*rhs).rVal);
            (*e).setVal = ((*lhs).setVal | (*rhs).setVal);
          } else if (op == 43) {
            (*e).iVal = ((*lhs).iVal - (*rhs).iVal);
            (*e).rVal = ((*lhs).rVal - (*rhs).rVal);
            (*e).setVal = ((*lhs).setVal & ~ (*rhs).setVal);
          } else if (op == 44) {
            (*e).iVal = ((*lhs).iVal * (*rhs).iVal);
            (*e).rVal = ((*lhs).rVal * (*rhs).rVal);
            (*e).setVal = ((*lhs).setVal & (*rhs).setVal);
          } else if (op == 45) {
            if ((*rhs).iVal == 0) {
              (*e).iVal = 0;
            } else {
              (*e).iVal = ((*lhs).iVal / (*rhs).iVal);
            }
            if ((*rhs).rVal == 0) {
              (*e).rVal = 0;
            } else {
              (*e).rVal = ((*lhs).rVal / (*rhs).rVal);
            }
            (*e).setVal = ((*lhs).setVal ^ (*rhs).setVal);
          }
        }
      } else {
        Lex_ErrorLn(&((*l)), "Expected INTEGER, REAL, or SET", 31);
      }
      break;
    case 8:
    case 19:
    case 2:
    case 3:
    case 4:
      if (AST_ExprCompatable(&((*l)), op, lhs, rhs) && ((*(*lhs).typ).kind == 2)) {
        if (AST_IsConst(lhs) && AST_IsConst(rhs)) {
          (*e).kind = 1;
          if (op == 8) {
            (*e).iVal = ((*lhs).iVal / (*rhs).iVal);
          } else if (op == 19) {
            (*e).iVal = ((*lhs).iVal % (*rhs).iVal);
          } else if (op == 2) {
            (*e).iVal = ((*lhs).iVal & (*rhs).iVal);
          } else if (op == 3) {
            (*e).iVal = ((*lhs).iVal | (*rhs).iVal);
          } else if (op == 4) {
            (*e).iVal = ((*lhs).iVal ^ (*rhs).iVal);
          }
        }
      } else {
        Lex_ErrorLn(&((*l)), "Expected INTEGER", 17);
      }
      break;
    case 47:
    case 24:
      if (AST_ExprCompatable(&((*l)), op, lhs, rhs) && ((*(*lhs).typ).kind == 4)) {
        if (AST_IsConst(lhs) && AST_IsConst(rhs)) {
        }
      } else {
        Lex_ErrorLn(&((*l)), "Expected BOOLEAN", 17);
      }
      break;
    case 62:
    case 63:
    case 64:
    case 65:
      (*e).typ = booleanType;
      if (AST_ExprCompatable(&((*l)), op, lhs, rhs) && (AST_IsStringType((*lhs).typ) || ((1 << (*(*lhs).typ).kind) & 236))) {
        if (AST_IsConst(lhs) && AST_IsConst(rhs)) {
        }
        if (AST_IsConst(lhs) && ((*(*rhs).typ).kind == 5)) {
          AST_CoerceToChar(&((*l)), lhs, (*rhs).typ);
        }
        if (AST_IsConst(rhs) && ((*(*lhs).typ).kind == 5)) {
          AST_CoerceToChar(&((*l)), rhs, (*lhs).typ);
        }
      } else {
        Lex_ErrorLn(&((*l)), "Expected INTEGER, REAL, SET, STRING, or CHAR", 45);
      }
      break;
    case 60:
    case 61:
      (*e).typ = booleanType;
      if (AST_ExprCompatable(&((*l)), op, lhs, rhs) && (AST_IsStringType((*lhs).typ) || ((1 << (*(*lhs).typ).kind) & 4588))) {
        if (AST_IsConst(lhs) && AST_IsConst(rhs)) {
        }
        if (AST_IsConst(lhs) && ((*(*rhs).typ).kind == 5)) {
          AST_CoerceToChar(&((*l)), lhs, (*rhs).typ);
        }
        if (AST_IsConst(rhs) && ((*(*lhs).typ).kind == 5)) {
          AST_CoerceToChar(&((*l)), rhs, (*lhs).typ);
        }
      } else {
        Lex_ErrorLn(&((*l)), "Expected INTEGER, REAL, SET, STRING, CHAR, POINTER, or PROCEDURE", 65);
      }
      break;
    case 17:
      (*e).typ = booleanType;
      if (((*(*lhs).typ).kind == 2) && ((*(*rhs).typ).kind == 6)) {
        if (AST_IsConst(lhs) && AST_IsConst(rhs)) {
        }
      } else {
        Lex_ErrorLn(&((*l)), "Expected INTEGER and SET expected", 34);
      }
      break;
    case 18:
      (*e).typ = booleanType;
      if (!(((1 << (*(*lhs).typ).kind) & 2304))) {
        Lex_ErrorLn(&((*l)), "LHS must be a POINTER or RECORD", 32);
      }
      if (!(((1 << (*(*rhs).typ).kind) & 2304))) {
        Lex_ErrorLn(&((*l)), "RHS must be a POINTER or RECORD", 32);
      }
      if ((*(*lhs).typ).kind != (*(*rhs).typ).kind) {
        Lex_ErrorLn(&((*l)), "LHS and RHS types must match", 29);
      }
      if (((*lhs).kind == 11) && (((*lhs).kind != 4) || ((*(*lhs).decl).kind != 7))) {
        Lex_ErrorLn(&((*l)), "LHS must be a VAR parameter", 28);
      }
      if (((*rhs).kind != 4) || ((*(*rhs).decl).kind != 3)) {
        Lex_ErrorLn(&((*l)), "RHS must be a type declaration", 31);
      }
      if (AST_Extends((*rhs).typ, (*lhs).typ) || AST_Extends((*(*rhs).typ).base, (*(*lhs).typ).base)) {
        AST_SetGenTypeInfo((*rhs).typ);
      } else {
        Lex_ErrorLn(&((*l)), "LHS and RHS types are unrelated", 32);
      }
      break;
  }
  return (e);
}

AST_Expr Parse_ParseTerm(void) {
  AST_Expr e;
  INTEGER op;
  e = Parse_ParseFactor();
  while (Parse_IsMulOperator()) {
    op = Parse_l.t.kind;
    Lex_NextToken(&(Parse_l));
    e = AST_NewExprBinary(&(Parse_l), op, e, Parse_ParseFactor(), Decls_booleanType);
  }
  return (e);
}

BOOLEAN Parse_IsAddOperator(void) {
  return (((Parse_IsToken(42) || Parse_IsToken(43)) || Parse_IsToken(24)));
}

AST_Expr Parse_ParseSimpleExpression(void) {
  AST_Expr e;
  INTEGER op;
  BOOLEAN unaryPlus;
  BOOLEAN unaryMinus;
  unaryPlus = 0;
  unaryMinus = 0;
  if (Parse_MatchToken(42)) {
    unaryPlus = 1;
  } else if (Parse_MatchToken(43)) {
    unaryMinus = 1;
  }
  e = Parse_ParseTerm();
  if (unaryPlus) {
    e = AST_NewExprUnary(&(Parse_l), 42, e);
  }
  if (unaryMinus) {
    e = AST_NewExprUnary(&(Parse_l), 43, e);
  }
  while (Parse_IsAddOperator()) {
    op = Parse_l.t.kind;
    Lex_NextToken(&(Parse_l));
    e = AST_NewExprBinary(&(Parse_l), op, e, Parse_ParseTerm(), Decls_booleanType);
  }
  return (e);
}

BOOLEAN Parse_IsRelation(void) {
  return ((((((((Parse_IsToken(60) || Parse_IsToken(61)) || Parse_IsToken(62)) || Parse_IsToken(64)) || Parse_IsToken(63)) || Parse_IsToken(65)) || Parse_IsToken(17)) || Parse_IsToken(18)));
}

AST_Expr Parse_ParseExpression0(void) {
  AST_Expr e;
  INTEGER op;
  e = Parse_ParseSimpleExpression();
  if (Parse_IsRelation()) {
    op = Parse_l.t.kind;
    Lex_NextToken(&(Parse_l));
    e = AST_NewExprBinary(&(Parse_l), op, e, Parse_ParseSimpleExpression(), Decls_booleanType);
  }
  return (e);
}

AST_Expr Parse_ParseBooleanExpression(void) {
  AST_Expr e;
  e = Parse_ParseExpression();
  if ((*(*e).typ).kind != 4) {
    Lex_ErrorLn(&(Parse_l), "BOOLEAN expected", 17);
  }
  return (e);
}

void AST_NewStmt(AST_Stmt  *s, INTEGER kind) {
  (*s) = malloc(sizeof(AST_StmtDesc));
  (*(*s)).kind = kind;
  (*(*s)).cond = (AST_Expr)(0);
  (*(*s)).body = (AST_Stmt)(0);
  (*(*s)).elsifs = (AST_Stmt)(0);
  (*(*s)).next = (AST_Stmt)(0);
}

AST_Stmt AST_NewStmtIf(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  ASSERT(((*(*cond).typ).kind == 4));
  AST_NewStmt(&(s), 3);
  (*s).cond = cond;
  (*s).body = body;
  return (s);
}

AST_Stmt AST_NewStmtElsIf(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  ASSERT(((*(*cond).typ).kind == 4));
  AST_NewStmt(&(s), 9);
  (*s).cond = cond;
  (*s).body = body;
  return (s);
}

AST_Stmt AST_NewStmtElse(AST_Stmt body) {
  AST_Stmt s;
  AST_NewStmt(&(s), 10);
  (*s).body = body;
  return (s);
}

AST_Stmt Parse_ParseIfStatement(void) {
  AST_Stmt s;
  AST_Stmt tail;
  AST_Expr cond;
  Parse_ExpectToken(15);
  cond = Parse_ParseBooleanExpression();
  Parse_ExpectToken(30);
  s = AST_NewStmtIf(cond, Parse_ParseStatementSequence());
  tail = s;
  while (Parse_MatchToken(11)) {
    cond = Parse_ParseBooleanExpression();
    Parse_ExpectToken(30);
    (*tail).elsifs = AST_NewStmtElsIf(cond, Parse_ParseStatementSequence());
    tail = (*tail).elsifs;
  }
  if (Parse_MatchToken(10)) {
    (*tail).elsifs = AST_NewStmtElse(Parse_ParseStatementSequence());
  }
  Parse_ExpectToken(12);
  return (s);
}

AST_Expr Parse_ParseCaseLabel(AST_Expr caseVar) {
  AST_Expr cond;
  cond = (AST_Expr)(0);
  if ((Parse_IsToken(40) || Parse_IsToken(39)) || Parse_IsToken(37)) {
    cond = AST_NewExprBinary(&(Parse_l), 60, caseVar, Parse_ParseFactor(), Decls_booleanType);
    if (!(AST_IsConst((*cond).rhs))) {
      Lex_ErrorLn(&(Parse_l), "CASE label must be constant", 28);
    }
  } else {
    Lex_ErrorLn(&(Parse_l), "Case label (INTEGER, STRING, IDENT) expected", 45);
  }
  return (cond);
}

AST_Expr Parse_ParseCaseLabelRange(AST_Expr caseVar) {
  AST_Expr cond;
  cond = Parse_ParseCaseLabel(caseVar);
  if (Parse_MatchToken(66)) {
    cond = AST_NewExprBinary(&(Parse_l), 69, cond, Parse_ParseCaseLabel(caseVar), Decls_booleanType);
  }
  return (cond);
}

AST_Expr Parse_ParseCaseLabelList(AST_Expr caseVar) {
  AST_Expr head;
  AST_Expr tail;
  head = Parse_ParseCaseLabelRange(caseVar);
  tail = head;
  while (Parse_MatchToken(49)) {
    (*tail).next = Parse_ParseCaseLabelRange(caseVar);
    tail = (*tail).next;
  }
  return (head);
}

AST_Stmt AST_NewStmtCaseItem(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  ASSERT(((*(*cond).typ).kind == 4));
  AST_NewStmt(&(s), 8);
  (*s).cond = cond;
  (*s).body = body;
  return (s);
}

AST_Stmt Parse_ParseCase(AST_Expr caseVar) {
  AST_Stmt s;
  AST_Expr cond;
  s = (AST_Stmt)(0);
  if ((Parse_IsToken(40) || Parse_IsToken(39)) || Parse_IsToken(37)) {
    cond = Parse_ParseCaseLabelList(caseVar);
    Parse_ExpectToken(67);
    s = AST_NewStmtCaseItem(cond, Parse_ParseStatementSequence());
  }
  return (s);
}

AST_Stmt AST_NewStmtCase(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  if (body != 0) {
    ASSERT(((*body).kind == 8));
  }
  AST_NewStmt(&(s), 7);
  (*s).cond = cond;
  (*s).elsifs = body;
  return (s);
}

AST_Stmt Parse_ParseCaseStatement(void) {
  AST_Expr cond;
  AST_Stmt s;
  AST_Stmt head;
  AST_Stmt tail;
  Parse_ExpectToken(6);
  cond = Parse_ParseExpression();
  if (!(((1 << (*(*cond).typ).kind) & 36))) {
    Lex_ErrorLn(&(Parse_l), "CASE requires INTEGER or CHAR", 30);
  }
  Parse_ExpectToken(23);
  head = Parse_ParseCase(cond);
  tail = head;
  while (Parse_MatchToken(51)) {
    s = Parse_ParseCase(cond);
    if (tail == 0) {
      head = s;
      tail = head;
    } else {
      (*tail).elsifs = s;
      if (s != 0) {
        tail = (*tail).elsifs;
      }
    }
  }
  Parse_ExpectToken(12);
  s = AST_NewStmtCase(cond, head);
  return (s);
}

AST_Stmt AST_NewStmtWhile(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  ASSERT(((*(*cond).typ).kind == 4));
  AST_NewStmt(&(s), 4);
  (*s).cond = cond;
  (*s).body = body;
  return (s);
}

AST_Stmt Parse_ParseWhileStatement(void) {
  AST_Stmt s;
  AST_Stmt tail;
  AST_Expr cond;
  Parse_ExpectToken(36);
  cond = Parse_ParseBooleanExpression();
  Parse_ExpectToken(9);
  s = AST_NewStmtWhile(cond, Parse_ParseStatementSequence());
  tail = s;
  while (Parse_MatchToken(11)) {
    cond = Parse_ParseBooleanExpression();
    Parse_ExpectToken(9);
    (*tail).elsifs = AST_NewStmtElsIf(cond, Parse_ParseStatementSequence());
    tail = (*tail).elsifs;
  }
  Parse_ExpectToken(12);
  return (s);
}

AST_Stmt AST_NewStmtRepeat(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  ASSERT(((*(*cond).typ).kind == 4));
  AST_NewStmt(&(s), 5);
  (*s).cond = cond;
  (*s).body = body;
  return (s);
}

AST_Stmt Parse_ParseRepeatStatement(void) {
  AST_Stmt s;
  Parse_ExpectToken(28);
  s = Parse_ParseStatementSequence();
  Parse_ExpectToken(34);
  s = AST_NewStmtRepeat(Parse_ParseBooleanExpression(), s);
  return (s);
}

AST_Expr AST_NewExprAssign(struct Lex_Lexer  *l, AST_Expr lValue, AST_Expr rValue) {
  AST_Expr e;
  AST_NewExpr(&(e), 12, (*lValue).typ);
  if (!((*lValue).assignable)) {
    Lex_ErrorLn(&((*l)), "lvalue of assignment is not assignable", 39);
  }
  if (AST_ExprCompatable(&((*l)), 58, lValue, rValue)) {
    (*e).lhs = lValue;
    (*e).rhs = rValue;
  }
  if (AST_IsConst(rValue) && ((*(*lValue).typ).kind == 5)) {
    AST_CoerceToChar(&((*l)), rValue, (*lValue).typ);
  }
  return (e);
}

AST_Stmt AST_NewStmtFor(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  ASSERT(((*cond).kind == 12));
  ASSERT(((1 << (*(*cond).typ).kind) & 12));
  AST_NewStmt(&(s), 6);
  (*s).cond = cond;
  (*s).body = body;
  return (s);
}

AST_Stmt Parse_ParseForStatement(void) {
  AST_Decl d;
  AST_Expr startExpr;
  AST_Expr endExpr;
  AST_Expr byExpr;
  AST_Stmt s;
  Parse_ExpectToken(14);
  d = Decls_LookupDecl(&(Parse_l), Parse_ExpectIdentifier());
  startExpr = AST_NewExprIdentRef(d);
  Parse_ExpectToken(58);
  startExpr = AST_NewExprAssign(&(Parse_l), startExpr, Parse_ParseExpression());
  Parse_ExpectToken(31);
  endExpr = AST_NewExprAssign(&(Parse_l), (*startExpr).lhs, Parse_ParseExpression());
  endExpr = (*endExpr).rhs;
  byExpr = (AST_Expr)(0);
  if (Parse_MatchToken(5)) {
    byExpr = AST_NewExprAssign(&(Parse_l), (*startExpr).lhs, Parse_ParseExpression());
    byExpr = (*byExpr).rhs;
  }
  (*startExpr).next = endExpr;
  (*endExpr).next = byExpr;
  Parse_ExpectToken(9);
  s = AST_NewStmtFor(startExpr, Parse_ParseStatementSequence());
  Parse_ExpectToken(12);
  return (s);
}

void Decls_NewDecl(AST_Decl  *d, INTEGER name) {
  (*d) = malloc(sizeof(AST_DeclDesc));
  (*(*d)).qname.name = name;
  (*(*d)).qname.moduleName = AST_currentModuleName;
  (*(*d)).kind = 0;
  (*(*d)).typ = (AST_Type)(0);
  (*(*d)).expr = (AST_Expr)(0);
  (*(*d)).body = (AST_Stmt)(0);
  (*(*d)).next = (AST_Decl)(0);
  (*(*d)).nesting = 0;
  (*(*d)).procVars = (AST_Decl)(0);
  (*(*d)).exported = 0;
  (*(*d)).isNative = 0;
  (*(*d)).state = 0;
  (*(*d)).offset = -1;
}

AST_Decl Decls_AddDecl(struct Lex_Lexer  *l, AST_Decl  *chain, INTEGER name) {
  AST_Decl p;
  AST_Decl d;
  Decls_NewDecl(&(d), name);
  if ((*chain) == 0) {
    Decls_NewDecl(&((*chain)), 0);
    (*(*chain)).kind = 1001;
  }
  if ((*(*chain)).kind == 1001) {
    (*d).next = (*chain);
    (*chain) = d;
  } else {
    p = (*chain);
    while (((*(*p).next).kind != 1001) && ((*p).qname.name != name)) {
      p = (*p).next;
    }
    if ((*p).qname.name == name) {
      Lex_Error(&((*l)), "", 1);
      Lex_OutStr(&((*l)), name);
      Lex_PrintLn(" already defined", 17);
    } else {
      (*d).next = (*p).next;
      (*p).next = d;
    }
  }
  return (d);
}

AST_Decl Decls_AddScopeDecl(struct Lex_Lexer  *l, INTEGER name) {
  return (Decls_AddDecl(&((*l)), &(Decls_scope), name));
}

AST_Stmt AST_NewStmtAssign(AST_Expr e) {
  AST_Stmt s;
  ASSERT(((*e).kind == 12));
  AST_NewStmt(&(s), 1);
  (*s).cond = e;
  return (s);
}

AST_Stmt Parse_ParseVarStatement(void) {
  AST_Decl d;
  AST_Expr e;
  Parse_ExpectToken(35);
  d = Decls_AddScopeDecl(&(Parse_l), Parse_ExpectIdentifier());
  (*d).kind = 4;
  (*d).nesting = Parse_nesting;
  Parse_ExpectToken(58);
  e = Parse_ParseExpression();
  (*d).typ = (*e).typ;
  e = AST_NewExprAssign(&(Parse_l), AST_NewExprIdentRef(d), e);
  return (AST_NewStmtAssign(e));
}

AST_Stmt AST_NewStmtProcCall(AST_Expr e) {
  AST_Stmt s;
  ASSERT(((1 << (*e).kind) & 2080));
  AST_NewStmt(&(s), 2);
  (*s).cond = e;
  return (s);
}

AST_Stmt Parse_ParseAssignOrProcCall(void) {
  AST_Expr e;
  AST_Expr args;
  AST_Stmt s;
  e = Parse_ParseDesignator();
  if (Parse_MatchToken(58)) {
    e = AST_NewExprAssign(&(Parse_l), e, Parse_ParseExpression());
    s = AST_NewStmtAssign(e);
  } else {
    args = (AST_Expr)(0);
    if (Parse_IsToken(52)) {
      args = Parse_ParseActualParameters();
    }
    e = AST_NewExprProcCall(&(Parse_l), e, args);
    s = AST_NewStmtProcCall(e);
  }
  return (s);
}

AST_Stmt AST_NewStmtEmpty(void) {
  AST_Stmt s;
  AST_NewStmt(&(s), 11);
  return (s);
}

AST_Stmt Parse_ParseStatement(void) {
  AST_Stmt s;
  if (Parse_IsToken(15)) {
    s = Parse_ParseIfStatement();
  } else if (Parse_IsToken(6)) {
    s = Parse_ParseCaseStatement();
  } else if (Parse_IsToken(36)) {
    s = Parse_ParseWhileStatement();
  } else if (Parse_IsToken(28)) {
    s = Parse_ParseRepeatStatement();
  } else if (Parse_IsToken(14)) {
    s = Parse_ParseForStatement();
  } else if (Parse_IsToken(35) && Parse_allowLanguageExtensions) {
    s = Parse_ParseVarStatement();
  } else if (Parse_IsToken(37)) {
    s = Parse_ParseAssignOrProcCall();
  } else {
    s = AST_NewStmtEmpty();
  }
  return (s);
}

AST_Stmt Parse_ParseStatementSequence0(void) {
  AST_Stmt head;
  AST_Stmt tail;
  head = Parse_ParseStatement();
  tail = head;
  while (Parse_MatchToken(50)) {
    (*tail).next = Parse_ParseStatement();
    tail = (*tail).next;
  }
  return (head);
}

AST_Type Parse_ParseQualidentAndGetType(void) {
  AST_Decl d;
  AST_Type t;
  t = (AST_Type)(0);
  d = Parse_ParseQualident();
  if (d != 0) {
    t = (*d).typ;
    if ((*d).kind != 3) {
      Lex_Error(&(Parse_l), "", 1);
      Lex_OutStr(&(Parse_l), (*d).qname.name);
      Lex_PrintLn(" is not a TYPE", 15);
    }
  }
  return (t);
}

void Decls_NewType(AST_Type  *t, INTEGER kind) {
  (*t) = malloc(sizeof(AST_TypeDesc));
  (*(*t)).kind = kind;
  (*(*t)).base = (AST_Type)(0);
  (*(*t)).fields = (AST_Decl)(0);
  (*(*t)).length = 0;
  (*(*t)).needTypeInfo = 0;
  (*(*t)).decl = (AST_Decl)(0);
  (*(*t)).reachable = 0;
}

AST_Type Decls_NewBufferType(AST_Type base) {
  AST_Type t;
  Decls_NewType(&(t), 10);
  (*t).length = -1;
  (*t).base = base;
  return (t);
}

AST_Type Decls_NewArrayType(struct Lex_Lexer  *l, AST_Expr length) {
  AST_Type t;
  Decls_NewType(&(t), 9);
  if (AST_IsConst(length) && ((*(*length).typ).kind == 2)) {
    (*t).length = (*length).iVal;
  } else {
    Lex_ErrorLn(&((*l)), "ARRAY length must be a CONST INTEGER", 37);
  }
  return (t);
}

AST_Type Parse_ParseArrayType(void) {
  AST_Type outer;
  AST_Type current;
  AST_Type last;
  AST_Expr e;
  Parse_ExpectToken(0);
  if (Parse_allowLanguageExtensions && Parse_MatchToken(44)) {
    Parse_ExpectToken(23);
    outer = Decls_NewBufferType(Parse_ParseType());
  } else {
    e = Parse_ParseExpression();
    outer = Decls_NewArrayType(&(Parse_l), e);
    ASSERT(((*e).iVal > 0));
    last = outer;
    while (Parse_MatchToken(49)) {
      e = Parse_ParseExpression();
      current = Decls_NewArrayType(&(Parse_l), e);
      ASSERT(((*e).iVal > 0));
      (*last).base = current;
      last = current;
    }
    Parse_ExpectToken(23);
    current = Parse_ParseType();
    (*last).base = current;
  }
  return (outer);
}

INTEGER AST_GetNextTypeId(void) {
  AST_nextTypeId++;
  return (AST_nextTypeId);
}

void AST_SetRecordToParent(INTEGER tid, INTEGER base) {
  AST_recordToParent[tid] = base;
}

AST_Type Decls_NewRecordType(struct Lex_Lexer  *l, AST_Type base) {
  AST_Type t;
  AST_Decl d;
  AST_Decl dCopy;
  Decls_NewType(&(t), 11);
  (*t).base = base;
  (*t).typeId = AST_GetNextTypeId();
  if (base == 0) {
    AST_SetRecordToParent((*t).typeId, 0);
  } else {
    AST_SetRecordToParent((*t).typeId, (*base).typeId);
  }
  if (base != 0) {
    if ((*base).kind == 11) {
      d = (*base).fields;
      while ((d != 0) && ((*d).kind != 1001)) {
        dCopy = Decls_AddDecl(&((*l)), &((*t).fields), (*d).qname.name);
        (*dCopy).kind = (*d).kind;
        (*dCopy).typ = (*d).typ;
        (*dCopy).exported = (*d).exported;
        d = (*d).next;
      }
    } else {
      Lex_ErrorLn(&((*l)), "RECORD base type is not a RECORD", 33);
    }
  }
  return (t);
}

AST_Decl Parse_ParseFieldIdentDef(AST_Decl  *recordScope) {
  AST_Decl d;
  INTEGER name;
  name = Parse_ExpectIdentifier();
  d = Decls_AddDecl(&(Parse_l), &((*recordScope)), name);
  if (Parse_MatchToken(44)) {
    (*d).exported = 1;
  }
  return (d);
}

AST_Type Parse_ParseRecordType(void) {
  AST_Type r;
  AST_Type base;
  AST_Type fieldType;
  AST_Decl baseDecl;
  AST_Decl firstField;
  AST_Decl lastField;
  BOOLEAN isNative;
  base = (AST_Type)(0);
  Parse_ExpectToken(27);
  if (Parse_MatchToken(52)) {
    baseDecl = Parse_ParseQualident();
    Parse_ExpectToken(53);
    if (baseDecl != 0) {
      base = (*baseDecl).typ;
    }
  }
  r = Decls_NewRecordType(&(Parse_l), base);
  if (Parse_IsToken(37)) {
    do {
      firstField = Parse_ParseFieldIdentDef(&((*r).fields));
      lastField = firstField;
      while (Parse_MatchToken(49)) {
        lastField = Parse_ParseFieldIdentDef(&((*r).fields));
      }
      Parse_ExpectToken(67);
      isNative = Parse_MatchToken(21);
      fieldType = Parse_ParseType();
      while (((firstField != 0) && (lastField != 0)) && (firstField != (*lastField).next)) {
        (*firstField).kind = 8;
        (*firstField).typ = fieldType;
        (*firstField).isNative = isNative;
        firstField = (*firstField).next;
      }
      Parse_MatchToken(50);
    } while (!(Parse_IsToken(12) || Parse_IsToken(70)));
  }
  Parse_ExpectToken(12);
  return (r);
}

void Lex_MakeDummy(INTEGER i, CHAR s[], size_t s__len) {
  (void)s__len;
  s[0] = 'i';
  s[4] = ((char)((i % 10) + 48));
  i = (i / 10);
  s[3] = ((char)((i % 10) + 48));
  i = (i / 10);
  s[2] = ((char)((i % 10) + 48));
  i = (i / 10);
  s[1] = ((char)((i % 10) + 48));
  s[5] = '\0';
}

INTEGER Lex_Intern(struct Lex_Lexer  *l, CHAR s[], size_t s__len) {
  (void)s__len;
  return (Lex_StringIntern(&((*l).sp), s, s__len));
}

void Decls_MakeSyntheticDecl(struct Lex_Lexer  *l, AST_Type base) {
  CHAR name[10];
  ASSERT(((*base).kind == 11));
  if ((*base).decl == 0) {
    Lex_MakeDummy(Decls_genSymNum, name, 10);
    Decls_NewDecl(&((*base).decl), Lex_Intern(&((*l)), name, 10));
    (*(*base).decl).kind = 3;
    (*(*base).decl).typ = base;
    Decls_genSymNum++;
  }
}

AST_Type Decls_NewPointerType(struct Lex_Lexer  *l, AST_Type base) {
  AST_Type t;
  t = (AST_Type)(0);
  if ((base != 0) && ((*base).kind != 11)) {
    Lex_ErrorLn(&((*l)), "Pointer base type must be a RECORD", 35);
  } else {
    Decls_MakeSyntheticDecl(&((*l)), base);
    Decls_NewType(&(t), 8);
    (*t).base = base;
  }
  return (t);
}

AST_Type Decls_NewPointerTypeByName(struct Lex_Lexer  *l, INTEGER name) {
  AST_Decl d;
  Decls_Forward f;
  AST_Type t;
  t = (AST_Type)(0);
  d = Decls_LookupDecl0(name);
  if (d == 0) {
    Decls_NewType(&(t), 8);
    Decls_NewDecl(&((*t).fields), name);
    f = malloc(sizeof(Decls_FwdDecl));
    (*f).t = t;
    (*f).next = Decls_fwds;
    Decls_fwds = f;
  } else {
    if ((*d).kind != 3) {
      Lex_Error(&((*l)), "", 1);
      Lex_OutStr(&((*l)), (*d).qname.name);
      Lex_PrintLn(" is not a TYPE", 15);
    }
    t = Decls_NewPointerType(&((*l)), (*d).typ);
  }
  return (t);
}

AST_Type Parse_ParsePointerType(void) {
  AST_Type t;
  Parse_ExpectToken(25);
  Parse_ExpectToken(31);
  if (Parse_IsToken(37)) {
    t = Decls_NewPointerTypeByName(&(Parse_l), Parse_ExpectIdentifier());
  } else {
    t = Decls_NewPointerType(&(Parse_l), Parse_ParseType());
  }
  return (t);
}

AST_Type Decls_NewProcedureType(void) {
  AST_Type t;
  Decls_NewType(&(t), 12);
  (*t).base = Decls_nilType;
  return (t);
}

void Parse_ParseFPSection(AST_Type procType) {
  INTEGER name;
  AST_Decl firstParam;
  AST_Decl lastParam;
  AST_Type paramType;
  AST_Type arrType;
  BOOLEAN varParameter;
  BOOLEAN openArr;
  varParameter = Parse_MatchToken(35);
  openArr = 0;
  name = Parse_ExpectIdentifier();
  firstParam = Decls_AddDecl(&(Parse_l), &((*procType).fields), name);
  lastParam = firstParam;
  if (varParameter) {
    (*firstParam).kind = 7;
  } else {
    (*firstParam).kind = 6;
  }
  while (Parse_MatchToken(49)) {
    name = Parse_ExpectIdentifier();
    lastParam = Decls_AddDecl(&(Parse_l), &((*procType).fields), name);
    if (varParameter) {
      (*lastParam).kind = 7;
    } else {
      (*lastParam).kind = 6;
    }
  }
  Parse_ExpectToken(67);
  if (Parse_MatchToken(0)) {
    Parse_ExpectToken(23);
    openArr = 1;
  }
  paramType = Parse_ParseQualidentAndGetType();
  if (openArr) {
    arrType = Decls_NewArrayType(&(Parse_l), AST_NewExprInteger(0, Decls_integerType));
    (*arrType).base = paramType;
    paramType = arrType;
  }
  while (((firstParam != 0) && (lastParam != 0)) && (firstParam != (*lastParam).next)) {
    (*firstParam).typ = paramType;
    firstParam = (*firstParam).next;
  }
}

void Decls_CountProcedureArgs(AST_Type t) {
  INTEGER i;
  AST_Decl p;
  i = 0;
  p = (*t).fields;
  while ((p != 0) && ((*p).kind != 1001)) {
    i++;
    p = (*p).next;
  }
  (*t).length = i;
}

AST_Type Parse_ParseFormalParameters(void) {
  AST_Type t;
  t = Decls_NewProcedureType();
  if (Parse_MatchToken(52)) {
    if (Parse_IsToken(35) || Parse_IsToken(37)) {
      Parse_ParseFPSection(t);
    }
    while (Parse_MatchToken(50)) {
      Parse_ParseFPSection(t);
    }
    Parse_ExpectToken(53);
    if (Parse_MatchToken(67)) {
      (*t).base = Parse_ParseQualidentAndGetType();
    }
  }
  Decls_CountProcedureArgs(t);
  return (t);
}

AST_Type Parse_ParseProcedureType(void) {
  Parse_ExpectToken(26);
  return (Parse_ParseFormalParameters());
}

AST_Type Parse_ParseType0(void) {
  AST_Type t;
  t = (AST_Type)(0);
  if (Parse_IsToken(37)) {
    t = Parse_ParseQualidentAndGetType();
  } else if (Parse_IsToken(0)) {
    t = Parse_ParseArrayType();
  } else if (Parse_IsToken(27)) {
    t = Parse_ParseRecordType();
  } else if (Parse_IsToken(25)) {
    t = Parse_ParsePointerType();
  } else if (Parse_IsToken(26)) {
    t = Parse_ParseProcedureType();
  } else {
    Lex_ErrorLn(&(Parse_l), "Identifier, ARRAY, RECORD, POINTER, or PROCEDURE expected", 58);
  }
  return (t);
}

AST_Decl Parse_ParseIdentDef(void) {
  AST_Decl d;
  INTEGER n;
  n = Parse_ExpectIdentifier();
  d = Decls_AddScopeDecl(&(Parse_l), n);
  (*d).nesting = Parse_nesting;
  if (Parse_MatchToken(44)) {
    (*d).exported = 1;
  }
  return (d);
}

void Parse_ParseConstDeclaration(void) {
  AST_Decl d;
  AST_Expr e;
  d = Parse_ParseIdentDef();
  Parse_ExpectToken(60);
  e = Parse_ParseExpression();
  (*d).kind = 2;
  (*d).typ = (*e).typ;
  (*d).expr = e;
  if (!(AST_IsConst(e))) {
    Lex_ErrorLn(&(Parse_l), "CONST declaration is not constant", 34);
  }
}

void Parse_ParseTypeDeclaration(void) {
  AST_Decl d;
  d = Parse_ParseIdentDef();
  Parse_ExpectToken(60);
  (*d).kind = 3;
  (*d).typ = Parse_ParseType();
  if ((*(*d).typ).decl == 0) {
    (*(*d).typ).decl = d;
  }
}

void Decls_ResolveForwards(struct Lex_Lexer  *l) {
  AST_Decl d;
  while (Decls_fwds != 0) {
    ASSERT(((*(*Decls_fwds).t).kind == 8));
    d = Decls_LookupDecl(&((*l)), (*(*(*Decls_fwds).t).fields).qname.name);
    if (((d != 0) && ((*d).kind == 3)) && ((*(*d).typ).kind == 11)) {
      (*(*Decls_fwds).t).base = (*d).typ;
      (*(*Decls_fwds).t).fields = (AST_Decl)(0);
    } else {
      Lex_Error(&((*l)), "Bad forward declaration ", 25);
      Lex_OutStr(&((*l)), (*(*(*Decls_fwds).t).fields).qname.name);
      Lex_Ln();
    }
    Decls_fwds = (*Decls_fwds).next;
  }
}

void Parse_ParseVarDeclaration(void) {
  AST_Decl first;
  AST_Decl last;
  AST_Type t;
  first = Parse_ParseIdentDef();
  last = first;
  while (Parse_MatchToken(49)) {
    last = Parse_ParseIdentDef();
  }
  Parse_ExpectToken(67);
  t = Parse_ParseType();
  while (((first != 0) && (last != 0)) && (first != (*last).next)) {
    (*first).kind = 4;
    (*first).typ = t;
    first = (*first).next;
  }
}

AST_Decl Parse_ParseProcedureHeading(void) {
  AST_Decl d;
  BOOLEAN isNative;
  AST_Expr e;
  isNative = Parse_MatchToken(21);
  if (isNative) {
    e = Parse_ParseExpression();
    ASSERT(((*e).iVal < 0));
  }
  Parse_ExpectToken(26);
  d = Parse_ParseIdentDef();
  (*d).kind = 5;
  (*d).typ = Parse_ParseFormalParameters();
  (*d).isNative = isNative;
  if (isNative) {
    (*d).offset = (*e).iVal;
  }
  return (d);
}

AST_Decl Decls_OpenScope(void) {
  AST_Decl d;
  AST_Decl oldScope;
  Decls_NewDecl(&(d), 0);
  (*d).kind = 1001;
  (*d).next = Decls_scope;
  oldScope = Decls_scope;
  Decls_scope = d;
  return (oldScope);
}

void Decls_AddFormalParamsToScope(struct Lex_Lexer  *l, AST_Decl procDecl) {
  AST_Decl formal;
  AST_Decl actual;
  ASSERT(((*procDecl).kind == 5));
  ASSERT(((*(*procDecl).typ).kind == 12));
  formal = (*(*procDecl).typ).fields;
  while (formal != 0) {
    actual = Decls_AddScopeDecl(&((*l)), (*formal).qname.name);
    (*actual).kind = (*formal).kind;
    (*actual).typ = (*formal).typ;
    formal = (*formal).next;
  }
}

AST_Expr AST_ValidateReturnStatement(struct Lex_Lexer  *l, AST_Decl procDecl, AST_Expr e) {
  ASSERT(((*procDecl).kind == 5));
  ASSERT(((*(*procDecl).typ).kind == 12));
  if ((*(*(*procDecl).typ).base).kind == 1) {
    Lex_ErrorLn(&((*l)), "RETURN statement unexpected", 28);
  }
  if ((*(*e).typ).kind != 1) {
    AST_ExpectType(&((*l)), e, (*(*(*procDecl).typ).base).kind);
  }
  return (e);
}

AST_Decl Decls_CurrentScope(void) {
  return (Decls_scope);
}

void Decls_CloseScope(AST_Decl s) {
  Decls_scope = s;
}

void Parse_ParseProcedureBody(AST_Decl procDecl) {
  AST_Decl oldScope;
  oldScope = Decls_OpenScope();
  Parse_nesting++;
  Decls_AddFormalParamsToScope(&(Parse_l), procDecl);
  Parse_ParseDeclarationSequence();
  if (Parse_MatchToken(1)) {
    (*procDecl).body = Parse_ParseStatementSequence();
  }
  if (Parse_MatchToken(29)) {
    (*procDecl).expr = AST_ValidateReturnStatement(&(Parse_l), procDecl, Parse_ParseExpression());
  }
  Parse_ExpectToken(12);
  (*procDecl).procVars = Decls_CurrentScope();
  Parse_nesting--;
  Decls_CloseScope(oldScope);
}

void Parse_ParseProcedureDeclaration(void) {
  AST_Decl d;
  INTEGER endName;
  d = Parse_ParseProcedureHeading();
  Parse_ExpectToken(50);
  Parse_ParseProcedureBody(d);
  endName = Parse_ExpectIdentifier();
  if ((*d).qname.name != endName) {
    Lex_Error(&(Parse_l), "Procedure end name [", 21);
    Lex_OutStr(&(Parse_l), endName);
    Lex_Str("] must match start name [", 26);
    Lex_OutStr(&(Parse_l), (*d).qname.name);
    Lex_PrintLn("]", 2);
  }
}

void Parse_ParseDeclarationSequence0(void) {
  if (Parse_MatchToken(7)) {
    while (Parse_IsToken(37)) {
      Parse_ParseConstDeclaration();
      Parse_ExpectToken(50);
    }
  }
  if (Parse_MatchToken(33)) {
    while (Parse_IsToken(37)) {
      Parse_ParseTypeDeclaration();
      Parse_ExpectToken(50);
    }
  }
  Decls_ResolveForwards(&(Parse_l));
  if (Parse_MatchToken(35)) {
    while (Parse_IsToken(37)) {
      Parse_ParseVarDeclaration();
      Parse_ExpectToken(50);
    }
  }
  while (Parse_IsToken(26) || Parse_IsToken(21)) {
    Parse_ParseProcedureDeclaration();
    Parse_ExpectToken(50);
  }
}

void Decls_AddTypeDecl(struct Lex_Lexer  *l, INTEGER name, AST_Type t) {
  AST_Decl d;
  d = Decls_AddDecl(&((*l)), &(Decls_scope), name);
  (*d).kind = 3;
  (*d).typ = t;
  if ((*(*d).typ).decl == 0) {
    (*(*d).typ).decl = d;
  }
}

void Decls_AddBuiltin(struct Lex_Lexer  *l, INTEGER name, AST_BuiltinResolver callback) {
  AST_Decl d;
  d = Decls_AddDecl(&((*l)), &(Decls_scope), name);
  (*d).kind = 9;
  (*d).typ = Decls_nilType;
  (*d).resolver = callback;
}

AST_Expr Decls_builtinAbs(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 1;
  (*e).rhs = args;
  if ((args == 0) || ((*args).next != 0)) {
    Lex_ErrorLn(&((*l)), "ABS expects 1 argument", 23);
  }
  if ((1 << (*(*args).typ).kind) & 12) {
    (*e).typ = (*args).typ;
  } else {
    Lex_ErrorLn(&((*l)), "ABS expects INTEGER or REAL", 28);
  }
  return (e);
}

AST_Expr Decls_builtinInc(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 7;
  (*e).rhs = args;
  if ((args == 0) || (((*args).next != 0) && ((*(*args).next).next != 0))) {
    Lex_ErrorLn(&((*l)), "INC expects 1 or 2 arguments", 29);
  }
  if (!((*args).assignable)) {
    Lex_ErrorLn(&((*l)), "First argument to INC must be assignable", 41);
  }
  if (((*args).next != 0) && ((*(*(*args).next).typ).kind != 2)) {
    Lex_ErrorLn(&((*l)), "Second arg to INC must be an INTEGER", 37);
  }
  return (e);
}

AST_Expr Decls_builtinDec(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 4;
  (*e).rhs = args;
  if ((args == 0) || (((*args).next != 0) && ((*(*args).next).next != 0))) {
    Lex_ErrorLn(&((*l)), "DEC expects 1 or 2 arguments", 29);
  }
  if (!((*args).assignable)) {
    Lex_ErrorLn(&((*l)), "First argument to DEC must be assignable", 41);
  }
  if (((*args).next != 0) && ((*(*(*args).next).typ).kind != 2)) {
    Lex_ErrorLn(&((*l)), "Second arg to DEC must be an INTEGER", 37);
  }
  return (e);
}

AST_Expr Decls_builtinAssert(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 2;
  (*e).rhs = args;
  if ((args == 0) || ((*args).next != 0)) {
    Lex_ErrorLn(&((*l)), "ASSERT expects 1 argument", 26);
  }
  if ((*(*args).typ).kind == 4) {
    (*e).typ = (*args).typ;
  } else {
    Lex_ErrorLn(&((*l)), "ASSERT expects a BOOLEAN", 25);
  }
  return (e);
}

AST_Expr Decls_builtinOrd(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 10;
  (*e).rhs = args;
  if (AST_IsConst((*e).rhs)) {
    AST_CoerceToChar(&((*l)), (*e).rhs, Decls_charType);
  }
  if ((args == 0) || ((*args).next != 0)) {
    Lex_ErrorLn(&((*l)), "ORD expects 1 argument", 23);
  }
  if (((1 << (*(*args).typ).kind) & 112) || (((*(*args).typ).kind == 7) && Lex_IsOneChar(&((*l)), (*args).iVal))) {
    (*e).typ = Decls_integerType;
  } else {
    Lex_ErrorLn(&((*l)), "ORD expects CHAR, BOOLEAN, or SET", 34);
  }
  return (e);
}

AST_Expr Decls_builtinChr(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 3;
  (*e).rhs = args;
  if ((args == 0) || ((*args).next != 0)) {
    Lex_ErrorLn(&((*l)), "CHR expects 1 argument", 23);
  }
  if ((*(*args).typ).kind == 2) {
    (*e).typ = Decls_charType;
  } else {
    Lex_ErrorLn(&((*l)), "CHR expects an INTEGER", 23);
  }
  return (e);
}

AST_Expr Decls_builtinFlt(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 5;
  (*e).rhs = args;
  if ((args == 0) || ((*args).next != 0)) {
    Lex_ErrorLn(&((*l)), "FLT expects 1 argument", 23);
  }
  if ((*(*args).typ).kind == 2) {
    (*e).typ = Decls_realType;
  } else {
    Lex_ErrorLn(&((*l)), "FLT expects an INTEGER", 23);
  }
  return (e);
}

AST_Expr Decls_builtinLen(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 8;
  (*e).rhs = args;
  if ((args == 0) || ((*args).next != 0)) {
    Lex_ErrorLn(&((*l)), "LEN expects 1 argument", 23);
  }
  if ((1 << (*(*args).typ).kind) & 1536) {
    (*e).typ = Decls_integerType;
  } else {
    Lex_ErrorLn(&((*l)), "LEN expects an ARRAY", 21);
  }
  return (e);
}

AST_Expr Decls_builtinNew(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 9;
  (*e).rhs = args;
  if ((args == 0) || ((*args).next != 0)) {
    Lex_ErrorLn(&((*l)), "NEW expects 1 argument", 23);
  }
  if (!((*args).assignable)) {
    Lex_ErrorLn(&((*l)), "First argument to NEW must be assignable", 41);
  }
  if ((*(*args).typ).kind == 8) {
    (*e).typ = (*args).typ;
  } else {
    Lex_ErrorLn(&((*l)), "NEW expects a POINTER", 22);
  }
  return (e);
}

AST_Expr Decls_builtinInit(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 6;
  (*e).rhs = args;
  if (((args == 0) || ((*args).next == 0)) || ((*(*args).next).next != 0)) {
    Lex_ErrorLn(&((*l)), "INIT expects 2 arguments", 25);
  }
  if ((*(*(*args).next).typ).kind != 2) {
    Lex_ErrorLn(&((*l)), "Second arg to INIT must be an INTEGER", 38);
  }
  if ((*(*args).typ).kind == 10) {
    (*e).typ = Decls_nilType;
  } else {
    Lex_ErrorLn(&((*l)), "First arg to INIT expects an ARRAY *", 37);
  }
  return (e);
}

AST_Expr Decls_builtinPush(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 11;
  (*e).rhs = args;
  if (((args == 0) || ((*args).next == 0)) || ((*(*args).next).next != 0)) {
    Lex_ErrorLn(&((*l)), "PUSH expects 2 arguments", 25);
  }
  if (!((*args).assignable)) {
    Lex_ErrorLn(&((*l)), "First argument to PUSH must be assignable", 42);
  }
  if ((*(*args).next).typ != (*(*args).typ).base) {
    Lex_ErrorLn(&((*l)), "Second arg to PUSH must have same type as ARRAY", 48);
  }
  if ((*(*args).typ).kind == 10) {
    (*e).typ = Decls_nilType;
  } else {
    Lex_ErrorLn(&((*l)), "First arg to PUSH expects an ARRAY *", 37);
  }
  return (e);
}

AST_Expr Decls_builtinReadInt(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 12;
  (*e).rhs = args;
  if ((args == 0) || ((*args).next != 0)) {
    Lex_ErrorLn(&((*l)), "ReadInt expects 1 argument", 27);
  }
  if (!((*args).assignable)) {
    Lex_ErrorLn(&((*l)), "Argument to ReadInt must be assignable", 39);
  }
  return (e);
}

AST_Expr Decls_builtinWriteInt(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 13;
  (*e).rhs = args;
  if ((args == 0) || ((*args).next != 0)) {
    Lex_ErrorLn(&((*l)), "WriteInt expects 1 argument", 28);
  }
  return (e);
}

AST_Expr Decls_builtinWriteChar(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 14;
  (*e).rhs = args;
  if ((args == 0) || ((*args).next != 0)) {
    Lex_ErrorLn(&((*l)), "WriteChar expects 1 argument", 29);
  }
  if ((*(*(*e).rhs).typ).kind == 7) {
    AST_CoerceToChar(&((*l)), (*e).rhs, Decls_charType);
  }
  return (e);
}

AST_Expr Decls_builtinWriteLn(struct Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 15;
  (*e).rhs = args;
  if (args != 0) {
    Lex_ErrorLn(&((*l)), "WriteLn expects 0 argumens", 27);
  }
  return (e);
}

void Decls_InitGlobalScope(struct Lex_Lexer  *l) {
  Decls_fwds = (Decls_Forward)(0);
  if (Decls_globalScope == 0) {
    Decls_scope = (AST_Decl)(0);
    Decls_NewType(&(Decls_nilType), 1);
    Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "NIL", 4), Decls_nilType);
    Decls_NewType(&(Decls_integerType), 2);
    Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "INTEGER", 8), Decls_integerType);
    Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "BYTE", 5), Decls_integerType);
    Decls_NewType(&(Decls_realType), 3);
    Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "REAL", 5), Decls_realType);
    Decls_NewType(&(Decls_booleanType), 4);
    Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "BOOLEAN", 8), Decls_booleanType);
    Decls_NewType(&(Decls_charType), 5);
    Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "CHAR", 5), Decls_charType);
    Decls_NewType(&(Decls_setType), 6);
    Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "SET", 4), Decls_setType);
    Decls_NewType(&(Decls_stringType), 7);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "ABS", 4), Decls_builtinAbs);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "INC", 4), Decls_builtinInc);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "DEC", 4), Decls_builtinDec);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "ASSERT", 7), Decls_builtinAssert);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "ORD", 4), Decls_builtinOrd);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "CHR", 4), Decls_builtinChr);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "FLT", 4), Decls_builtinFlt);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "LEN", 4), Decls_builtinLen);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "NEW", 4), Decls_builtinNew);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "INIT", 5), Decls_builtinInit);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "PUSH", 5), Decls_builtinPush);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "ReadInt", 8), Decls_builtinReadInt);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "WriteInt", 9), Decls_builtinWriteInt);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "WriteChar", 10), Decls_builtinWriteChar);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "WriteLn", 8), Decls_builtinWriteLn);
    Decls_globalScope = Decls_scope;
    Decls_modInitName = Lex_Intern(&((*l)), "_module_init_", 14);
  }
  Decls_scope = Decls_globalScope;
}

INTEGER AST_SetModuleName(INTEGER name) {
  INTEGER oldModuleName;
  oldModuleName = AST_currentModuleName;
  AST_currentModuleName = name;
  return (oldModuleName);
}

void Lex_ImportHelper(struct Lex_Lexer  *l, INTEGER moduleName, Lex_LexCallback callback) {
  CHAR savedBuf[65536];
  INTEGER savedFileName;
  CHAR fileName[128];
  INTEGER savedPos;
  INTEGER i;
  Lex_Token savedToken;
  strncpy(savedBuf, (*l).buf, sizeof(savedBuf));
  savedFileName = (*l).fileName;
  savedPos = (*l).pos;
  memcpy(&(savedToken), &((*l).t), sizeof(savedToken));
  i = 0;
  while ((*l).sp.buf[(moduleName + i)] != '\0') {
    fileName[i] = (*l).sp.buf[(moduleName + i)];
    i++;
  }
  fileName[i] = '.';
  fileName[(i + 1)] = 'o';
  fileName[(i + 2)] = 'b';
  fileName[(i + 3)] = '\0';
  Out_ReadFile(fileName, 128, (*l).buf, 65536);
  (*l).fileName = Lex_StringIntern(&((*l).sp), fileName, 128);
  (*l).pos = 0;
  callback();
  memcpy(&((*l).t), &(savedToken), sizeof((*l).t));
  (*l).pos = savedPos;
  (*l).fileName = savedFileName;
  strncpy((*l).buf, savedBuf, sizeof((*l).buf));
}

AST_Decl Parse_GetModuleImports(INTEGER moduleName) {
  INTEGER i;
  AST_Decl d;
  i = 0;
  while ((i < Parse_importCacheEnd) && (Parse_importCache[i].name != moduleName)) {
    i++;
  }
  if (Parse_importCache[i].name == moduleName) {
    d = Parse_importCache[i].decls;
  } else {
    ASSERT((Parse_importCacheEnd < 128));
    Lex_ImportHelper(&(Parse_l), moduleName, Parse_importCallback);
    d = Parse_lastModuleDecls;
    Parse_importCache[Parse_importCacheEnd].name = moduleName;
    Parse_importCache[Parse_importCacheEnd].decls = d;
    Parse_importCacheEnd++;
  }
  return (d);
}

void Decls_AddImportDecl(struct Lex_Lexer  *l, INTEGER name, AST_Decl decls) {
  AST_Decl d;
  d = Decls_AddScopeDecl(&((*l)), name);
  (*d).kind = 1;
  Decls_NewType(&((*d).typ), 13);
  (*(*d).typ).fields = decls;
}

void Parse_ParseImport(void) {
  INTEGER name;
  INTEGER alias;
  AST_Decl d;
  name = Parse_ExpectIdentifier();
  alias = name;
  if (Parse_MatchToken(58)) {
    name = Parse_ExpectIdentifier();
  }
  d = Parse_GetModuleImports(name);
  Decls_AddImportDecl(&(Parse_l), alias, d);
}

void Parse_ParseImportList(void) {
  Parse_ExpectToken(16);
  Parse_ParseImport();
  while (Parse_MatchToken(49)) {
    Parse_ParseImport();
  }
  Parse_ExpectToken(50);
}

void Decls_NewModuleInitDecl(AST_Stmt body) {
  AST_Decl d;
  Decls_NewDecl(&(d), Decls_modInitName);
  (*d).kind = 5;
  (*d).typ = Decls_NewProcedureType();
  (*d).body = body;
  (*d).next = Decls_scope;
  Decls_scope = d;
}

void Parse_ParseModule(void) {
  INTEGER s;
  INTEGER e;
  INTEGER oldModule;
  AST_Decl d;
  Decls_InitGlobalScope(&(Parse_l));
  Parse_nesting = 0;
  Parse_ExpectToken(20);
  s = Parse_ExpectIdentifier();
  oldModule = AST_SetModuleName(s);
  d = Decls_OpenScope();
  Parse_ExpectToken(50);
  if (Parse_IsToken(16)) {
    Parse_ParseImportList();
  }
  Parse_ParseDeclarationSequence();
  if (Parse_MatchToken(1)) {
    Decls_NewModuleInitDecl(Parse_ParseStatementSequence());
  } else {
    Decls_NewModuleInitDecl((AST_Stmt )(0));
  }
  Parse_ExpectToken(12);
  e = Parse_ExpectIdentifier();
  if (s != e) {
    Lex_Error(&(Parse_l), "Module end name [", 18);
    Lex_OutStr(&(Parse_l), e);
    Lex_Str("] must match start name [", 26);
    Lex_OutStr(&(Parse_l), s);
    Lex_PrintLn("]", 2);
  }
  Parse_ExpectToken(48);
  Parse_lastModuleDecls = Decls_CurrentScope();
  AST_SetModuleName(oldModule);
  Decls_CloseScope(d);
}

void Parse_ImportHelper(void) {
  AST_Decl savedScope;
  savedScope = Decls_CurrentScope();
  Lex_NextToken(&(Parse_l));
  Parse_ParseModule();
  Decls_CloseScope(savedScope);
}

void Parse__module_init_(void) {
  Parse_importCacheEnd = 0;
  Parse_ParseExpression = Parse_ParseExpression0;
  Parse_ParseStatementSequence = Parse_ParseStatementSequence0;
  Parse_ParseType = Parse_ParseType0;
  Parse_ParseDeclarationSequence = Parse_ParseDeclarationSequence0;
  Parse_importCallback = Parse_ImportHelper;
  Parse_allowLanguageExtensions = 1;
}

void Lex_PoolInit(struct Lex_StringPool  *sp) {
  INTEGER i;
  (*sp).last = 0;
  for (i = 0; i <= 4095; i++) {
    (*sp).buckets[i] = -1;
  }
}

void Lex_InfoPrintLn(CHAR s[], size_t s__len) {
  (void)s__len;
  Out_Str(s, s__len);
  Out_Ln();
}

void Lex_TestPool(void) {
  Lex_StringPool sp;
  CHAR s[25];
  INTEGER i;
  INTEGER j;
  Lex_PoolInit(&(sp));
  ASSERT((11 == Lex_StringLen("Hello world", 12)));
  strncpy(s, "Hello world", sizeof(s));
  ASSERT(Lex_StrEq(s, 25, 0, "Hello world", 12, 0, 11));
  ASSERT(!(Lex_StrEq(s, 25, 0, "Hello", 6, 0, 11)));
  ASSERT(Lex_StrEq(s, 25, 1, "Hello world", 12, 1, 10));
  ASSERT((11 == Lex_StringLen(s, 25)));
  ASSERT((Lex_StringIntern(&(sp), s, 25) == 0));
  strncpy(s, "Yello world", sizeof(s));
  ASSERT((Lex_StringIntern(&(sp), s, 25) == 12));
  i = Lex_StringInternRange(&(sp), "Hellooo", 8, 1, 4);
  ASSERT((i == Lex_StringIntern(&(sp), "ello", 5)));
  j = Lex_StringInternRange(&(sp), s, 25, 0, 0);
  ASSERT((i != j));
  ASSERT((Lex_StringIntern(&(sp), "", 1) == j));
  s[0] = 'A';
  s[1] = '\0';
  ASSERT((Lex_StringIntern(&(sp), s, 25) == Lex_StringIntern(&(sp), "A", 2)));
  ASSERT((Lex_StringIntern(&(sp), s, 25) != Lex_StringIntern(&(sp), "B", 2)));
  Lex_PoolInit(&(sp));
  for (i = 1; i <= 4000; i++) {
    Lex_MakeDummy(i, s, 25);
    Lex_StringIntern(&(sp), s, 25);
  }
  for (i = 1; i <= 4000; i++) {
    Lex_MakeDummy(i, s, 25);
    ASSERT((Lex_StringIntern(&(sp), s, 25) == ((i - 1) * 6)));
  }
  ASSERT((sp.last == 24000));
  Lex_PoolInit(&(sp));
  Lex_StringInternRange(&(sp), "A", 2, 0, 9);
  Lex_StringInternRange(&(sp), "PROCEDURE", 10, 0, 9);
  Lex_StringInternRange(&(sp), "B", 2, 0, 9);
  ASSERT((Lex_StringIntern(&(sp), "A", 2) == 0));
  ASSERT((Lex_StringIntern(&(sp), "PROCEDURE", 10) == 10));
  ASSERT((Lex_StringIntern(&(sp), "B", 2) == 20));
  Lex_InfoPrintLn("PASS: String pool test", 23);
}

void Lex_Mute(void) {
  Out_Mute();
  Lex_fatal = 0;
}

void Lex_AddKeywords(struct Lex_StringPool  *sp) {
  Lex_StringInternRange(&((*sp)), "ARRAY", 6, 0, 9);
  Lex_StringInternRange(&((*sp)), "BEGIN", 6, 0, 9);
  Lex_StringInternRange(&((*sp)), "BITAND", 7, 0, 9);
  Lex_StringInternRange(&((*sp)), "BITOR", 6, 0, 9);
  Lex_StringInternRange(&((*sp)), "BITXOR", 7, 0, 9);
  Lex_StringInternRange(&((*sp)), "BY", 3, 0, 9);
  Lex_StringInternRange(&((*sp)), "CASE", 5, 0, 9);
  Lex_StringInternRange(&((*sp)), "CONST", 6, 0, 9);
  Lex_StringInternRange(&((*sp)), "DIV", 4, 0, 9);
  Lex_StringInternRange(&((*sp)), "DO", 3, 0, 9);
  Lex_StringInternRange(&((*sp)), "ELSE", 5, 0, 9);
  Lex_StringInternRange(&((*sp)), "ELSIF", 6, 0, 9);
  Lex_StringInternRange(&((*sp)), "END", 4, 0, 9);
  Lex_StringInternRange(&((*sp)), "FALSE", 6, 0, 9);
  Lex_StringInternRange(&((*sp)), "FOR", 4, 0, 9);
  Lex_StringInternRange(&((*sp)), "IF", 3, 0, 9);
  Lex_StringInternRange(&((*sp)), "IMPORT", 7, 0, 9);
  Lex_StringInternRange(&((*sp)), "IN", 3, 0, 9);
  Lex_StringInternRange(&((*sp)), "IS", 3, 0, 9);
  Lex_StringInternRange(&((*sp)), "MOD", 4, 0, 9);
  Lex_StringInternRange(&((*sp)), "MODULE", 7, 0, 9);
  Lex_StringInternRange(&((*sp)), "NATIVE", 7, 0, 9);
  Lex_StringInternRange(&((*sp)), "NIL", 4, 0, 9);
  Lex_StringInternRange(&((*sp)), "OF", 3, 0, 9);
  Lex_StringInternRange(&((*sp)), "OR", 3, 0, 9);
  Lex_StringInternRange(&((*sp)), "POINTER", 8, 0, 9);
  Lex_StringInternRange(&((*sp)), "PROCEDURE", 10, 0, 9);
  Lex_StringInternRange(&((*sp)), "RECORD", 7, 0, 9);
  Lex_StringInternRange(&((*sp)), "REPEAT", 7, 0, 9);
  Lex_StringInternRange(&((*sp)), "RETURN", 7, 0, 9);
  Lex_StringInternRange(&((*sp)), "THEN", 5, 0, 9);
  Lex_StringInternRange(&((*sp)), "TO", 3, 0, 9);
  Lex_StringInternRange(&((*sp)), "TRUE", 5, 0, 9);
  Lex_StringInternRange(&((*sp)), "TYPE", 5, 0, 9);
  Lex_StringInternRange(&((*sp)), "UNTIL", 6, 0, 9);
  Lex_StringInternRange(&((*sp)), "VAR", 4, 0, 9);
  Lex_StringInternRange(&((*sp)), "WHILE", 6, 0, 9);
}

void Lex_LexerInitFromString(struct Lex_Lexer  *l, CHAR s[], size_t s__len) {
  (void)s__len;
  Lex_PoolInit(&((*l).sp));
  Lex_AddKeywords(&((*l).sp));
  strncpy((*l).buf, s, sizeof((*l).buf));
  (*l).fileName = Lex_StringIntern(&((*l).sp), "<string>", 9);
  (*l).pos = 0;
}

void Lex_Unmute(void) {
  Out_Unmute();
  Lex_fatal = 1;
}

void Lex_LexerInitFromFile(struct Lex_Lexer  *l, CHAR fileName[], size_t fileName__len) {
  (void)fileName__len;
  Lex_PoolInit(&((*l).sp));
  Lex_AddKeywords(&((*l).sp));
  Out_ReadFile(fileName, fileName__len, (*l).buf, 65536);
  (*l).fileName = Lex_StringIntern(&((*l).sp), fileName, fileName__len);
  (*l).pos = 0;
}

void Lex_TestLexer(void) {
  Lex_Lexer l;
  INTEGER k;
  Lex_fatal = 0;
  Lex_Mute();
  Lex_LexerInitFromString(&(l), "0C ", 4);
  Lex_NextToken(&(l));
  Lex_LexerInitFromString(&(l), "100X", 5);
  Lex_NextToken(&(l));
  Lex_LexerInitFromString(&(l), "' ", 3);
  Lex_NextToken(&(l));
  Lex_LexerInitFromString(&(l), "   ", 4);
  l.buf[0] = '"';
  Lex_NextToken(&(l));
  Lex_LexerInitFromString(&(l), "(* ", 4);
  Lex_NextToken(&(l));
  Lex_Unmute();
  Lex_fatal = 1;
  Lex_LexerInitFromString(&(l), "\n      Test Hello World Test alpha..beta\n  ARRAY       BEGIN       BITAND      BITOR       BITXOR\n  BY          CASE        CONST       DIV         DO\n  ELSE        ELSIF       END         FALSE       FOR\n  IF          IMPORT      IN          IS          MOD\n  MODULE      NATIVE      NIL         OF          OR\n  POINTER     PROCEDURE   RECORD      REPEAT      RETURN\n  THEN        TO          TRUE        TYPE        UNTIL\n  VAR         WHILE\n      0FFD2H 041X\n      101 102 (103)Wow 104Whoa\n      0.1 0.1E4 0.08E-3 12.83e1\n      + - * / ~ & . , ; | ( ) [ ] { } := ^ = # < >\n      <= >=  .. 10..20\n      (* totally (* skipped *)*)\n      BITXOR\n  ", 649);
  l.buf[11] = '"';
  l.buf[23] = '"';
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 37));
  ASSERT((l.t.sVal == Lex_StringIntern(&(l.sp), "Test", 5)));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 39));
  ASSERT((l.t.sVal == Lex_StringIntern(&(l.sp), "Hello World", 12)));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 37));
  ASSERT((l.t.sVal == Lex_StringIntern(&(l.sp), "Test", 5)));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 37));
  ASSERT((l.t.sVal == Lex_StringIntern(&(l.sp), "alpha", 6)));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 66));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 37));
  ASSERT((l.t.sVal == Lex_StringIntern(&(l.sp), "beta", 5)));
  for (k = 0; k <= 36; k++) {
    Lex_NextToken(&(l));
    ASSERT((l.t.kind == k));
  }
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 40));
  ASSERT((l.t.iVal == 65490));
  ASSERT((l.t.iVal == 65490));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 39));
  ASSERT((l.sp.buf[l.t.sVal] == 'A'));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 40));
  ASSERT((l.t.iVal == 101));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 40));
  ASSERT((l.t.iVal == 102));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 52));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 40));
  ASSERT((l.t.iVal == 103));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 53));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 37));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 40));
  ASSERT((l.t.iVal == 104));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 37));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 41));
  ASSERT((oberon_abs(l.t.rVal - 0.1) < 1e-05));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 41));
  ASSERT((oberon_abs(l.t.rVal - 1000) < 1e-05));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 41));
  ASSERT((oberon_abs(l.t.rVal - 8e-05) < 1e-05));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 41));
  ASSERT((oberon_abs(l.t.rVal - 128.3) < 1e-05));
  for (k = 42; k <= 66; k++) {
    Lex_NextToken(&(l));
    ASSERT((l.t.kind == k));
  }
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 40));
  ASSERT((l.t.iVal == 10));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 66));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 40));
  ASSERT((l.t.iVal == 20));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 4));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 70));
  Lex_NextToken(&(l));
  ASSERT((l.t.kind == 70));
  Lex_LexerInitFromFile(&(l), "Lex.ob", 7);
  do {
    Lex_NextToken(&(l));
  } while (!(l.t.kind == 70));
  Lex_InfoPrintLn("PASS: Lexer test", 17);
}

void Lex_RunTests(void) {
  Lex_TestPool();
  Lex_TestLexer();
}

void Decls_TestCleanup(void) {
  Decls_scope = (AST_Decl)(0);
  Decls_globalScope = (AST_Decl)(0);
}

void Decls_TestDecls(void) {
  Lex_Lexer l;
  AST_Decl d;
  AST_Type t;
  Lex_LexerInitFromString(&(l), "", 1);
  d = (AST_Decl)(0);
  Decls_AddDecl(&(l), &(d), 10);
  Decls_AddDecl(&(l), &(d), 20);
  Decls_AddDecl(&(l), &(d), 30);
  Decls_AddDecl(&(l), &(d), 40);
  Lex_Mute();
  Decls_AddDecl(&(l), &(d), 10);
  Decls_AddDecl(&(l), &(d), 20);
  Decls_AddDecl(&(l), &(d), 30);
  Decls_AddDecl(&(l), &(d), 40);
  Decls_scope = d;
  ASSERT((Decls_LookupDecl(&(l), 20) != 0));
  ASSERT((Decls_LookupDecl(&(l), 100) == 0));
  Lex_Unmute();
  Decls_InitGlobalScope(&(l));
  ASSERT((Decls_LookupDecl(&(l), Lex_Intern(&(l), "NIL", 4)) != 0));
  d = Decls_LookupDecl(&(l), Lex_Intern(&(l), "NIL", 4));
  ASSERT(((*d).kind == 3));
  ASSERT(((*(*d).typ).kind == 1));
  d = Decls_LookupDecl(&(l), Lex_Intern(&(l), "INTEGER", 8));
  ASSERT(((*d).kind == 3));
  t = (*d).typ;
  d = Decls_LookupDecl(&(l), Lex_Intern(&(l), "BYTE", 5));
  ASSERT((t == (*d).typ));
  Decls_TestCleanup();
  Lex_InfoPrintLn("PASS: Decls test", 17);
}

void Decls_RunTests(void) {
  Decls_TestDecls();
}

void Parse_InitFromFile(CHAR fileName[], size_t fileName__len) {
  (void)fileName__len;
  Lex_LexerInitFromFile(&(Parse_l), fileName, fileName__len);
  Lex_NextToken(&(Parse_l));
}

void Parse_TestParse(void) {
  Parse_InitFromFile("Parse.ob", 9);
  Parse_ParseModule();
  Lex_InfoPrintLn("PASS: Parser test", 18);
}

void Parse_RunTests(void) {
  Parse_TestParse();
}

void Compiler_RunTests(void) {
  Lex_RunTests();
  Decls_RunTests();
  Parse_RunTests();
}

void CCodegen_EnableBoundsChecks(void) {
  CCodegen_addBoundsChecks = 1;
}

void CCodegen_EnableCPlusPlus(void) {
  CCodegen_genCPlusPlus = 1;
}

void CCodegen_EnableDumpDecls(void) {
  CCodegen_dumpDecls = 1;
}

void CCodegen_GenTypeinfos(void) {
  INTEGER i;
  CCodegen_GenStr("typedef int oberon_typeid;", 27);
  CCodegen_GenLn();
  CCodegen_GenStr("oberon_typeid oberon_typeinfos[] = {", 37);
  for (i = 0; i <= AST_nextTypeId; i++) {
    CCodegen_GenInt(AST_recordToParent[i]);
    CCodegen_GenStr(", ", 3);
  }
  CCodegen_GenStr("};", 3);
  CCodegen_GenLn();
  CCodegen_GenStr("#include ", 10);
  CCodegen_GenStr("\"", 2);
  CCodegen_GenStr("runtime.c", 10);
  CCodegen_GenStr("\"", 2);
  CCodegen_GenLn();
}

void CCodegen_GenTypedef(struct Lex_Lexer  *l, AST_Decl d) {
  if ((*(*d).typ).kind != 1) {
    CCodegen_GenI();
    CCodegen_GenStr("typedef ", 9);
    CCodegen_GenType(&((*l)), (*d).typ, &((*d).qname), 1, 0);
    CCodegen_GenStr(";", 2);
    CCodegen_GenLn();
  }
}

void CCodegen_GenVar(struct Lex_Lexer  *l, AST_Decl d) {
  CCodegen_GenType(&((*l)), (*d).typ, &((*d).qname), 0, 0);
  CCodegen_GenStr(";", 2);
  CCodegen_GenLn();
}

void CCodegen_RenameInnerProc(AST_Decl d) {
  (*d).qname.name = ((*d).qname.name + CCodegen_innerProcCount);
  CCodegen_innerProcCount++;
}

void CCodegen_GenParenExpr(struct Lex_Lexer  *l, AST_Expr e) {
  if ((*e).kind == 3) {
    CCodegen_GenExpr(&((*l)), e);
  } else {
    CCodegen_GenStr("(", 2);
    CCodegen_GenExpr(&((*l)), e);
    CCodegen_GenStr(")", 2);
  }
}

BOOLEAN CCodegen_ForForwards(AST_Expr e) {
  return ((((e == 0) || (((*(*e).typ).kind == 2) && ((*e).iVal > 0))) || (((*(*e).typ).kind == 3) && ((*e).rVal > 0))));
}

void CCodegen_GenStatements(struct Lex_Lexer  *l, AST_Stmt s) {
  AST_Expr e;
  INTEGER fromVal;
  INTEGER toVal;
  BOOLEAN useChar;
  while (s != 0) {
    ASSERT(((*s).kind >= 1));
    ASSERT(((*s).kind <= 11));
    if (!(((1 << (*s).kind) & 2432))) {
      CCodegen_GenI();
    }
    switch ((*s).kind) {
      case 1:
      case 2:
        CCodegen_GenExpr(&((*l)), (*s).cond);
        CCodegen_GenStr(";", 2);
        break;
      case 3:
        CCodegen_GenStr("if ", 4);
        CCodegen_GenParenExpr(&((*l)), (*s).cond);
        CCodegen_GenStr(" {", 3);
        CCodegen_GenLn();
        CCodegen_indent++;
        CCodegen_GenStatements(&((*l)), (*s).body);
        CCodegen_indent--;
        CCodegen_GenStatements(&((*l)), (*s).elsifs);
        CCodegen_GenI();
        CCodegen_GenStr("}", 2);
        break;
      case 4:
        if ((*s).elsifs == 0) {
          CCodegen_GenStr("while ", 7);
          CCodegen_GenParenExpr(&((*l)), (*s).cond);
          CCodegen_GenStr(" {", 3);
          CCodegen_GenLn();
          CCodegen_indent++;
          CCodegen_GenStatements(&((*l)), (*s).body);
          CCodegen_indent--;
          CCodegen_GenI();
          CCodegen_GenStr("}", 2);
        } else {
          CCodegen_GenStr("while (1) {", 12);
          CCodegen_GenLn();
          CCodegen_indent++;
          CCodegen_GenI();
          CCodegen_GenStr("if ", 4);
          CCodegen_GenParenExpr(&((*l)), (*s).cond);
          CCodegen_GenStr(" {", 3);
          CCodegen_GenLn();
          CCodegen_indent++;
          CCodegen_GenStatements(&((*l)), (*s).body);
          CCodegen_indent--;
          CCodegen_GenStatements(&((*l)), (*s).elsifs);
          CCodegen_GenI();
          CCodegen_GenStr("} else { break; }", 18);
          CCodegen_GenLn();
          CCodegen_indent--;
          CCodegen_GenI();
          CCodegen_GenStr("}", 2);
        }
        break;
      case 5:
        CCodegen_GenStr("do {", 5);
        CCodegen_GenLn();
        CCodegen_indent++;
        CCodegen_GenStatements(&((*l)), (*s).body);
        CCodegen_indent--;
        CCodegen_GenI();
        CCodegen_GenStr("} while (!", 11);
        CCodegen_GenExpr(&((*l)), (*s).cond);
        CCodegen_GenStr(");", 3);
        CCodegen_GenLn();
        break;
      case 6:
        CCodegen_GenStr("for (", 6);
        CCodegen_GenExpr(&((*l)), (*s).cond);
        CCodegen_GenStr("; ", 3);
        CCodegen_GenExpr(&((*l)), (*(*s).cond).lhs);
        if (CCodegen_ForForwards((*(*(*s).cond).next).next)) {
          CCodegen_GenStr(" <= ", 5);
        } else {
          CCodegen_GenStr(" >= ", 5);
        }
        CCodegen_GenExpr(&((*l)), (*(*s).cond).next);
        CCodegen_GenStr("; ", 3);
        CCodegen_GenExpr(&((*l)), (*(*s).cond).lhs);
        if ((*(*(*s).cond).next).next == 0) {
          if (CCodegen_ForForwards((*(*(*s).cond).next).next)) {
            CCodegen_GenStr("++", 3);
          } else {
            CCodegen_GenStr("--", 3);
          }
        } else {
          CCodegen_GenStr(" += ", 5);
          CCodegen_GenExpr(&((*l)), (*(*(*s).cond).next).next);
        }
        CCodegen_GenStr(") {", 4);
        CCodegen_GenLn();
        CCodegen_indent++;
        CCodegen_GenStatements(&((*l)), (*s).body);
        CCodegen_indent--;
        CCodegen_GenI();
        CCodegen_GenStr("}", 2);
        break;
      case 7:
        CCodegen_GenStr("switch ", 8);
        CCodegen_GenParenExpr(&((*l)), (*s).cond);
        CCodegen_GenStr(" {", 3);
        CCodegen_indent++;
        CCodegen_GenStatements(&((*l)), (*s).elsifs);
        CCodegen_indent--;
        CCodegen_GenI();
        CCodegen_GenStr("}", 2);
        CCodegen_GenLn();
        break;
      case 8:
        CCodegen_GenLn();
        ASSERT(((*s).next == 0));
        ASSERT(((*(*s).cond).kind == 3));
        e = (*s).cond;
        while (e != 0) {
          ASSERT((((*e).op == 60) || ((*e).op == 69)));
          if ((*e).op == 60) {
            ASSERT(AST_IsConst((*e).rhs));
            useChar = ((*(*(*e).rhs).typ).kind == 5);
            fromVal = (*(*e).rhs).iVal;
            toVal = fromVal;
          } else {
            ASSERT(AST_IsConst((*(*e).lhs).rhs));
            ASSERT(AST_IsConst((*(*e).rhs).rhs));
            useChar = ((*(*(*(*e).rhs).rhs).typ).kind == 5);
            fromVal = (*(*(*e).lhs).rhs).iVal;
            toVal = (*(*(*e).rhs).rhs).iVal;
          }
          while (fromVal <= toVal) {
            CCodegen_GenI();
            CCodegen_GenStr("case ", 6);
            if (useChar) {
              CCodegen_GenChar(fromVal);
            } else {
              CCodegen_GenInt(fromVal);
            }
            CCodegen_GenStr(":", 2);
            CCodegen_GenLn();
            fromVal++;
          }
          e = (*e).next;
        }
        CCodegen_indent++;
        CCodegen_GenStatements(&((*l)), (*s).body);
        CCodegen_GenI();
        CCodegen_GenStr("break;", 7);
        CCodegen_GenLn();
        CCodegen_indent--;
        CCodegen_GenStatements(&((*l)), (*s).elsifs);
        break;
      case 9:
        ASSERT(((*s).next == 0));
        CCodegen_GenStr("} else if ", 11);
        CCodegen_GenParenExpr(&((*l)), (*s).cond);
        CCodegen_GenStr(" {", 3);
        CCodegen_GenLn();
        CCodegen_indent++;
        CCodegen_GenStatements(&((*l)), (*s).body);
        CCodegen_indent--;
        CCodegen_GenStatements(&((*l)), (*s).elsifs);
        break;
      case 10:
        ASSERT(((*s).elsifs == 0));
        ASSERT(((*s).next == 0));
        CCodegen_GenStr("} else {", 9);
        CCodegen_GenLn();
        CCodegen_indent++;
        CCodegen_GenStatements(&((*l)), (*s).body);
        CCodegen_indent--;
        break;
    }
    if (!(((1 << (*s).kind) & 2432))) {
      CCodegen_GenLn();
    }
    s = (*s).next;
  }
}

void CCodegen_GenProc(struct Lex_Lexer  *l, AST_Decl d) {
  AST_Decl p;
  AST_QName q;
  q.moduleName = 0;
  CCodegen_GenType(&((*l)), (*d).typ, &((*d).qname), 0, 1);
  CCodegen_GenStr(";", 2);
  CCodegen_GenLn();
  if ((*d).procVars != 0) {
    p = (*d).procVars;
    while ((*p).kind != 1001) {
      if ((*p).kind == 5) {
        CCodegen_RenameInnerProc(p);
        CCodegen_GenProc(&((*l)), p);
      }
      p = (*p).next;
    }
  }
  CCodegen_GenType(&((*l)), (*d).typ, &((*d).qname), 0, 1);
  CCodegen_GenStr(" {", 3);
  CCodegen_GenLn();
  CCodegen_indent++;
  if ((*d).procVars != 0) {
    p = (*d).procVars;
    while ((*p).kind != 1001) {
      q.name = (*p).qname.name;
      if ((*p).kind == 4) {
        if ((*p).state == 0) {
          CCodegen_GenStr("#pragma GCC warning ", 21);
          CCodegen_GenStr("\"", 2);
          CCodegen_GenStr("variable ", 10);
          CCodegen_GenQName(&((*l)), &(q));
          CCodegen_GenStr(" unused in PROCEDURE ", 22);
          CCodegen_GenQName(&((*l)), &((*d).qname));
          CCodegen_GenStr("\"", 2);
          CCodegen_GenLn();
        }
        CCodegen_GenI();
        CCodegen_GenType(&((*l)), (*p).typ, &(q), 0, 0);
        CCodegen_GenStr(";", 2);
        CCodegen_GenLn();
      } else if ((*p).kind == 3) {
        CCodegen_GenTypedef(&((*l)), p);
        CCodegen_GenLn();
      } else if (AST_IsOpenArray((*p).typ)) {
        CCodegen_GenI();
        CCodegen_GenStr("(void)", 7);
        CCodegen_GenQName(&((*l)), &(q));
        CCodegen_GenStr("__len;", 7);
        CCodegen_GenLn();
      }
      p = (*p).next;
    }
  }
  CCodegen_GenStatements(&((*l)), (*d).body);
  if ((*d).expr != 0) {
    CCodegen_GenI();
    CCodegen_GenStr("return (", 9);
    CCodegen_GenExpr(&((*l)), (*d).expr);
    CCodegen_GenStr(");", 3);
    CCodegen_GenLn();
  }
  CCodegen_indent--;
  CCodegen_GenI();
  CCodegen_GenStr("}", 2);
  CCodegen_GenLn();
}

void CCodegen_Generate(struct Lex_Lexer  *l, AST_Decl d) {
  if ((*d).nesting == 0) {
    if (CCodegen_dumpDecls) {
      CCodegen_GenStr("/*", 3);
      CCodegen_GenLn();
      DumpDecl_Generate(&((*l)), d);
      CCodegen_GenStr("*/", 3);
      CCodegen_GenLn();
    }
    switch ((*d).kind) {
      case 3:
        CCodegen_GenTypedef(&((*l)), d);
        break;
      case 4:
        CCodegen_GenVar(&((*l)), d);
        break;
      case 5:
        CCodegen_GenProc(&((*l)), d);
        break;
    }
  }
}

void CCodegen_GenStartMain(void) {
  CCodegen_GenStr("int main(int argc, const char **argv) {", 40);
  CCodegen_GenLn();
  CCodegen_indent++;
  CCodegen_GenI();
  CCodegen_GenStr("InitArgs(argc, argv);", 22);
  CCodegen_GenLn();
}

void CCodegen_GenCall(struct Lex_Lexer  *l, struct AST_QName  *name) {
  CCodegen_GenI();
  CCodegen_GenQName(&((*l)), &((*name)));
  CCodegen_GenStr("();", 4);
  CCodegen_GenLn();
}

void CCodegen_GenEndMain(void) {
  CCodegen_indent--;
  CCodegen_GenI();
  CCodegen_GenStr("}", 2);
  CCodegen_GenLn();
}

void Compiler_CompileFile(void) {
  CHAR fileName[256];
  Lex_Lexer l;
  Decls_ReachableDecl p;
  INTEGER i;
  BOOLEAN gotFile;
  i = 1;
  gotFile = 0;
  do {
    Args_GetArg(fileName, 256, i);
    if (strcmp(fileName, "-bounds") == 0) {
      CCodegen_EnableBoundsChecks();
    } else if (strcmp(fileName, "-cpp") == 0) {
      CCodegen_EnableCPlusPlus();
    } else if (strcmp(fileName, "-dumpdecl") == 0) {
      CCodegen_EnableDumpDecls();
    } else {
      gotFile = 1;
    }
    i++;
  } while (!gotFile);
  Parse_InitFromFile(fileName, 256);
  Parse_ParseModule();
  memcpy(&(l), &(Parse_l), sizeof(l));
  Decls_VisitDecl(Parse_lastModuleDecls);
  p = Decls_reachableDecls;
  CCodegen_GenTypeinfos();
  while (p != 0) {
    if (((*(*p).d).kind == 3) && ((*(*(*p).d).typ).kind == 8)) {
      CCodegen_Generate(&(l), (*p).d);
    }
    p = (*p).next;
  }
  p = Decls_reachableDecls;
  while (p != 0) {
    if (((*(*p).d).kind == 3) && ((*(*(*p).d).typ).kind != 8)) {
      CCodegen_Generate(&(l), (*p).d);
    }
    p = (*p).next;
  }
  p = Decls_reachableDecls;
  while (p != 0) {
    if ((*(*p).d).kind == 4) {
      CCodegen_Generate(&(l), (*p).d);
    }
    p = (*p).next;
  }
  p = Decls_reachableDecls;
  while (p != 0) {
    if (((*(*p).d).kind == 5) && !((*(*p).d).isNative)) {
      CCodegen_Generate(&(l), (*p).d);
    }
    p = (*p).next;
  }
  CCodegen_GenStartMain();
  p = Decls_reachableDecls;
  while (p != 0) {
    if ((*(*p).d).qname.name == Decls_modInitName) {
      CCodegen_GenCall(&(l), &((*(*p).d).qname));
    }
    p = (*p).next;
  }
  CCodegen_GenEndMain();
}

void Compiler__module_init_(void) {
  if (Args_Count() == 1) {
    Compiler_RunTests();
  } else {
    Compiler_CompileFile();
  }
}


int main(int argc, const char **argv) {
  InitArgs(argc, argv);
  Lex__module_init_();
  AST__module_init_();
  DumpDecl__module_init_();
  CCodegen__module_init_();
  Decls__module_init_();
  Parse__module_init_();
  Compiler__module_init_();
  return 0;
}
