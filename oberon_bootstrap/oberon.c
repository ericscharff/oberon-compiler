typedef int oberon_typeid;
oberon_typeid oberon_typeinfos[1];
typedef struct oberon_typedesc { int parent[6]; } oberon_typedesc;
oberon_typedesc oberon_typedescs[] = {
  { {0, -1, -1, -1, -1, -1, } },
  { {1, -1, -1, -1, -1, -1, } },
  { {2, -1, -1, -1, -1, -1, } },
  { {3, -1, -1, -1, -1, -1, } },
  { {4, -1, -1, -1, -1, -1, } },
  { {5, -1, -1, -1, -1, -1, } },
  { {6, -1, -1, -1, -1, -1, } },
  { {7, -1, -1, -1, -1, -1, } },
  { {8, -1, -1, -1, -1, -1, } },
  { {9, -1, -1, -1, -1, -1, } },
  { {10, -1, -1, -1, -1, -1, } },
  { {11, -1, -1, -1, -1, -1, } },
};
#include "runtime.c"
typedef struct AST_StmtDesc *AST_Stmt;
typedef struct AST_DeclDesc *AST_Decl;
typedef struct AST_TypeDesc *AST_Type;
typedef struct AST_ExprDesc *AST_Expr;
typedef struct Decls_ReachableDesc *Decls_ReachableDecl;
typedef struct Decls_FwdDecl *Decls_Forward;
typedef char CHAR;
typedef int INTEGER;
typedef bool BOOLEAN;
typedef struct Lex_StringPool {
  CHAR buf[65536];
  INTEGER last;
  INTEGER buckets[4096];
} Lex_StringPool;
typedef OBERON_REAL REAL;
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
typedef struct AST_StmtDesc {
  INTEGER kind;
  AST_Expr cond;
  AST_Stmt body;
  AST_Stmt elsifs;
  AST_Stmt next;
} AST_StmtDesc;
typedef AST_Expr  (*AST_BuiltinResolver)(const Lex_Lexer  *, AST_Expr );
typedef struct AST_DeclDesc {
  INTEGER kind;
  AST_Decl next;
  AST_QName qname;
  AST_Type typ;
  AST_Type origTyp;
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
typedef struct AST_TypeDesc {
  INTEGER kind;
  AST_Type base;
  AST_Decl fields;
  INTEGER length;
  INTEGER nesting;
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
typedef struct Decls_ReachableDesc {
  AST_Decl d;
  Decls_ReachableDecl next;
} Decls_ReachableDesc;
typedef struct Decls_FwdDecl {
  AST_Type t;
  Decls_Forward next;
} Decls_FwdDecl;
typedef void  (*Lex_LexCallback)(void);
typedef struct Parse_CachedImport {
  INTEGER name;
  AST_Decl decls;
} Parse_CachedImport;
CHAR Lex_TokenNames[71][10];
BOOLEAN Lex_fatal;
BOOLEAN Lex_ignoreKeywordCase;
INTEGER AST_currentModuleName;
INTEGER AST_nextTypeId;
CHAR AST_TypeKindNames[14][10];
void  (*CCodegen_GenExpr)(const Lex_Lexer  *, AST_Expr );
BOOLEAN CCodegen_genCPlusPlus;
BOOLEAN CCodegen_addBoundsChecks;
INTEGER CCodegen_indent;
INTEGER CCodegen_innerProcCount;
void  (*Decls_VisitDecl)(AST_Decl );
INTEGER Decls_modInitName;
Decls_ReachableDecl Decls_reachableDecls;
Decls_ReachableDecl Decls_tailReachable;
INTEGER Decls_genSymNum;
AST_Decl Decls_globalScope;
INTEGER Parse_importCacheEnd;
AST_Decl Parse_currentProcDecl;
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
void  (*Parse_ParseDeclarationSequence)(void);
Lex_LexCallback Parse_importCallback;
AST_Type Decls_charType;
Parse_CachedImport Parse_importCache[128];
AST_Decl Parse_lastModuleDecls;
void Args__module_init_(void);
void Args__module_init_(void) {
}
void Out__module_init_(void);
void Out__module_init_(void) {
}
void Lex_InitTokenNames(void);
void Lex_InitTokenNames(void) {
  strncpy(Lex_TokenNames[0], "ARRAY", 10);
  strncpy(Lex_TokenNames[1], "BEGIN", 10);
  strncpy(Lex_TokenNames[2], "BITAND", 10);
  strncpy(Lex_TokenNames[3], "BITOR", 10);
  strncpy(Lex_TokenNames[4], "BITXOR", 10);
  strncpy(Lex_TokenNames[5], "BY", 10);
  strncpy(Lex_TokenNames[6], "CASE", 10);
  strncpy(Lex_TokenNames[7], "CONST", 10);
  strncpy(Lex_TokenNames[8], "DIV", 10);
  strncpy(Lex_TokenNames[9], "DO", 10);
  strncpy(Lex_TokenNames[10], "ELSE", 10);
  strncpy(Lex_TokenNames[11], "ELSIF", 10);
  strncpy(Lex_TokenNames[12], "END", 10);
  strncpy(Lex_TokenNames[13], "FALSE", 10);
  strncpy(Lex_TokenNames[14], "FOR", 10);
  strncpy(Lex_TokenNames[15], "IF", 10);
  strncpy(Lex_TokenNames[16], "IMPORT", 10);
  strncpy(Lex_TokenNames[17], "IN", 10);
  strncpy(Lex_TokenNames[18], "IS", 10);
  strncpy(Lex_TokenNames[19], "MOD", 10);
  strncpy(Lex_TokenNames[20], "MODULE", 10);
  strncpy(Lex_TokenNames[21], "NATIVE", 10);
  strncpy(Lex_TokenNames[22], "NIL", 10);
  strncpy(Lex_TokenNames[23], "OF", 10);
  strncpy(Lex_TokenNames[24], "OR", 10);
  strncpy(Lex_TokenNames[25], "POINTER", 10);
  strncpy(Lex_TokenNames[26], "PROCEDURE", 10);
  strncpy(Lex_TokenNames[27], "RECORD", 10);
  strncpy(Lex_TokenNames[28], "REPEAT", 10);
  strncpy(Lex_TokenNames[29], "RETURN", 10);
  strncpy(Lex_TokenNames[30], "THEN", 10);
  strncpy(Lex_TokenNames[31], "TO", 10);
  strncpy(Lex_TokenNames[32], "TRUE", 10);
  strncpy(Lex_TokenNames[33], "TYPE", 10);
  strncpy(Lex_TokenNames[34], "UNTIL", 10);
  strncpy(Lex_TokenNames[35], "VAR", 10);
  strncpy(Lex_TokenNames[36], "WHILE", 10);
  strncpy(Lex_TokenNames[37], "IDENT", 10);
  strncpy(Lex_TokenNames[38], "KEYWORD", 10);
  strncpy(Lex_TokenNames[39], "STRING", 10);
  strncpy(Lex_TokenNames[40], "INT", 10);
  strncpy(Lex_TokenNames[41], "REAL", 10);
  strncpy(Lex_TokenNames[42], "PLUS", 10);
  strncpy(Lex_TokenNames[43], "MINUS", 10);
  strncpy(Lex_TokenNames[44], "STAR", 10);
  strncpy(Lex_TokenNames[45], "SLASH", 10);
  strncpy(Lex_TokenNames[46], "TILDE", 10);
  strncpy(Lex_TokenNames[47], "AMP", 10);
  strncpy(Lex_TokenNames[48], "DOT", 10);
  strncpy(Lex_TokenNames[49], "COMMA", 10);
  strncpy(Lex_TokenNames[50], "SEMI", 10);
  strncpy(Lex_TokenNames[51], "VBAR", 10);
  strncpy(Lex_TokenNames[52], "LPAREN", 10);
  strncpy(Lex_TokenNames[53], "RPAREN", 10);
  strncpy(Lex_TokenNames[54], "LBRACK", 10);
  strncpy(Lex_TokenNames[55], "RBRACK", 10);
  strncpy(Lex_TokenNames[56], "LBRACE", 10);
  strncpy(Lex_TokenNames[57], "RBRACE", 10);
  strncpy(Lex_TokenNames[58], "ASSIGN", 10);
  strncpy(Lex_TokenNames[59], "CARET", 10);
  strncpy(Lex_TokenNames[60], "EQ", 10);
  strncpy(Lex_TokenNames[61], "POUND", 10);
  strncpy(Lex_TokenNames[62], "LT", 10);
  strncpy(Lex_TokenNames[63], "GT", 10);
  strncpy(Lex_TokenNames[64], "LTEQ", 10);
  strncpy(Lex_TokenNames[65], "GTEQ", 10);
  strncpy(Lex_TokenNames[66], "DOTDOT", 10);
  strncpy(Lex_TokenNames[67], "COLON", 10);
  strncpy(Lex_TokenNames[68], "AS_SET", 10);
  strncpy(Lex_TokenNames[69], "DOTDOT", 10);
  strncpy(Lex_TokenNames[70], "EOF", 10);
}
void Lex__module_init_(void);
void Lex__module_init_(void) {
  Lex_InitTokenNames();
  Lex_fatal = 1;
  Lex_ignoreKeywordCase = 1;
}
void AST_InitTypeKindNames(void);
void AST_InitTypeKindNames(void) {
  strncpy(AST_TypeKindNames[1], "NIL", 10);
  strncpy(AST_TypeKindNames[2], "INTEGER", 10);
  strncpy(AST_TypeKindNames[3], "REAL", 10);
  strncpy(AST_TypeKindNames[4], "BOOLEAN", 10);
  strncpy(AST_TypeKindNames[5], "CHAR", 10);
  strncpy(AST_TypeKindNames[6], "SET", 10);
  strncpy(AST_TypeKindNames[7], "STRING", 10);
  strncpy(AST_TypeKindNames[8], "POINTER", 10);
  strncpy(AST_TypeKindNames[9], "ARRAY", 10);
  strncpy(AST_TypeKindNames[10], "ARRAY *", 10);
  strncpy(AST_TypeKindNames[11], "RECORD", 10);
  strncpy(AST_TypeKindNames[12], "PROCEDURE", 10);
  strncpy(AST_TypeKindNames[13], "IMPORT", 10);
}
void AST__module_init_(void);
void AST__module_init_(void) {
  AST_currentModuleName = 0;
  AST_nextTypeId = 0;
  AST_InitTypeKindNames();
}
void CCodegen_GenStr(const CHAR  *s, INTEGER s__len);
void CCodegen_GenStr(const CHAR  *s, INTEGER s__len) {
  (void)s__len;
  Out_Str(s, s__len);
}
void CCodegen_GenInt(INTEGER i);
void CCodegen_GenInt(INTEGER i) {
  Out_Int(i);
}
void CCodegen_GenChar(INTEGER i);
void CCodegen_GenChar(INTEGER i) {
  CHAR c2[2];
  if ((((i == 39) || (i == 92)) || (i < 32)) || (i > 126)) {
    CCodegen_GenInt(i);
  } else {
    c2[1] = 0;
    c2[0] = i;
    CCodegen_GenStr("'", 2);
    CCodegen_GenStr(c2, 2);
    CCodegen_GenStr("'", 2);

  }
}
void CCodegen_GenReal(REAL r);
void CCodegen_GenReal(REAL r) {
  Out_Real(r);
}
void Lex_OutStrEscaped(const Lex_Lexer  *l, INTEGER s);
void Lex_OutStrEscaped(const Lex_Lexer  *l, INTEGER s) {
  CHAR c;
  Out_Str("\"", 2);
  while ((*l).sp.buf[s] != 0) {
    c = (*l).sp.buf[s];
    if (c == 92) {
      Out_Str("\\\\", 3);
    } else if (c == '"') {
      Out_Str("\\", 2);
      Out_Str("\"", 2);
    } else if (c == 10) {
      Out_Str("\\n", 3);
    } else if (c == 9) {
      Out_Str("\\t", 3);
    } else {
      Out_Char(c);




    }
    s++;
  }
  Out_Str("\"", 2);
}
void CCodegen_GenVal(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenVal(const Lex_Lexer  *l, AST_Expr e) {
  assert(((*e).typ != 0 /*NULL*/));
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
    assert(0);






  }
}
void CCodegen_GenUnaryExpr(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenUnaryExpr(const Lex_Lexer  *l, AST_Expr e) {
  if ((*(*(*e).lhs).typ).kind == 6) {
    if ((*e).op == 43) {
      CCodegen_GenStr("~", 2);
      CCodegen_GenExpr(&((*l)), (*e).lhs);
    } else {
      assert(0);

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
BOOLEAN AST_IsStringType(AST_Type t);
BOOLEAN AST_IsStringType(AST_Type t) {
  return (((*t).kind == 7) || (((*t).kind == 9) && ((*(*t).base).kind == 5)));
  return ((((*t).kind == 7) || (((*t).kind == 9) && ((*(*t).base).kind == 5))));
}
void Lex_OutStr(const Lex_Lexer  *l, INTEGER s);
void Lex_OutStr(const Lex_Lexer  *l, INTEGER s) {
  Out_StrI((*l).sp.buf, 65536, s);
}
void CCodegen_GenQName(const Lex_Lexer  *l, const AST_QName  *name);
void CCodegen_GenQName(const Lex_Lexer  *l, const AST_QName  *name) {
  if ((*name).moduleName > 0) {
    Lex_OutStr(&((*l)), (*name).moduleName);
    CCodegen_GenStr("_", 2);
  }
  if ((*name).name > 0) {
    Lex_OutStr(&((*l)), (*name).name);
  }
}
void CCodegen_GenTypeId(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenTypeId(const Lex_Lexer  *l, AST_Expr e) {
  AST_QName q;
  if ((*(*e).decl).kind == 4) {
    CCodegen_GenInt((*(*e).typ).typeId);
  } else {
    assert((((*(*e).decl).kind == 7) || ((*(*e).decl).kind == 6)));
    q.moduleName = 0;
    q.name = (*(*e).decl).qname.name;
    CCodegen_GenQName(&((*l)), &(q));
    CCodegen_GenStr("__typeid", 9);

  }
}
void CCodegen_GenTypeTest(const Lex_Lexer  *l, AST_Expr base, AST_Type t);
void CCodegen_GenTypeTest(const Lex_Lexer  *l, AST_Expr base, AST_Type t) {
  AST_QName q;
  if ((*(*base).typ).kind == 8) {
    CCodegen_GenExpr(&((*l)), base);
    if ((*(*(*base).typ).base).typeId == (*(*t).base).typeId) {
      CCodegen_GenStr(" && 1", 6);
    } else {
      CCodegen_GenStr(" && oberon_typedescs[*(((oberon_typeid*)", 41);
      CCodegen_GenExpr(&((*l)), base);
      CCodegen_GenStr(")-1)].parent[", 14);
      CCodegen_GenInt((*(*t).base).nesting);
      CCodegen_GenStr("] == ", 6);
      CCodegen_GenInt((*(*t).base).typeId);

    }
  } else {
    assert(((*(*base).typ).kind == 11));
    assert(((*t).kind == 11));
    assert((((*(*base).decl).kind == 7) || ((*(*base).decl).kind == 6)));
    q.moduleName = 0;
    q.name = (*(*base).decl).qname.name;
    CCodegen_GenQName(&((*l)), &(q));
    if ((*(*base).typ).typeId == (*t).typeId) {
      CCodegen_GenStr(" && 1", 6);
    } else {
      CCodegen_GenStr(" && oberon_typedescs[", 22);
      CCodegen_GenTypeId(&((*l)), base);
      CCodegen_GenStr("].parent[", 10);
      CCodegen_GenInt((*t).nesting);
      CCodegen_GenStr("] == ", 6);
      CCodegen_GenInt((*t).typeId);

    }

  }
}
void CCodegen_GenBinaryExpr(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenBinaryExpr(const Lex_Lexer  *l, AST_Expr e) {
  CCodegen_GenStr("(", 2);
  if (AST_IsStringType((*(*e).lhs).typ)) {
    assert(AST_IsStringType((*(*e).rhs).typ));
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
        assert(0);
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
        CCodegen_GenTypeTest(&((*l)), (*e).lhs, (*(*e).rhs).typ);
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
void CCodegen_GenIdentRefExpr(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenIdentRefExpr(const Lex_Lexer  *l, AST_Expr e) {
  AST_QName q;
  assert(((*e).kind == 4));
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
BOOLEAN AST_IsOpenArray(AST_Type t);
BOOLEAN AST_IsOpenArray(AST_Type t) {
  return (((*t).kind == 9) && ((*t).length == 0));
  return ((((*t).kind == 9) && ((*t).length == 0)));
}
INTEGER Lex_StringLenI(const Lex_Lexer  *l, INTEGER s);
INTEGER Lex_StringLenI(const Lex_Lexer  *l, INTEGER s) {
  INTEGER len;
  len = 0;
  while ((*l).sp.buf[s] != 0) {
    s++;
    len++;
  }
  return (len);
}
void CCodegen_GenLengthof(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenLengthof(const Lex_Lexer  *l, AST_Expr e) {
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
    assert(((*e).kind == 4));
    q.name = (*(*e).decl).qname.name;
    CCodegen_GenQName(&((*l)), &(q));
    CCodegen_GenStr("__len", 6);



  }
}
BOOLEAN AST_NeedsTypeInfo(AST_Type t);
BOOLEAN AST_NeedsTypeInfo(AST_Type t) {
  BOOLEAN ti;
  ti = 0;
  do {
    ti = (*t).needTypeInfo;
    t = (*t).base;
  } while (!(ti || (t == 0 /*NULL*/)));

  return ti;
  return (ti);
}
void CCodegen_GenProcCallExpr(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenProcCallExpr(const Lex_Lexer  *l, AST_Expr e) {
  AST_Decl formal;
  CCodegen_GenExpr(&((*l)), (*e).lhs);
  CCodegen_GenStr("(", 2);
  formal = (*(*(*e).lhs).typ).fields;
  e = (*e).rhs;
  while (e != 0 /*NULL*/) {
    if ((*(*e).typ).kind == 9) {
      CCodegen_GenExpr(&((*l)), e);
    } else if (((*(*e).typ).kind == 11) || ((*formal).kind == 7)) {
      if (((*e).typ != (*formal).typ) && !(CCodegen_genCPlusPlus)) {
        CCodegen_GenStr("(", 2);
        CCodegen_GenQName(&((*l)), &((*(*(*formal).typ).decl).qname));
        CCodegen_GenStr("*)", 3);
      }
      CCodegen_GenStr("&(", 3);
      CCodegen_GenExpr(&((*l)), e);
      CCodegen_GenStr(")", 2);
    } else if (((*(*e).typ).kind == 10) && ((*(*formal).typ).kind == 9)) {
      CCodegen_GenExpr(&((*l)), e);
      CCodegen_GenStr(".buf", 5);
    } else if ((*(*e).typ).kind == 8) {
      if (((*e).typ != (*formal).typ) && !(CCodegen_genCPlusPlus)) {
        CCodegen_GenStr("((", 3);
        CCodegen_GenQName(&((*l)), &((*(*(*formal).typ).decl).qname));
        CCodegen_GenStr(")", 2);
        CCodegen_GenExpr(&((*l)), e);
        CCodegen_GenStr(")", 2);
      } else {
        CCodegen_GenExpr(&((*l)), e);

      }
    } else {
      CCodegen_GenExpr(&((*l)), e);




    }
    if (AST_IsOpenArray((*formal).typ)) {
      CCodegen_GenStr(", ", 3);
      CCodegen_GenLengthof(&((*l)), e);
    }
    if (((*(*e).typ).kind == 11) && AST_NeedsTypeInfo((*formal).typ)) {
      CCodegen_GenStr(", ", 3);
      if ((*e).kind == 7) {
        CCodegen_GenInt((*(*e).typ).typeId);
      } else {
        CCodegen_GenTypeId(&((*l)), e);

      }
    }
    if ((*e).next != 0 /*NULL*/) {
      CCodegen_GenStr(", ", 3);
    }
    e = (*e).next;
    formal = (*formal).next;
  }
  CCodegen_GenStr(")", 2);
}
void CCodegen_GenFieldRefExpr(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenFieldRefExpr(const Lex_Lexer  *l, AST_Expr e) {
  INTEGER i;
  CCodegen_GenExpr(&((*l)), (*e).lhs);
  i = (*(*e).decl).nesting;
  if (!(CCodegen_genCPlusPlus)) {
    while (i > 0) {
      CCodegen_GenStr("._base", 7);
      i--;
    }
  }
  CCodegen_GenStr(".", 2);
  Lex_OutStr(&((*l)), (*e).iVal);
}
void CCodegen_GenPointerDerefExpr(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenPointerDerefExpr(const Lex_Lexer  *l, AST_Expr e) {
  CCodegen_GenStr("(*", 3);
  CCodegen_GenExpr(&((*l)), (*e).lhs);
  CCodegen_GenStr(")", 2);
}
void CCodegen_GenBufferRefExpr(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenBufferRefExpr(const Lex_Lexer  *l, AST_Expr e) {
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
void CCodegen_GenArrayRefExpr(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenArrayRefExpr(const Lex_Lexer  *l, AST_Expr e) {
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
void CCodegen_GenTypeGuardExpr(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenTypeGuardExpr(const Lex_Lexer  *l, AST_Expr e) {
  AST_QName q;
  if (CCodegen_genCPlusPlus) {
    if ((*(*(*e).lhs).typ).kind == 8) {
      CCodegen_GenStr("dynamic_cast<", 14);
      CCodegen_GenQName(&((*l)), &((*(*e).decl).qname));
      CCodegen_GenStr(">(", 3);
      CCodegen_GenExpr(&((*l)), (*e).lhs);
      CCodegen_GenStr(")", 2);
    } else {
      assert(((*(*(*e).lhs).typ).kind == 11));
      assert(((*(*e).lhs).kind == 4));
      assert(((*(*(*e).lhs).decl).kind == 7));
      CCodegen_GenStr("(*dynamic_cast<", 16);
      CCodegen_GenQName(&((*l)), &((*(*e).decl).qname));
      CCodegen_GenStr("*>(", 4);
      q.moduleName = 0;
      q.name = (*(*(*e).lhs).decl).qname.name;
      CCodegen_GenQName(&((*l)), &(q));
      CCodegen_GenStr("))", 3);

    }
  } else {
    if ((*(*(*e).lhs).typ).kind == 8) {
      CCodegen_GenStr("(assert(", 9);
      if ((*e).iVal == 0) {
        CCodegen_GenTypeTest(&((*l)), (*e).lhs, (*e).typ);
      } else {
        CCodegen_GenStr("1", 2);

      }
      CCodegen_GenStr("), ((", 6);
      CCodegen_GenQName(&((*l)), &((*(*e).decl).qname));
      CCodegen_GenStr(")(", 3);
      CCodegen_GenExpr(&((*l)), (*e).lhs);
      CCodegen_GenStr(")))", 4);
    } else {
      assert(((*(*(*e).lhs).typ).kind == 11));
      assert(((*(*e).lhs).kind == 4));
      assert(((*(*(*e).lhs).decl).kind == 7));
      CCodegen_GenStr("(*(assert(", 11);
      if ((*e).iVal == 0) {
        CCodegen_GenTypeTest(&((*l)), (*e).lhs, (*e).typ);
      } else {
        CCodegen_GenStr("1", 2);

      }
      CCodegen_GenStr("), ((", 6);
      CCodegen_GenQName(&((*l)), &((*(*e).decl).qname));
      CCodegen_GenStr("*)", 3);
      q.moduleName = 0;
      q.name = (*(*(*e).lhs).decl).qname.name;
      CCodegen_GenQName(&((*l)), &(q));
      CCodegen_GenStr(")))", 4);

    }

  }
}
void CCodegen_GenLn(void);
void CCodegen_GenLn(void) {
  Out_Ln();
}
void CCodegen_GenI(void);
void CCodegen_GenI(void) {
  INTEGER i;
  for (i = 1; i <= CCodegen_indent; i++) {
    CCodegen_GenStr("  ", 3);
  }
}
void CCodegen_GenType(const Lex_Lexer  *l, AST_Type t, const AST_QName  *name, BOOLEAN skipDecl, BOOLEAN procDecl);
void CCodegen_GenType(const Lex_Lexer  *l, AST_Type t, const AST_QName  *name, BOOLEAN skipDecl, BOOLEAN procDecl) {
  AST_Decl f;
  AST_QName q;
  AST_Type p;
  q.moduleName = 0;
  q.name = 0;
  if (((*t).decl == 0 /*NULL*/) || skipDecl) {
switch ((*t).kind) {
      case 2:
        CCodegen_GenStr("int ", 5);
        CCodegen_GenQName(&((*l)), &((*name)));
        break;

      case 3:
        CCodegen_GenStr("OBERON_REAL ", 13);
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
        if ((*(*t).base).decl == 0 /*NULL*/) {
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
        CCodegen_GenStr(" *buf; INTEGER cap; INTEGER len;", 33);
        CCodegen_GenLn();
        CCodegen_indent--;
        CCodegen_GenI();
        CCodegen_GenStr("} ", 3);
        CCodegen_GenQName(&((*l)), &((*name)));
        break;

      case 11:
        CCodegen_GenStr("struct ", 8);
        CCodegen_GenQName(&((*l)), &((*name)));
        if ((*t).base == 0 /*NULL*/) {
          CCodegen_GenStr(" {", 3);
          CCodegen_GenLn();
          CCodegen_indent++;
          if (CCodegen_genCPlusPlus) {
            CCodegen_GenI();
            CCodegen_GenStr("virtual ~", 10);
            CCodegen_GenQName(&((*l)), &((*name)));
            CCodegen_GenStr("() {}", 6);
            CCodegen_GenLn();
          }
        } else {
          assert(((*(*t).base).decl != 0 /*NULL*/));
          if (CCodegen_genCPlusPlus) {
            CCodegen_GenStr(": public ", 10);
            CCodegen_GenQName(&((*l)), &((*(*(*t).base).decl).qname));
            CCodegen_GenStr(" {", 3);
            CCodegen_GenLn();
            CCodegen_indent++;
          } else {
            CCodegen_GenStr(" {", 3);
            CCodegen_GenLn();
            CCodegen_indent++;
            CCodegen_GenI();
            CCodegen_GenQName(&((*l)), &((*(*(*t).base).decl).qname));
            CCodegen_GenStr(" _base;", 8);
            CCodegen_GenLn();

          }

        }
        f = (*t).fields;
        if (((f == 0 /*NULL*/) || ((*f).kind == 1001)) && !(CCodegen_genCPlusPlus)) {
          CCodegen_GenI();
          CCodegen_GenStr("int __dummy;", 13);
          CCodegen_GenLn();
        }
        while ((f != 0 /*NULL*/) && ((*f).kind != 1001)) {
          if ((*f).nesting == 0) {
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
          }
          f = (*f).next;
        }
        CCodegen_indent--;
        CCodegen_GenI();
        CCodegen_GenStr("} ", 3);
        CCodegen_GenQName(&((*l)), &((*name)));
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
        if ((*t).fields == 0 /*NULL*/) {
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
              if (AST_NeedsTypeInfo(t)) {
                CCodegen_GenStr(", oberon_typeid ", 17);
                if (procDecl) {
                  q.name = (*f).qname.name;
                  CCodegen_GenQName(&((*l)), &(q));
                  CCodegen_GenStr("__typeid", 9);
                }
              }
            } else if (AST_IsOpenArray(t)) {
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
              CCodegen_GenStr(", INTEGER", 10);
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
void CCodegen_GenBuiltinExpr(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenBuiltinExpr(const Lex_Lexer  *l, AST_Expr e) {
  AST_QName q;
  q.moduleName = 0;
  q.name = 0;
  assert(((*e).iVal >= 1));
  assert(((*e).iVal <= 16));
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
    case 11:
    case 6:
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      break;

    case 5:
      CCodegen_GenStr("((INTEGER)", 11);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr(")", 2);
      break;

    case 4:
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      if ((*(*e).rhs).next == 0 /*NULL*/) {
        CCodegen_GenStr("--", 3);
      } else {
        CCodegen_GenStr(" -= ", 5);
        CCodegen_GenExpr(&((*l)), (*(*e).rhs).next);

      }
      break;

    case 8:
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      if ((*(*e).rhs).next == 0 /*NULL*/) {
        CCodegen_GenStr("++", 3);
      } else {
        CCodegen_GenStr(" += ", 5);
        CCodegen_GenExpr(&((*l)), (*(*e).rhs).next);

      }
      break;

    case 7:
      CCodegen_GenStr("oberon_buf_init(", 17);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr(", ", 3);
      CCodegen_GenExpr(&((*l)), (*(*e).rhs).next);
      CCodegen_GenStr(", ", 3);
      CCodegen_GenType(&((*l)), (*(*(*e).rhs).typ).base, &(q), 0, 0);
      CCodegen_GenStr(")", 2);
      break;

    case 12:
      CCodegen_GenStr("oberon_buf_push(", 17);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr(", ", 3);
      CCodegen_GenExpr(&((*l)), (*(*e).rhs).next);
      CCodegen_GenStr(", ", 3);
      CCodegen_GenType(&((*l)), (*(*(*e).rhs).typ).base, &(q), 0, 0);
      CCodegen_GenStr(")", 2);
      break;

    case 9:
      CCodegen_GenLengthof(&((*l)), (*e).rhs);
      break;

    case 10:
      if (AST_NeedsTypeInfo((*(*e).rhs).typ)) {
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        if (CCodegen_genCPlusPlus) {
          CCodegen_GenStr(" = new ", 8);
          CCodegen_GenQName(&((*l)), &((*(*(*(*(*e).rhs).typ).base).decl).qname));
          CCodegen_GenStr("[2]", 4);
        } else {
          CCodegen_GenStr(" = malloc(2*sizeof(", 20);
          CCodegen_GenQName(&((*l)), &((*(*(*(*(*e).rhs).typ).base).decl).qname));
          CCodegen_GenStr("))", 3);

        }
        CCodegen_GenStr(";", 2);
        CCodegen_GenLn();
        CCodegen_GenI();
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        CCodegen_GenStr("++;", 4);
        CCodegen_GenLn();
        CCodegen_GenI();
        CCodegen_GenStr("*(((oberon_typeid*)", 20);
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        CCodegen_GenStr(")-1) = ", 8);
        CCodegen_GenInt((*(*(*(*e).rhs).typ).base).typeId);
      } else {
        CCodegen_GenExpr(&((*l)), (*e).rhs);
        if (CCodegen_genCPlusPlus) {
          CCodegen_GenStr(" = new ", 8);
          CCodegen_GenQName(&((*l)), &((*(*(*(*(*e).rhs).typ).base).decl).qname));
        } else {
          CCodegen_GenStr(" = malloc(sizeof(", 18);
          CCodegen_GenQName(&((*l)), &((*(*(*(*(*e).rhs).typ).base).decl).qname));
          CCodegen_GenStr("))", 3);

        }

      }
      break;

    case 13:
      CCodegen_GenStr("scanf(", 7);
      CCodegen_GenStr("\"", 2);
      CCodegen_GenStr("%d", 3);
      CCodegen_GenStr("\"", 2);
      CCodegen_GenStr(", &(", 5);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr("))", 3);
      break;

    case 14:
      CCodegen_GenStr("printf(", 8);
      CCodegen_GenStr("\"", 2);
      CCodegen_GenStr("%4d", 4);
      CCodegen_GenStr("\"", 2);
      CCodegen_GenStr(", ", 3);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr(")", 2);
      break;

    case 15:
      CCodegen_GenStr("putchar(", 9);
      CCodegen_GenExpr(&((*l)), (*e).rhs);
      CCodegen_GenStr(")", 2);
      break;

    case 16:
      CCodegen_GenStr("putchar('\\n')", 14);
      break;
  }
}
void CCodegen_GenAssignExpr(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenAssignExpr(const Lex_Lexer  *l, AST_Expr e) {
  AST_Type t;
  if ((*(*(*e).lhs).typ).kind == 9) {
    assert(((*(*(*(*e).lhs).typ).base).kind == 5));
    CCodegen_GenStr("strncpy(", 9);
    CCodegen_GenExpr(&((*l)), (*e).lhs);
    CCodegen_GenStr(", ", 3);
    CCodegen_GenExpr(&((*l)), (*e).rhs);
    CCodegen_GenStr(", ", 3);
    CCodegen_GenLengthof(&((*l)), (*e).lhs);
    CCodegen_GenStr(")", 2);
  } else if (((!(CCodegen_genCPlusPlus) && ((*(*(*e).lhs).typ).kind == 11)) && ((*(*(*e).rhs).typ).kind == 11)) && ((*(*e).lhs).typ != (*(*e).rhs).typ)) {
    CCodegen_GenExpr(&((*l)), (*e).lhs);
    CCodegen_GenStr(" = ", 4);
    CCodegen_GenExpr(&((*l)), (*e).rhs);
    t = (*(*e).rhs).typ;
    while (t != (*(*e).lhs).typ) {
      CCodegen_GenStr("._base", 7);
      t = (*t).base;
    }
  } else if ((!(CCodegen_genCPlusPlus) && ((*(*(*e).lhs).typ).kind == 8)) && ((*(*e).lhs).typ != (*(*e).rhs).typ)) {
    CCodegen_GenExpr(&((*l)), (*e).lhs);
    CCodegen_GenStr(" = ", 4);
    CCodegen_GenStr("((", 3);
    CCodegen_GenQName(&((*l)), &((*(*(*(*e).lhs).typ).decl).qname));
    CCodegen_GenStr(")", 2);
    CCodegen_GenExpr(&((*l)), (*e).rhs);
    CCodegen_GenStr(")", 2);
  } else {
    CCodegen_GenExpr(&((*l)), (*e).lhs);
    CCodegen_GenStr(" = ", 4);
    CCodegen_GenExpr(&((*l)), (*e).rhs);



  }
}
void CCodegen_GenExpr0(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenExpr0(const Lex_Lexer  *l, AST_Expr e) {
  assert((e != 0 /*NULL*/));
  assert(((*e).kind >= 1));
  assert(((*e).kind <= 12));
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
void CCodegen__module_init_(void);
void CCodegen__module_init_(void) {
  CCodegen_GenExpr = CCodegen_GenExpr0;
  CCodegen_addBoundsChecks = 0;
  CCodegen_genCPlusPlus = 0;
  CCodegen_indent = 0;
  CCodegen_innerProcCount = 0;
}
void Decls_VisitType(AST_Type t);
void Decls_VisitType(AST_Type t) {
  AST_Decl f;
  if ((t != 0 /*NULL*/) && !((*t).reachable)) {
    (*t).reachable = 1;
    Decls_VisitType((*t).base);
    f = (*t).fields;
    while ((f != 0 /*NULL*/) && ((*f).kind != 1001)) {
      Decls_VisitType((*f).typ);
      f = (*f).next;
    }
    if ((*t).decl != 0 /*NULL*/) {
      Decls_VisitDecl((*t).decl);
    }
  }
}
void Decls_VisitExpr(AST_Expr e);
void Decls_VisitExpr(AST_Expr e) {
  while (e != 0 /*NULL*/) {
    Decls_VisitExpr((*e).lhs);
    Decls_VisitExpr((*e).rhs);
    Decls_VisitType((*e).typ);
    if ((*e).decl != 0 /*NULL*/) {
      Decls_VisitDecl((*e).decl);
    }
    e = (*e).next;
  }
}
void Decls_VisitStatement(AST_Stmt s);
void Decls_VisitStatement(AST_Stmt s) {
  while (s != 0 /*NULL*/) {
    Decls_VisitExpr((*s).cond);
    Decls_VisitStatement((*s).body);
    Decls_VisitStatement((*s).elsifs);
    s = (*s).next;
  }
}
void Decls_VisitDecl0(AST_Decl d);
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
    (*reachable).next = ((Decls_ReachableDecl)0 /*NULL*/);
    if (Decls_reachableDecls == 0 /*NULL*/) {
      Decls_reachableDecls = reachable;
    } else {
      (*Decls_tailReachable).next = reachable;

    }
    Decls_tailReachable = reachable;
  } else if ((*d).state == 1) {
    if ((*d).kind != 5) {
      assert(0);
    }
  } else {
    assert(((*d).state == 2));


  }
}
void Decls__module_init_(void);
void Decls__module_init_(void) {
  Decls_VisitDecl = Decls_VisitDecl0;
  Decls_genSymNum = 0;
  Decls_reachableDecls = ((Decls_ReachableDecl)0 /*NULL*/);
  Decls_tailReachable = ((Decls_ReachableDecl)0 /*NULL*/);
  Decls_globalScope = ((AST_Decl)0 /*NULL*/);
}
BOOLEAN Parse_IsToken(INTEGER kind);
BOOLEAN Parse_IsToken(INTEGER kind) {
  return (Parse_l.t.kind == kind);
  return ((Parse_l.t.kind == kind));
}
BOOLEAN Lex_StrEq(const CHAR  *a, INTEGER a__len, INTEGER ai, const CHAR  *b, INTEGER b__len, INTEGER bi, INTEGER len);
BOOLEAN Lex_StrEq(const CHAR  *a, INTEGER a__len, INTEGER ai, const CHAR  *b, INTEGER b__len, INTEGER bi, INTEGER len) {
  (void)a__len;
  (void)b__len;
  while ((len > 0) && (a[ai] == b[bi])) {
    ai++;
    bi++;
    len--;
  }
  return (len == 0);
  return ((len == 0));
}
INTEGER Lex_StringInternRange(Lex_StringPool  *sp, const CHAR  *s, INTEGER s__len, INTEGER offset, INTEGER length);
INTEGER Lex_StringInternRange(Lex_StringPool  *sp, const CHAR  *s, INTEGER s__len, INTEGER offset, INTEGER length) {
  (void)s__len;
  INTEGER i;
  INTEGER hash;
  INTEGER b;
  assert((((*sp).last + length) < 65536));
  hash = -2128831035;
  i = 0;
  while ((i < length) && (s[(offset + i)] != 0)) {
    hash = (hash ^ s[(offset + i)]);
    hash = (hash & 2147483647);
    hash = (hash * 16777619);
    (*sp).buf[((*sp).last + i)] = s[(offset + i)];
    i++;
  }
  (*sp).buf[((*sp).last + i)] = 0;
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
  return (*sp).buckets[b];
  return ((*sp).buckets[b]);
}
void Lex_ScanIdent(Lex_Lexer  *l);
void Lex_ScanIdent(Lex_Lexer  *l) {
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
  } else if ((idx <= 730) && Lex_ignoreKeywordCase) {
    (*l).t.kind = (((idx - 360) / 10) - 1);
  } else {
    (*l).t.kind = 37;
    (*l).t.sVal = idx;


  }
}
void Lex_Next(Lex_Lexer  *l, CHAR  *c);
void Lex_Next(Lex_Lexer  *l, CHAR  *c) {
  (*l).pos++;
  (*c) = (*l).buf[(*l).pos];
}
void Lex_Error(const Lex_Lexer  *l, const CHAR  *s, INTEGER s__len);
void Lex_Error(const Lex_Lexer  *l, const CHAR  *s, INTEGER s__len) {
  (void)s__len;
  Out_Str("Err!", 5);
  Lex_OutStr(&((*l)), (*l).fileName);
  Out_Str("!", 2);
  Out_Int((*l).pos);
  Out_Str("!", 2);
  Out_Str(s, s__len);
}
void Lex_Ln(void);
void Lex_Ln(void) {
  Out_Ln();
  if (Lex_fatal) {
    Out_Halt();
  }
}
void Lex_ErrorLn(const Lex_Lexer  *l, const CHAR  *s, INTEGER s__len);
void Lex_ErrorLn(const Lex_Lexer  *l, const CHAR  *s, INTEGER s__len) {
  (void)s__len;
  Lex_Error(&((*l)), s, s__len);
  Lex_Ln();
}
REAL Lex_Ten(INTEGER e);
REAL Lex_Ten(INTEGER e) {
  REAL r;
  assert((e >= 0));
  r = 1.000000;
  while (e > 0) {
    r = (r * 10.000000);
    e--;
  }
  return r;
  return (r);
}
REAL Lex_StrToReal(const CHAR  *s, INTEGER s__len, INTEGER idx);
REAL Lex_StrToReal(const CHAR  *s, INTEGER s__len, INTEGER idx) {
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
    r = (digits * Lex_Ten(e));
  } else {
    r = (digits / Lex_Ten(-(e)));

  }
  return r;
  return (r);
}
void Out_PrintLn(const CHAR  *s, INTEGER s__len);
void Out_PrintLn(const CHAR  *s, INTEGER s__len) {
  (void)s__len;
  Out_Str(s, s__len);
  Out_Ln();
}
INTEGER Lex_StringLen(const CHAR  *s, INTEGER s__len);
INTEGER Lex_StringLen(const CHAR  *s, INTEGER s__len) {
  (void)s__len;
  INTEGER l;
  l = 0;
  while (s[l] != 0) {
    l++;
  }
  return (l);
}
INTEGER Lex_StringIntern(Lex_StringPool  *sp, const CHAR  *s, INTEGER s__len);
INTEGER Lex_StringIntern(Lex_StringPool  *sp, const CHAR  *s, INTEGER s__len) {
  (void)s__len;
  return Lex_StringInternRange(&((*sp)), s, s__len, 0, Lex_StringLen(s, s__len));
  return (Lex_StringInternRange(&((*sp)), s, s__len, 0, Lex_StringLen(s, s__len)));
}
void Lex_ScanNumber(Lex_Lexer  *l);
void Lex_ScanNumber(Lex_Lexer  *l) {
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
        assert(0);




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
      s[0] = (*l).t.iVal;
      s[1] = 0;
      (*l).t.sVal = Lex_StringIntern(&((*l).sp), s, 2);

    }
  }
}
void Lex_ScanString(Lex_Lexer  *l);
void Lex_ScanString(Lex_Lexer  *l) {
  CHAR ch;
  INTEGER start;
  start = (*l).pos;
  do {
    Lex_Next(&((*l)), &(ch));
  } while (!((ch == 0) || (ch == '"')));

  if (ch == '"') {
    (*l).t.kind = 39;
    (*l).t.sVal = Lex_StringInternRange(&((*l).sp), (*l).buf, 65536, (start + 1), (((*l).pos - start) - 1));
    Lex_Next(&((*l)), &(ch));
  } else {
    (*l).pos = start;
    Lex_ErrorLn(&((*l)), "Unterminated string", 20);
    (*l).buf[(*l).pos] = 0;

  }
}
void Lex_ScanComment(Lex_Lexer  *l);
void Lex_ScanComment(Lex_Lexer  *l) {
  INTEGER start;
  start = (*l).pos;
  assert((((*l).buf[(*l).pos] == '(') && ((*l).buf[((*l).pos + 1)] == '*')));
  (*l).pos += 2;
  do {
    if (((*l).buf[(*l).pos] == '(') && ((*l).buf[((*l).pos + 1)] == '*')) {
      Lex_ScanComment(&((*l)));
    } else {
      (*l).pos++;

    }
  } while (!(((*l).buf[(*l).pos] == 0) || (((*l).buf[(*l).pos] == '*') && ((*l).buf[((*l).pos + 1)] == ')'))));

  if ((*l).buf[(*l).pos] == 0) {
    (*l).pos = start;
    Lex_ErrorLn(&((*l)), "Unterminated comment", 21);
    (*l).buf[(*l).pos] = 0;
  } else {
    (*l).pos += 2;

  }
}
void Lex_NextToken(Lex_Lexer  *l);
void Lex_NextToken(Lex_Lexer  *l) {
  (*l).t.kind = 71;
  do {
switch ((*l).buf[(*l).pos]) {
      case 0:
        (*l).t.kind = 70;
        break;

      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case ' ':
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
BOOLEAN Parse_MatchToken(INTEGER kind);
BOOLEAN Parse_MatchToken(INTEGER kind) {
  BOOLEAN found;
  if (Parse_IsToken(kind)) {
    Lex_NextToken(&(Parse_l));
    found = 1;
  } else {
    found = 0;

  }
  return found;
  return (found);
}
void AST_NewExpr(AST_Expr  *e, INTEGER kind, AST_Type typ);
void AST_NewExpr(AST_Expr  *e, INTEGER kind, AST_Type typ) {
  (*e) = malloc(sizeof(AST_ExprDesc));
  (*(*e)).kind = kind;
  (*(*e)).typ = typ;
  (*(*e)).lhs = ((AST_Expr)0 /*NULL*/);
  (*(*e)).rhs = ((AST_Expr)0 /*NULL*/);
  (*(*e)).next = ((AST_Expr)0 /*NULL*/);
  (*(*e)).decl = ((AST_Decl)0 /*NULL*/);
  (*(*e)).assignable = 0;
}
AST_Expr AST_NewExprNil(AST_Type typ);
AST_Expr AST_NewExprNil(AST_Type typ) {
  AST_Expr e;
  AST_NewExpr(&(e), 1, typ);
  (*e).iVal = 0;
  return e;
  return (e);
}
AST_Expr AST_NewExprInteger(INTEGER iVal, AST_Type typ);
AST_Expr AST_NewExprInteger(INTEGER iVal, AST_Type typ) {
  AST_Expr e;
  AST_NewExpr(&(e), 1, typ);
  (*e).iVal = iVal;
  return e;
  return (e);
}
AST_Expr AST_NewExprReal(REAL rVal, AST_Type typ);
AST_Expr AST_NewExprReal(REAL rVal, AST_Type typ) {
  AST_Expr e;
  AST_NewExpr(&(e), 1, typ);
  (*e).rVal = rVal;
  return e;
  return (e);
}
AST_Expr AST_NewExprString(INTEGER sVal, AST_Type typ);
AST_Expr AST_NewExprString(INTEGER sVal, AST_Type typ) {
  AST_Expr e;
  AST_NewExpr(&(e), 1, typ);
  (*e).iVal = sVal;
  return e;
  return (e);
}
AST_Expr AST_NewExprBoolean(INTEGER bVal, AST_Type typ);
AST_Expr AST_NewExprBoolean(INTEGER bVal, AST_Type typ) {
  AST_Expr e;
  AST_NewExpr(&(e), 1, typ);
  (*e).iVal = bVal;
  return e;
  return (e);
}
void Lex_Str(const CHAR  *s, INTEGER s__len);
void Lex_Str(const CHAR  *s, INTEGER s__len) {
  (void)s__len;
  Out_Str(s, s__len);
}
void Lex_PrintLnAndHalt(const CHAR  *s, INTEGER s__len);
void Lex_PrintLnAndHalt(const CHAR  *s, INTEGER s__len) {
  (void)s__len;
  Out_Str(s, s__len);
  Lex_Ln();
}
void Parse_ExpectToken(INTEGER kind);
void Parse_ExpectToken(INTEGER kind) {
  if (Parse_IsToken(kind)) {
    Lex_NextToken(&(Parse_l));
  } else {
    Lex_Error(&(Parse_l), "Expected ", 10);
    Lex_Str(Lex_TokenNames[kind], 10);
    Lex_Str(", got ", 7);
    Lex_PrintLnAndHalt(Lex_TokenNames[Parse_l.t.kind], 10);

  }
}
AST_Expr AST_NewExprSet(AST_Type typ);
AST_Expr AST_NewExprSet(AST_Type typ) {
  AST_Expr e;
  AST_NewExpr(&(e), 1, typ);
  (*e).setVal = 0;
  return e;
  return (e);
}
void AST_OutTypeName(const Lex_Lexer  *l, AST_Type t);
void AST_OutTypeName(const Lex_Lexer  *l, AST_Type t) {
  if ((*t).decl == 0 /*NULL*/) {
    Lex_Str(AST_TypeKindNames[(*t).kind], 10);
  } else {
    if (((*(*t).decl).qname.moduleName > 0) && ((*(*t).decl).qname.moduleName != AST_currentModuleName)) {
      Lex_OutStr(&((*l)), (*(*t).decl).qname.moduleName);
      Lex_Str(".", 2);
    }
    Lex_OutStr(&((*l)), (*(*t).decl).qname.name);

  }
}
void AST_ExpectType(const Lex_Lexer  *l, AST_Expr e, INTEGER kind);
void AST_ExpectType(const Lex_Lexer  *l, AST_Expr e, INTEGER kind) {
  assert((e != 0 /*NULL*/));
  assert(((*e).typ != 0 /*NULL*/));
  if ((*(*e).typ).kind != kind) {
    Lex_Error(&((*l)), "Expected ", 10);
    Lex_Str(AST_TypeKindNames[kind], 10);
    Lex_Str(", got ", 7);
    AST_OutTypeName(&((*l)), (*e).typ);
    Lex_Ln();
  }
}
BOOLEAN AST_IsConst(AST_Expr e);
BOOLEAN AST_IsConst(AST_Expr e) {
  return ((*e).kind == 1);
  return (((*e).kind == 1));
}
AST_Expr AST_NewExprSetRange(const Lex_Lexer  *l, AST_Expr lhs, AST_Expr rhs, AST_Type setType);
AST_Expr AST_NewExprSetRange(const Lex_Lexer  *l, AST_Expr lhs, AST_Expr rhs, AST_Type setType) {
  AST_Expr e;
  AST_ExpectType(&((*l)), lhs, 2);
  AST_ExpectType(&((*l)), rhs, 2);
  if (AST_IsConst(lhs) && AST_IsConst(rhs)) {
    e = AST_NewExprSet(setType);
    (*e).setVal = (make_set_range((*lhs).iVal, (*rhs).iVal));
  } else {
    AST_NewExpr(&(e), 3, setType);
    (*e).op = 66;
    (*e).lhs = lhs;
    (*e).rhs = rhs;

  }
  return e;
  return (e);
}
void Lex_Int(INTEGER i);
void Lex_Int(INTEGER i) {
  Out_Int(i);
}
AST_Expr AST_NewExprSetElement(const Lex_Lexer  *l, AST_Expr elt, AST_Type setType);
AST_Expr AST_NewExprSetElement(const Lex_Lexer  *l, AST_Expr elt, AST_Type setType) {
  AST_Expr e;
  e = AST_NewExprSet(setType);
  (*e).setVal = 0;
  AST_ExpectType(&((*l)), elt, 2);
  if (AST_IsConst(elt)) {
    if (((*elt).iVal < 0) || ((*elt).iVal > 31)) {
      Lex_Error(&((*l)), "Value ", 7);
      Lex_Int((*elt).iVal);
      Lex_PrintLnAndHalt(" out OF range of SET 0..31", 27);
    } else {
      e = AST_NewExprSet(setType);
      (*e).setVal = (1 << (*elt).iVal);

    }
  } else {
    AST_NewExpr(&(e), 2, setType);
    (*e).op = 68;
    (*e).lhs = elt;

  }
  return e;
  return (e);
}
AST_Expr Parse_ParseSetElement(void);
AST_Expr Parse_ParseSetElement(void) {
  AST_Expr e;
  e = Parse_ParseExpression();
  if (Parse_MatchToken(66)) {
    e = AST_NewExprSetRange(&(Parse_l), e, Parse_ParseExpression(), Decls_setType);
  } else {
    e = AST_NewExprSetElement(&(Parse_l), e, Decls_setType);

  }
  return e;
  return (e);
}
AST_Expr AST_NewExprSetUnion(const Lex_Lexer  *l, AST_Expr lhs, AST_Expr rhs);
AST_Expr AST_NewExprSetUnion(const Lex_Lexer  *l, AST_Expr lhs, AST_Expr rhs) {
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
  return e;
  return (e);
}
AST_Expr Parse_ParseSet(void);
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
  return e;
  return (e);
}
BOOLEAN AST_IsImported(AST_Decl d);
BOOLEAN AST_IsImported(AST_Decl d) {
  assert((d != 0 /*NULL*/));
  while ((d != 0 /*NULL*/) && ((*d).kind != 1001)) {
    d = (*d).next;
  }
  assert((d != 0 /*NULL*/));
  assert(((*d).kind == 1001));
  return ((*d).qname.moduleName != AST_currentModuleName);
  return (((*d).qname.moduleName != AST_currentModuleName));
}
BOOLEAN AST_Extends(AST_Type a, AST_Type b);
BOOLEAN AST_Extends(AST_Type a, AST_Type b) {
  if ((((a != 0 /*NULL*/) && (b != 0 /*NULL*/)) && ((*a).kind == 11)) && ((*b).kind == 11)) {
    while ((a != 0 /*NULL*/) && (a != b)) {
      a = (*a).base;
    }
  }
  return (((a != 0 /*NULL*/) && (b != 0 /*NULL*/)) && (a == b));
  return ((((a != 0 /*NULL*/) && (b != 0 /*NULL*/)) && (a == b)));
}
void AST_SetGenTypeInfo(AST_Type t);
void AST_SetGenTypeInfo(AST_Type t) {
  if ((*t).kind == 8) {
    t = (*t).base;
  }
  while (t != 0 /*NULL*/) {
    (*t).needTypeInfo = 1;
    t = (*t).base;
  }
}
AST_Expr AST_NewExprTypeGuard(const Lex_Lexer  *l, AST_Expr base, AST_Decl newType);
AST_Expr AST_NewExprTypeGuard(const Lex_Lexer  *l, AST_Expr base, AST_Decl newType) {
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
    Lex_PrintLnAndHalt(" must be a POINTER or RECORD type", 34);

  }
  return e;
  return (e);
}
AST_Expr AST_NewExprIdentRef(const Lex_Lexer  *l, AST_Decl d);
AST_Expr AST_NewExprIdentRef(const Lex_Lexer  *l, AST_Decl d) {
  AST_Expr e;
  assert((d != 0 /*NULL*/));
  assert(((*d).typ != 0 /*NULL*/));
  AST_NewExpr(&(e), 4, (*d).typ);
  (*e).decl = d;
  if (((((*d).kind == 4) && !(AST_IsImported(d))) || (((*d).kind == 6) && !(((1 << (*(*d).typ).kind) & 3584)))) || ((*d).kind == 7)) {
    (*e).assignable = 1;
  } else {
    (*e).assignable = 0;

  }
  if ((*d).kind == 2) {
    assert(((*d).typ == (*(*d).expr).typ));
    assert(((*(*d).expr).kind == 1));
    (*e).kind = 1;
    (*e).iVal = (*(*d).expr).iVal;
    (*e).rVal = (*(*d).expr).rVal;
    (*e).setVal = (*(*d).expr).setVal;
  }
  if ((*d).origTyp != 0 /*NULL*/) {
    e = AST_NewExprTypeGuard(&((*l)), e, (*(*d).origTyp).decl);
    (*e).iVal = 1;
  }
  return e;
  return (e);
}
INTEGER Parse_ExpectIdentifier(void);
INTEGER Parse_ExpectIdentifier(void) {
  INTEGER s;
  s = Parse_l.t.sVal;
  Parse_ExpectToken(37);
  return s;
  return (s);
}
AST_Decl Decls_LookupDecl0(INTEGER name);
AST_Decl Decls_LookupDecl0(INTEGER name) {
  AST_Decl p;
  p = Decls_scope;
  while ((p != 0 /*NULL*/) && ((*p).qname.name != name)) {
    p = (*p).next;
  }
  return p;
  return (p);
}
AST_Decl Decls_LookupDecl(const Lex_Lexer  *l, INTEGER name);
AST_Decl Decls_LookupDecl(const Lex_Lexer  *l, INTEGER name) {
  AST_Decl p;
  p = Decls_LookupDecl0(name);
  if (p == 0 /*NULL*/) {
    Lex_Error(&((*l)), "", 1);
    Lex_OutStr(&((*l)), name);
    Lex_PrintLnAndHalt(" undefined", 11);
  }
  return p;
  return (p);
}
BOOLEAN Parse_IsImportedModule(INTEGER ident);
BOOLEAN Parse_IsImportedModule(INTEGER ident) {
  AST_Decl d;
  d = Decls_LookupDecl(&(Parse_l), ident);
  return ((d != 0 /*NULL*/) && ((*d).kind == 1));
  return (((d != 0 /*NULL*/) && ((*d).kind == 1)));
}
AST_Decl Decls_LookupImport(const Lex_Lexer  *l, INTEGER moduleName, INTEGER name);
AST_Decl Decls_LookupImport(const Lex_Lexer  *l, INTEGER moduleName, INTEGER name) {
  AST_Decl p;
  AST_Decl d;
  d = Decls_LookupDecl(&((*l)), moduleName);
  assert(((*d).kind == 1));
  p = (*(*d).typ).fields;
  while ((p != 0 /*NULL*/) && ((*p).qname.name != name)) {
    p = (*p).next;
  }
  if (p == 0 /*NULL*/) {
    Lex_Error(&((*l)), "", 1);
    Lex_OutStr(&((*l)), moduleName);
    Lex_Str(".", 2);
    Lex_OutStr(&((*l)), name);
    Lex_PrintLnAndHalt(" undefined", 11);
  } else if (!((*p).exported)) {
    Lex_Error(&((*l)), "", 1);
    Lex_OutStr(&((*l)), moduleName);
    Lex_Str(".", 2);
    Lex_OutStr(&((*l)), name);
    Lex_PrintLnAndHalt(" is not exported", 17);

  }
  return p;
  return (p);
}
AST_Decl Parse_ParseQualident(void);
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
  return d;
  return (d);
}
BOOLEAN Parse_IsTypeGuard(AST_Expr e);
BOOLEAN Parse_IsTypeGuard(AST_Expr e) {
  return (((*(*e).typ).kind == 8) || ((((*(*e).typ).kind == 11) && ((*e).kind == 4)) && ((*(*e).decl).kind == 7)));
  return ((((*(*e).typ).kind == 8) || ((((*(*e).typ).kind == 11) && ((*e).kind == 4)) && ((*(*e).decl).kind == 7))));
}
AST_Expr AST_NewExprPointerDeref(const Lex_Lexer  *l, AST_Expr base);
AST_Expr AST_NewExprPointerDeref(const Lex_Lexer  *l, AST_Expr base) {
  AST_Expr e;
  AST_NewExpr(&(e), 7, (*base).typ);
  (*e).lhs = base;
  (*e).assignable = (*base).assignable;
  if ((*(*base).typ).kind == 8) {
    (*e).typ = (*(*base).typ).base;
  } else {
    Lex_ErrorLn(&((*l)), "not a POINTER", 14);

  }
  return e;
  return (e);
}
AST_Expr AST_NewExprFieldRef(const Lex_Lexer  *l, AST_Expr base, INTEGER name);
AST_Expr AST_NewExprFieldRef(const Lex_Lexer  *l, AST_Expr base, INTEGER name) {
  AST_Expr e;
  AST_Decl d;
  e = base;
  if ((*(*base).typ).kind == 8) {
    base = AST_NewExprPointerDeref(&((*l)), base);
  }
  if ((*(*base).typ).kind == 11) {
    d = (*(*base).typ).fields;
    while (((d != 0 /*NULL*/) && ((*d).kind != 1001)) && ((*d).qname.name != name)) {
      d = (*d).next;
    }
    if ((*d).qname.name == name) {
      if (AST_IsImported(d) && !((*d).exported)) {
        Lex_Error(&((*l)), "Field ", 7);
        Lex_OutStr(&((*l)), name);
        Lex_PrintLnAndHalt(" is private", 12);
      }
      AST_NewExpr(&(e), 6, (*d).typ);
      (*e).lhs = base;
      (*e).iVal = name;
      (*e).decl = d;
      (*e).assignable = (*base).assignable;
    } else {
      Lex_Error(&((*l)), "Field ", 7);
      Lex_OutStr(&((*l)), name);
      Lex_PrintLnAndHalt(" not found", 11);

    }
  } else {
    Lex_ErrorLn(&((*l)), "Not a RECORD", 13);

  }
  return e;
  return (e);
}
AST_Expr AST_NewExprArrayRef(const Lex_Lexer  *l, AST_Expr base, AST_Expr index);
AST_Expr AST_NewExprArrayRef(const Lex_Lexer  *l, AST_Expr base, AST_Expr index) {
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
  return e;
  return (e);
}
AST_Expr Parse_ParseDesignator(void);
AST_Expr Parse_ParseDesignator(void) {
  AST_Expr e;
  e = AST_NewExprIdentRef(&(Parse_l), Parse_ParseQualident());
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
      assert(0);




    }
  }
  return e;
  return (e);
}
BOOLEAN Lex_IsOneChar(const Lex_Lexer  *l, INTEGER s);
BOOLEAN Lex_IsOneChar(const Lex_Lexer  *l, INTEGER s) {
  return (((*l).sp.buf[s] == 0) || ((*l).sp.buf[(s + 1)] == 0));
  return ((((*l).sp.buf[s] == 0) || ((*l).sp.buf[(s + 1)] == 0)));
}
BOOLEAN AST_AssignmentCompatable(const Lex_Lexer  *l, AST_Type a, AST_Type b, INTEGER aSval, INTEGER bSval);
BOOLEAN AST_AssignmentCompatable(const Lex_Lexer  *l, AST_Type a, AST_Type b, INTEGER aSval, INTEGER bSval) {
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
  return (((((((((((a == b) || (((*a).kind == 7) && ((*b).kind == 7))) || ((((*a).kind == 5) && ((*b).kind == 7)) && Lex_IsOneChar(&((*l)), bSval))) || ((((*b).kind == 5) && ((*a).kind == 7)) && Lex_IsOneChar(&((*l)), aSval))) || (((*a).kind == 1) && ((*b).kind == 8))) || (((*a).kind == 1) && ((*b).kind == 12))) || ((((*a).kind == 8) && ((*b).kind == 8)) && AST_Extends((*a).base, (*b).base))) || ((((*a).kind == 11) && ((*b).kind == 11)) && AST_Extends(a, b))) || ((((*a).kind == 12) && ((*b).kind == 12)) && procCompatable)) || (((((*a).kind == 9) && ((*(*a).base).kind == 5)) && ((*b).kind == 9)) && ((*(*b).base).kind == 5))) || ((((*a).kind == 7) && ((*b).kind == 9)) && ((*(*b).base).kind == 5)));
  return ((((((((((((a == b) || (((*a).kind == 7) && ((*b).kind == 7))) || ((((*a).kind == 5) && ((*b).kind == 7)) && Lex_IsOneChar(&((*l)), bSval))) || ((((*b).kind == 5) && ((*a).kind == 7)) && Lex_IsOneChar(&((*l)), aSval))) || (((*a).kind == 1) && ((*b).kind == 8))) || (((*a).kind == 1) && ((*b).kind == 12))) || ((((*a).kind == 8) && ((*b).kind == 8)) && AST_Extends((*a).base, (*b).base))) || ((((*a).kind == 11) && ((*b).kind == 11)) && AST_Extends(a, b))) || ((((*a).kind == 12) && ((*b).kind == 12)) && procCompatable)) || (((((*a).kind == 9) && ((*(*a).base).kind == 5)) && ((*b).kind == 9)) && ((*(*b).base).kind == 5))) || ((((*a).kind == 7) && ((*b).kind == 9)) && ((*(*b).base).kind == 5))));
}
void AST_ExpectArgMatch(const Lex_Lexer  *l, INTEGER arg, AST_Expr actual, AST_Decl formal);
void AST_ExpectArgMatch(const Lex_Lexer  *l, INTEGER arg, AST_Expr actual, AST_Decl formal) {
  if ((AST_IsOpenArray((*formal).typ) && ((*(*actual).typ).kind == 9)) && ((*(*actual).typ).base == (*(*formal).typ).base)) {
  } else if ((AST_IsOpenArray((*formal).typ) && ((*(*actual).typ).kind == 10)) && ((*(*actual).typ).base == (*(*formal).typ).base)) {
  } else if (((*formal).kind == 7) && !((*actual).assignable)) {
    Lex_Error(&((*l)), "For argument ", 14);
    Lex_Int(arg);
    Lex_PrintLnAndHalt(", param is not assignable (expected VAR param)", 47);
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
INTEGER Lex_FirstChar(const Lex_Lexer  *l, INTEGER s);
INTEGER Lex_FirstChar(const Lex_Lexer  *l, INTEGER s) {
  return (*l).sp.buf[s];
  return ((*l).sp.buf[s]);
}
void AST_CoerceToChar(const Lex_Lexer  *l, AST_Expr e, AST_Type charType);
void AST_CoerceToChar(const Lex_Lexer  *l, AST_Expr e, AST_Type charType) {
  assert(AST_IsConst(e));
  assert(((*(*e).typ).kind == 7));
  assert(Lex_IsOneChar(&((*l)), (*e).iVal));
  (*e).typ = charType;
  (*e).iVal = Lex_FirstChar(&((*l)), (*e).iVal);
}
AST_Expr AST_NewExprProcCall(const Lex_Lexer  *l, AST_Expr proc, AST_Expr args);
AST_Expr AST_NewExprProcCall(const Lex_Lexer  *l, AST_Expr proc, AST_Expr args) {
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
    while (arg != 0 /*NULL*/) {
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
  return e;
  return (e);
}
AST_Expr Parse_ParseActualParameters(void);
AST_Expr Parse_ParseActualParameters(void) {
  AST_Expr head;
  AST_Expr tail;
  head = ((AST_Expr)0 /*NULL*/);
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
  return head;
  return (head);
}
AST_Expr AST_NewExprUnary(const Lex_Lexer  *l, INTEGER op, AST_Expr lhs);
AST_Expr AST_NewExprUnary(const Lex_Lexer  *l, INTEGER op, AST_Expr lhs) {
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
          (*e).setVal = ~(*lhs).setVal;
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
  return e;
  return (e);
}
AST_Expr Parse_ParseFactor(void);
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
  return e;
  return (e);
}
BOOLEAN Parse_IsMulOperator(void);
BOOLEAN Parse_IsMulOperator(void) {
  return (((((((Parse_IsToken(44) || Parse_IsToken(45)) || Parse_IsToken(8)) || Parse_IsToken(19)) || Parse_IsToken(47)) || Parse_IsToken(2)) || Parse_IsToken(3)) || Parse_IsToken(4));
  return ((((((((Parse_IsToken(44) || Parse_IsToken(45)) || Parse_IsToken(8)) || Parse_IsToken(19)) || Parse_IsToken(47)) || Parse_IsToken(2)) || Parse_IsToken(3)) || Parse_IsToken(4)));
}
BOOLEAN AST_ExprCompatable(const Lex_Lexer  *l, INTEGER op, AST_Expr lhs, AST_Expr rhs);
BOOLEAN AST_ExprCompatable(const Lex_Lexer  *l, INTEGER op, AST_Expr lhs, AST_Expr rhs) {
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
  return good;
  return (good);
}
AST_Expr AST_NewExprBinary(const Lex_Lexer  *l, INTEGER op, AST_Expr lhs, AST_Expr rhs, AST_Type booleanType);
AST_Expr AST_NewExprBinary(const Lex_Lexer  *l, INTEGER op, AST_Expr lhs, AST_Expr rhs, AST_Type booleanType) {
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
            (*e).setVal = ((*lhs).setVal & ~(*rhs).setVal);
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
            if ((*rhs).rVal == 0.000000) {
              (*e).rVal = 0.000000;
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
  return e;
  return (e);
}
AST_Expr Parse_ParseTerm(void);
AST_Expr Parse_ParseTerm(void) {
  AST_Expr e;
  INTEGER op;
  e = Parse_ParseFactor();
  while (Parse_IsMulOperator()) {
    op = Parse_l.t.kind;
    Lex_NextToken(&(Parse_l));
    e = AST_NewExprBinary(&(Parse_l), op, e, Parse_ParseFactor(), Decls_booleanType);
  }
  return e;
  return (e);
}
BOOLEAN Parse_IsAddOperator(void);
BOOLEAN Parse_IsAddOperator(void) {
  return ((Parse_IsToken(42) || Parse_IsToken(43)) || Parse_IsToken(24));
  return (((Parse_IsToken(42) || Parse_IsToken(43)) || Parse_IsToken(24)));
}
AST_Expr Parse_ParseSimpleExpression(void);
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
  return e;
  return (e);
}
BOOLEAN Parse_IsRelation(void);
BOOLEAN Parse_IsRelation(void) {
  return (((((((Parse_IsToken(60) || Parse_IsToken(61)) || Parse_IsToken(62)) || Parse_IsToken(64)) || Parse_IsToken(63)) || Parse_IsToken(65)) || Parse_IsToken(17)) || Parse_IsToken(18));
  return ((((((((Parse_IsToken(60) || Parse_IsToken(61)) || Parse_IsToken(62)) || Parse_IsToken(64)) || Parse_IsToken(63)) || Parse_IsToken(65)) || Parse_IsToken(17)) || Parse_IsToken(18)));
}
AST_Expr Parse_ParseExpression0(void);
AST_Expr Parse_ParseExpression0(void) {
  AST_Expr e;
  INTEGER op;
  e = Parse_ParseSimpleExpression();
  if (Parse_IsRelation()) {
    op = Parse_l.t.kind;
    Lex_NextToken(&(Parse_l));
    e = AST_NewExprBinary(&(Parse_l), op, e, Parse_ParseSimpleExpression(), Decls_booleanType);
  }
  return e;
  return (e);
}
AST_Expr Parse_ParseBooleanExpression(void);
AST_Expr Parse_ParseBooleanExpression(void) {
  AST_Expr e;
  e = Parse_ParseExpression();
  if ((*(*e).typ).kind != 4) {
    Lex_ErrorLn(&(Parse_l), "BOOLEAN expected", 17);
  }
  return e;
  return (e);
}
void AST_NewStmt(AST_Stmt  *s, INTEGER kind);
void AST_NewStmt(AST_Stmt  *s, INTEGER kind) {
  (*s) = malloc(sizeof(AST_StmtDesc));
  (*(*s)).kind = kind;
  (*(*s)).cond = ((AST_Expr)0 /*NULL*/);
  (*(*s)).body = ((AST_Stmt)0 /*NULL*/);
  (*(*s)).elsifs = ((AST_Stmt)0 /*NULL*/);
  (*(*s)).next = ((AST_Stmt)0 /*NULL*/);
}
AST_Stmt AST_NewStmtIf(AST_Expr cond, AST_Stmt body);
AST_Stmt AST_NewStmtIf(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  assert(((*(*cond).typ).kind == 4));
  AST_NewStmt(&(s), 3);
  (*s).cond = cond;
  (*s).body = body;
  return s;
  return (s);
}
AST_Stmt AST_NewStmtElsIf(AST_Expr cond, AST_Stmt body);
AST_Stmt AST_NewStmtElsIf(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  assert(((*(*cond).typ).kind == 4));
  AST_NewStmt(&(s), 9);
  (*s).cond = cond;
  (*s).body = body;
  return s;
  return (s);
}
AST_Stmt AST_NewStmtElse(AST_Stmt body);
AST_Stmt AST_NewStmtElse(AST_Stmt body) {
  AST_Stmt s;
  AST_NewStmt(&(s), 10);
  (*s).body = body;
  return s;
  return (s);
}
AST_Stmt Parse_ParseIfStatement(void);
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
  return s;
  return (s);
}
AST_Stmt Parse_ParseTypeCase(AST_Expr caseVar);
AST_Stmt Parse_ParseTypeCase(AST_Expr caseVar) {
  AST_Expr e;
  AST_Stmt s;
  AST_Stmt tail;
  AST_Type savedType;
  Parse_ExpectToken(23);
  tail = ((AST_Stmt)0 /*NULL*/);
  savedType = (*(*caseVar).decl).typ;
  while (!(Parse_IsToken(12))) {
    e = AST_NewExprBinary(&(Parse_l), 18, caseVar, AST_NewExprIdentRef(&(Parse_l), Parse_ParseQualident()), Decls_booleanType);
    (*(*caseVar).decl).typ = (*(*(*e).rhs).decl).typ;
    (*(*caseVar).decl).origTyp = (*(*(*e).rhs).decl).typ;
    Parse_ExpectToken(67);
    if (tail == 0 /*NULL*/) {
      s = AST_NewStmtIf(e, Parse_ParseStatementSequence());
      tail = s;
    } else {
      (*tail).elsifs = AST_NewStmtElsIf(e, Parse_ParseStatementSequence());
      tail = (*tail).elsifs;

    }
    (*(*caseVar).decl).typ = savedType;
    (*(*caseVar).decl).origTyp = ((AST_Type)0 /*NULL*/);
    Parse_MatchToken(51);
  }
  Parse_ExpectToken(12);
  return s;
  return (s);
}
AST_Expr Parse_ParseCaseLabel(AST_Expr caseVar);
AST_Expr Parse_ParseCaseLabel(AST_Expr caseVar) {
  AST_Expr cond;
  cond = ((AST_Expr)0 /*NULL*/);
  if ((Parse_IsToken(40) || Parse_IsToken(39)) || Parse_IsToken(37)) {
    cond = AST_NewExprBinary(&(Parse_l), 60, caseVar, Parse_ParseFactor(), Decls_booleanType);
    if (!(AST_IsConst((*cond).rhs))) {
      Lex_ErrorLn(&(Parse_l), "CASE label must be constant", 28);
    }
  } else {
    Lex_ErrorLn(&(Parse_l), "Case label (INTEGER, STRING, IDENT) expected", 45);

  }
  return cond;
  return (cond);
}
AST_Expr Parse_ParseCaseLabelRange(AST_Expr caseVar);
AST_Expr Parse_ParseCaseLabelRange(AST_Expr caseVar) {
  AST_Expr cond;
  cond = Parse_ParseCaseLabel(caseVar);
  if (Parse_MatchToken(66)) {
    cond = AST_NewExprBinary(&(Parse_l), 69, cond, Parse_ParseCaseLabel(caseVar), Decls_booleanType);
  }
  return cond;
  return (cond);
}
AST_Expr Parse_ParseCaseLabelList(AST_Expr caseVar);
AST_Expr Parse_ParseCaseLabelList(AST_Expr caseVar) {
  AST_Expr head;
  AST_Expr tail;
  head = Parse_ParseCaseLabelRange(caseVar);
  tail = head;
  while (Parse_MatchToken(49)) {
    (*tail).next = Parse_ParseCaseLabelRange(caseVar);
    tail = (*tail).next;
  }
  return head;
  return (head);
}
AST_Stmt AST_NewStmtCaseItem(AST_Expr cond, AST_Stmt body);
AST_Stmt AST_NewStmtCaseItem(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  assert(((*(*cond).typ).kind == 4));
  AST_NewStmt(&(s), 8);
  (*s).cond = cond;
  (*s).body = body;
  return s;
  return (s);
}
AST_Stmt Parse_ParseCase(AST_Expr caseVar);
AST_Stmt Parse_ParseCase(AST_Expr caseVar) {
  AST_Stmt s;
  AST_Expr cond;
  s = ((AST_Stmt)0 /*NULL*/);
  if ((Parse_IsToken(40) || Parse_IsToken(39)) || Parse_IsToken(37)) {
    cond = Parse_ParseCaseLabelList(caseVar);
    Parse_ExpectToken(67);
    s = AST_NewStmtCaseItem(cond, Parse_ParseStatementSequence());
  }
  return s;
  return (s);
}
AST_Stmt AST_NewStmtCase(AST_Expr cond, AST_Stmt body);
AST_Stmt AST_NewStmtCase(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  if (body != 0 /*NULL*/) {
    assert(((*body).kind == 8));
  }
  AST_NewStmt(&(s), 7);
  (*s).cond = cond;
  (*s).elsifs = body;
  return s;
  return (s);
}
AST_Stmt Parse_ParseCaseStatement(void);
AST_Stmt Parse_ParseCaseStatement(void) {
  AST_Expr cond;
  AST_Stmt s;
  AST_Stmt head;
  AST_Stmt tail;
  Parse_ExpectToken(6);
  cond = Parse_ParseExpression();
  if (Parse_IsTypeGuard(cond)) {
    s = Parse_ParseTypeCase(cond);
  } else {
    if (!(((1 << (*(*cond).typ).kind) & 36))) {
      Lex_ErrorLn(&(Parse_l), "CASE requires INTEGER or CHAR", 30);
    }
    Parse_ExpectToken(23);
    head = Parse_ParseCase(cond);
    tail = head;
    while (Parse_MatchToken(51)) {
      s = Parse_ParseCase(cond);
      if (tail == 0 /*NULL*/) {
        head = s;
        tail = head;
      } else {
        (*tail).elsifs = s;
        if (s != 0 /*NULL*/) {
          tail = (*tail).elsifs;
        }

      }
    }
    Parse_ExpectToken(12);
    s = AST_NewStmtCase(cond, head);

  }
  return (s);
}
AST_Stmt AST_NewStmtWhile(AST_Expr cond, AST_Stmt body);
AST_Stmt AST_NewStmtWhile(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  assert(((*(*cond).typ).kind == 4));
  AST_NewStmt(&(s), 4);
  (*s).cond = cond;
  (*s).body = body;
  return s;
  return (s);
}
AST_Stmt Parse_ParseWhileStatement(void);
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
  return s;
  return (s);
}
AST_Stmt AST_NewStmtRepeat(AST_Expr cond, AST_Stmt body);
AST_Stmt AST_NewStmtRepeat(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  assert(((*(*cond).typ).kind == 4));
  AST_NewStmt(&(s), 5);
  (*s).cond = cond;
  (*s).body = body;
  return s;
  return (s);
}
AST_Stmt Parse_ParseRepeatStatement(void);
AST_Stmt Parse_ParseRepeatStatement(void) {
  AST_Stmt s;
  Parse_ExpectToken(28);
  s = Parse_ParseStatementSequence();
  Parse_ExpectToken(34);
  s = AST_NewStmtRepeat(Parse_ParseBooleanExpression(), s);
  return s;
  return (s);
}
AST_Expr AST_NewExprAssign(const Lex_Lexer  *l, AST_Expr lValue, AST_Expr rValue);
AST_Expr AST_NewExprAssign(const Lex_Lexer  *l, AST_Expr lValue, AST_Expr rValue) {
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
  return e;
  return (e);
}
AST_Stmt AST_NewStmtFor(AST_Expr cond, AST_Stmt body);
AST_Stmt AST_NewStmtFor(AST_Expr cond, AST_Stmt body) {
  AST_Stmt s;
  assert(((*cond).kind == 12));
  assert(((1 << (*(*cond).typ).kind) & 12));
  AST_NewStmt(&(s), 6);
  (*s).cond = cond;
  (*s).body = body;
  return s;
  return (s);
}
AST_Stmt Parse_ParseForStatement(void);
AST_Stmt Parse_ParseForStatement(void) {
  AST_Decl d;
  AST_Expr startExpr;
  AST_Expr endExpr;
  AST_Expr byExpr;
  AST_Stmt s;
  Parse_ExpectToken(14);
  d = Decls_LookupDecl(&(Parse_l), Parse_ExpectIdentifier());
  startExpr = AST_NewExprIdentRef(&(Parse_l), d);
  Parse_ExpectToken(58);
  startExpr = AST_NewExprAssign(&(Parse_l), startExpr, Parse_ParseExpression());
  Parse_ExpectToken(31);
  endExpr = AST_NewExprAssign(&(Parse_l), (*startExpr).lhs, Parse_ParseExpression());
  endExpr = (*endExpr).rhs;
  byExpr = ((AST_Expr)0 /*NULL*/);
  if (Parse_MatchToken(5)) {
    byExpr = AST_NewExprAssign(&(Parse_l), (*startExpr).lhs, Parse_ParseExpression());
    byExpr = (*byExpr).rhs;
  }
  (*startExpr).next = endExpr;
  (*endExpr).next = byExpr;
  Parse_ExpectToken(9);
  s = AST_NewStmtFor(startExpr, Parse_ParseStatementSequence());
  Parse_ExpectToken(12);
  return s;
  return (s);
}
void Decls_NewDecl(AST_Decl  *d, INTEGER name);
void Decls_NewDecl(AST_Decl  *d, INTEGER name) {
  (*d) = malloc(sizeof(AST_DeclDesc));
  (*(*d)).qname.name = name;
  (*(*d)).qname.moduleName = AST_currentModuleName;
  (*(*d)).kind = 0;
  (*(*d)).typ = ((AST_Type)0 /*NULL*/);
  (*(*d)).origTyp = ((AST_Type)0 /*NULL*/);
  (*(*d)).expr = ((AST_Expr)0 /*NULL*/);
  (*(*d)).body = ((AST_Stmt)0 /*NULL*/);
  (*(*d)).next = ((AST_Decl)0 /*NULL*/);
  (*(*d)).nesting = 0;
  (*(*d)).procVars = ((AST_Decl)0 /*NULL*/);
  (*(*d)).exported = 0;
  (*(*d)).isNative = 0;
  (*(*d)).state = 0;
  (*(*d)).offset = -1;
}
AST_Decl Decls_AddDecl(const Lex_Lexer  *l, AST_Decl  *chain, INTEGER name);
AST_Decl Decls_AddDecl(const Lex_Lexer  *l, AST_Decl  *chain, INTEGER name) {
  AST_Decl p;
  AST_Decl d;
  Decls_NewDecl(&(d), name);
  if ((*chain) == 0 /*NULL*/) {
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
      Lex_PrintLnAndHalt(" already defined", 17);
    } else {
      (*d).next = (*p).next;
      (*p).next = d;

    }

  }
  return d;
  return (d);
}
AST_Decl Decls_AddScopeDecl(const Lex_Lexer  *l, INTEGER name);
AST_Decl Decls_AddScopeDecl(const Lex_Lexer  *l, INTEGER name) {
  return Decls_AddDecl(&((*l)), &(Decls_scope), name);
  return (Decls_AddDecl(&((*l)), &(Decls_scope), name));
}
AST_Stmt AST_NewStmtAssign(AST_Expr e);
AST_Stmt AST_NewStmtAssign(AST_Expr e) {
  AST_Stmt s;
  assert(((*e).kind == 12));
  AST_NewStmt(&(s), 1);
  (*s).cond = e;
  return s;
  return (s);
}
AST_Stmt Parse_ParseVarStatement(void);
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
  e = AST_NewExprAssign(&(Parse_l), AST_NewExprIdentRef(&(Parse_l), d), e);
  return AST_NewStmtAssign(e);
  return (AST_NewStmtAssign(e));
}
AST_Stmt AST_NewStmtProcCall(AST_Expr e);
AST_Stmt AST_NewStmtProcCall(AST_Expr e) {
  AST_Stmt s;
  assert(((1 << (*e).kind) & 2080));
  AST_NewStmt(&(s), 2);
  (*s).cond = e;
  return s;
  return (s);
}
AST_Stmt Parse_ParseAssignOrProcCall(void);
AST_Stmt Parse_ParseAssignOrProcCall(void) {
  AST_Expr e;
  AST_Expr args;
  AST_Stmt s;
  e = Parse_ParseDesignator();
  if (Parse_MatchToken(58)) {
    e = AST_NewExprAssign(&(Parse_l), e, Parse_ParseExpression());
    s = AST_NewStmtAssign(e);
  } else {
    args = ((AST_Expr)0 /*NULL*/);
    if (Parse_IsToken(52)) {
      args = Parse_ParseActualParameters();
    }
    e = AST_NewExprProcCall(&(Parse_l), e, args);
    s = AST_NewStmtProcCall(e);

  }
  return s;
  return (s);
}
AST_Expr AST_ValidateReturnStatement(const Lex_Lexer  *l, AST_Decl procDecl, AST_Expr e);
AST_Expr AST_ValidateReturnStatement(const Lex_Lexer  *l, AST_Decl procDecl, AST_Expr e) {
  assert(((*procDecl).kind == 5));
  assert(((*(*procDecl).typ).kind == 12));
  if ((*(*(*procDecl).typ).base).kind == 1) {
    Lex_ErrorLn(&((*l)), "RETURN statement unexpected", 28);
  }
  if ((*(*e).typ).kind != 1) {
    AST_ExpectType(&((*l)), e, (*(*(*procDecl).typ).base).kind);
  }
  return e;
  return (e);
}
AST_Stmt AST_NewStmtReturn(AST_Expr e);
AST_Stmt AST_NewStmtReturn(AST_Expr e) {
  AST_Stmt s;
  AST_NewStmt(&(s), 12);
  (*s).cond = e;
  return s;
  return (s);
}
AST_Stmt Parse_ParseReturnStatement(void);
AST_Stmt Parse_ParseReturnStatement(void) {
  Parse_ExpectToken(29);
  (*Parse_currentProcDecl).expr = AST_ValidateReturnStatement(&(Parse_l), Parse_currentProcDecl, Parse_ParseExpression());
  return AST_NewStmtReturn((*Parse_currentProcDecl).expr);
  return (AST_NewStmtReturn((*Parse_currentProcDecl).expr));
}
AST_Stmt AST_NewStmtEmpty(void);
AST_Stmt AST_NewStmtEmpty(void) {
  AST_Stmt s;
  AST_NewStmt(&(s), 13);
  return s;
  return (s);
}
AST_Stmt Parse_ParseStatement(void);
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
  } else if (Parse_IsToken(29) && Parse_allowLanguageExtensions) {
    s = Parse_ParseReturnStatement();
  } else {
    s = AST_NewStmtEmpty();








  }
  return s;
  return (s);
}
AST_Stmt Parse_ParseStatementSequence0(void);
AST_Stmt Parse_ParseStatementSequence0(void) {
  AST_Stmt head;
  AST_Stmt tail;
  head = Parse_ParseStatement();
  tail = head;
  while (Parse_MatchToken(50)) {
    (*tail).next = Parse_ParseStatement();
    tail = (*tail).next;
  }
  return head;
  return (head);
}
AST_Type Parse_ParseQualidentAndGetType(void);
AST_Type Parse_ParseQualidentAndGetType(void) {
  AST_Decl d;
  AST_Type t;
  t = ((AST_Type)0 /*NULL*/);
  d = Parse_ParseQualident();
  if (d != 0 /*NULL*/) {
    t = (*d).typ;
    if ((*d).kind != 3) {
      Lex_Error(&(Parse_l), "", 1);
      Lex_OutStr(&(Parse_l), (*d).qname.name);
      Lex_PrintLnAndHalt(" is not a TYPE", 15);
    }
  }
  return t;
  return (t);
}
void Decls_NewType(AST_Type  *t, INTEGER kind);
void Decls_NewType(AST_Type  *t, INTEGER kind) {
  (*t) = malloc(sizeof(AST_TypeDesc));
  (*(*t)).kind = kind;
  (*(*t)).base = ((AST_Type)0 /*NULL*/);
  (*(*t)).fields = ((AST_Decl)0 /*NULL*/);
  (*(*t)).length = 0;
  (*(*t)).nesting = 0;
  (*(*t)).needTypeInfo = 0;
  (*(*t)).decl = ((AST_Decl)0 /*NULL*/);
  (*(*t)).reachable = 0;
}
AST_Type Decls_NewBufferType(AST_Type base);
AST_Type Decls_NewBufferType(AST_Type base) {
  AST_Type t;
  Decls_NewType(&(t), 10);
  (*t).length = -1;
  (*t).base = base;
  return t;
  return (t);
}
AST_Type Decls_NewArrayType(const Lex_Lexer  *l, AST_Expr length);
AST_Type Decls_NewArrayType(const Lex_Lexer  *l, AST_Expr length) {
  AST_Type t;
  Decls_NewType(&(t), 9);
  if (AST_IsConst(length) && ((*(*length).typ).kind == 2)) {
    (*t).length = (*length).iVal;
  } else {
    Lex_ErrorLn(&((*l)), "ARRAY length must be a CONST INTEGER", 37);

  }
  return t;
  return (t);
}
AST_Type Parse_ParseArrayType(void);
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
    assert(((*e).iVal > 0));
    last = outer;
    while (Parse_MatchToken(49)) {
      e = Parse_ParseExpression();
      current = Decls_NewArrayType(&(Parse_l), e);
      assert(((*e).iVal > 0));
      (*last).base = current;
      last = current;
    }
    Parse_ExpectToken(23);
    current = Parse_ParseType();
    (*last).base = current;

  }
  return outer;
  return (outer);
}
INTEGER AST_GetNextTypeId(void);
INTEGER AST_GetNextTypeId(void) {
  AST_nextTypeId++;
  return AST_nextTypeId;
  return (AST_nextTypeId);
}
void AST_SetRecordToParent(INTEGER tid, INTEGER base);
void AST_SetRecordToParent(INTEGER tid, INTEGER base) {
  AST_recordToParent[tid] = base;
}
AST_Type Decls_NewRecordType(const Lex_Lexer  *l, AST_Type base);
AST_Type Decls_NewRecordType(const Lex_Lexer  *l, AST_Type base) {
  AST_Type t;
  AST_Decl d;
  AST_Decl dCopy;
  Decls_NewType(&(t), 11);
  (*t).base = base;
  (*t).typeId = AST_GetNextTypeId();
  if (base == 0 /*NULL*/) {
    AST_SetRecordToParent((*t).typeId, 0);
  } else {
    AST_SetRecordToParent((*t).typeId, (*base).typeId);
    (*t).nesting = ((*base).nesting + 1);

  }
  if (base != 0 /*NULL*/) {
    if ((*base).kind == 11) {
      d = (*base).fields;
      while ((d != 0 /*NULL*/) && ((*d).kind != 1001)) {
        dCopy = Decls_AddDecl(&((*l)), &((*t).fields), (*d).qname.name);
        (*dCopy).kind = (*d).kind;
        (*dCopy).typ = (*d).typ;
        (*dCopy).exported = (*d).exported;
        (*dCopy).nesting = ((*d).nesting + 1);
        d = (*d).next;
      }
    } else {
      Lex_ErrorLn(&((*l)), "RECORD base type is not a RECORD", 33);

    }
  }
  return t;
  return (t);
}
AST_Decl Parse_ParseFieldIdentDef(AST_Decl  *recordScope);
AST_Decl Parse_ParseFieldIdentDef(AST_Decl  *recordScope) {
  AST_Decl d;
  INTEGER name;
  name = Parse_ExpectIdentifier();
  d = Decls_AddDecl(&(Parse_l), &((*recordScope)), name);
  if (Parse_MatchToken(44)) {
    (*d).exported = 1;
  }
  return d;
  return (d);
}
AST_Type Parse_ParseRecordType(void);
AST_Type Parse_ParseRecordType(void) {
  AST_Type r;
  AST_Type base;
  AST_Type fieldType;
  AST_Decl baseDecl;
  AST_Decl firstField;
  AST_Decl lastField;
  BOOLEAN isNative;
  base = ((AST_Type)0 /*NULL*/);
  Parse_ExpectToken(27);
  if (Parse_MatchToken(52)) {
    baseDecl = Parse_ParseQualident();
    Parse_ExpectToken(53);
    if (baseDecl != 0 /*NULL*/) {
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
      while (((firstField != 0 /*NULL*/) && (lastField != 0 /*NULL*/)) && (firstField != (*lastField).next)) {
        (*firstField).kind = 8;
        (*firstField).typ = fieldType;
        (*firstField).isNative = isNative;
        firstField = (*firstField).next;
      }
      Parse_MatchToken(50);
    } while (!(Parse_IsToken(12) || Parse_IsToken(70)));

  }
  Parse_ExpectToken(12);
  return r;
  return (r);
}
void Lex_MakeDummy(INTEGER i, CHAR  *s, INTEGER s__len);
void Lex_MakeDummy(INTEGER i, CHAR  *s, INTEGER s__len) {
  (void)s__len;
  s[0] = 'i';
  s[4] = ((i % 10) + 48);
  i = (i / 10);
  s[3] = ((i % 10) + 48);
  i = (i / 10);
  s[2] = ((i % 10) + 48);
  i = (i / 10);
  s[1] = ((i % 10) + 48);
  s[5] = 0;
}
INTEGER Lex_Intern(Lex_Lexer  *l, const CHAR  *s, INTEGER s__len);
INTEGER Lex_Intern(Lex_Lexer  *l, const CHAR  *s, INTEGER s__len) {
  (void)s__len;
  return Lex_StringIntern(&((*l).sp), s, s__len);
  return (Lex_StringIntern(&((*l).sp), s, s__len));
}
void Decls_MakeSyntheticDecl(Lex_Lexer  *l, AST_Type base);
void Decls_MakeSyntheticDecl(Lex_Lexer  *l, AST_Type base) {
  CHAR name[10];
  assert(((*base).kind == 11));
  if ((*base).decl == 0 /*NULL*/) {
    Lex_MakeDummy(Decls_genSymNum, name, 10);
    Decls_NewDecl(&((*base).decl), Lex_Intern(&((*l)), name, 10));
    (*(*base).decl).kind = 3;
    (*(*base).decl).typ = base;
    Decls_genSymNum++;
  }
}
AST_Type Decls_NewPointerType(Lex_Lexer  *l, AST_Type base);
AST_Type Decls_NewPointerType(Lex_Lexer  *l, AST_Type base) {
  AST_Type t;
  t = ((AST_Type)0 /*NULL*/);
  if ((base != 0 /*NULL*/) && ((*base).kind != 11)) {
    Lex_ErrorLn(&((*l)), "Pointer base type must be a RECORD", 35);
  } else {
    Decls_MakeSyntheticDecl(&((*l)), base);
    Decls_NewType(&(t), 8);
    (*t).base = base;

  }
  return t;
  return (t);
}
AST_Type Decls_NewPointerTypeByName(Lex_Lexer  *l, INTEGER name);
AST_Type Decls_NewPointerTypeByName(Lex_Lexer  *l, INTEGER name) {
  AST_Decl d;
  Decls_Forward f;
  AST_Type t;
  t = ((AST_Type)0 /*NULL*/);
  d = Decls_LookupDecl0(name);
  if (d == 0 /*NULL*/) {
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
      Lex_PrintLnAndHalt(" is not a TYPE", 15);
    }
    t = Decls_NewPointerType(&((*l)), (*d).typ);

  }
  return t;
  return (t);
}
AST_Type Parse_ParsePointerType(void);
AST_Type Parse_ParsePointerType(void) {
  AST_Type t;
  Parse_ExpectToken(25);
  Parse_ExpectToken(31);
  if (Parse_IsToken(37)) {
    t = Decls_NewPointerTypeByName(&(Parse_l), Parse_ExpectIdentifier());
  } else {
    t = Decls_NewPointerType(&(Parse_l), Parse_ParseType());

  }
  return t;
  return (t);
}
AST_Type Decls_NewProcedureType(void);
AST_Type Decls_NewProcedureType(void) {
  AST_Type t;
  Decls_NewType(&(t), 12);
  (*t).base = Decls_nilType;
  return t;
  return (t);
}
void Parse_ParseFPSection(AST_Type procType);
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
  while (((firstParam != 0 /*NULL*/) && (lastParam != 0 /*NULL*/)) && (firstParam != (*lastParam).next)) {
    (*firstParam).typ = paramType;
    firstParam = (*firstParam).next;
  }
}
void Decls_CountProcedureArgs(AST_Type t);
void Decls_CountProcedureArgs(AST_Type t) {
  INTEGER i;
  AST_Decl p;
  i = 0;
  p = (*t).fields;
  while ((p != 0 /*NULL*/) && ((*p).kind != 1001)) {
    i++;
    p = (*p).next;
  }
  (*t).length = i;
}
AST_Type Parse_ParseFormalParameters(void);
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
  return t;
  return (t);
}
AST_Type Parse_ParseProcedureType(void);
AST_Type Parse_ParseProcedureType(void) {
  Parse_ExpectToken(26);
  return Parse_ParseFormalParameters();
  return (Parse_ParseFormalParameters());
}
AST_Type Parse_ParseType0(void);
AST_Type Parse_ParseType0(void) {
  AST_Type t;
  t = ((AST_Type)0 /*NULL*/);
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
  return t;
  return (t);
}
AST_Decl Parse_ParseIdentDef(void);
AST_Decl Parse_ParseIdentDef(void) {
  AST_Decl d;
  INTEGER n;
  n = Parse_ExpectIdentifier();
  d = Decls_AddScopeDecl(&(Parse_l), n);
  (*d).nesting = Parse_nesting;
  if (Parse_MatchToken(44)) {
    (*d).exported = 1;
  }
  return d;
  return (d);
}
void Parse_ParseConstDeclaration(void);
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
void Parse_ParseTypeDeclaration(void);
void Parse_ParseTypeDeclaration(void) {
  AST_Decl d;
  d = Parse_ParseIdentDef();
  Parse_ExpectToken(60);
  (*d).kind = 3;
  (*d).typ = Parse_ParseType();
  if ((*(*d).typ).decl == 0 /*NULL*/) {
    (*(*d).typ).decl = d;
  }
}
void Decls_ResolveForwards(const Lex_Lexer  *l);
void Decls_ResolveForwards(const Lex_Lexer  *l) {
  AST_Decl d;
  while (Decls_fwds != 0 /*NULL*/) {
    assert(((*(*Decls_fwds).t).kind == 8));
    d = Decls_LookupDecl(&((*l)), (*(*(*Decls_fwds).t).fields).qname.name);
    if (((d != 0 /*NULL*/) && ((*d).kind == 3)) && ((*(*d).typ).kind == 11)) {
      (*(*Decls_fwds).t).base = (*d).typ;
      (*(*Decls_fwds).t).fields = ((AST_Decl)0 /*NULL*/);
    } else {
      Lex_Error(&((*l)), "Bad forward declaration ", 25);
      Lex_OutStr(&((*l)), (*(*(*Decls_fwds).t).fields).qname.name);
      Lex_Ln();

    }
    Decls_fwds = (*Decls_fwds).next;
  }
}
void Parse_ParseVarDeclaration(void);
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
  while (((first != 0 /*NULL*/) && (last != 0 /*NULL*/)) && (first != (*last).next)) {
    (*first).kind = 4;
    (*first).typ = t;
    first = (*first).next;
  }
}
AST_Decl Parse_ParseProcedureHeading(void);
AST_Decl Parse_ParseProcedureHeading(void) {
  AST_Decl d;
  BOOLEAN isNative;
  AST_Expr e;
  isNative = Parse_MatchToken(21);
  if (isNative) {
    e = Parse_ParseExpression();
    assert(((*e).iVal < 0));
  }
  Parse_ExpectToken(26);
  d = Parse_ParseIdentDef();
  (*d).kind = 5;
  (*d).typ = Parse_ParseFormalParameters();
  (*d).isNative = isNative;
  if (isNative) {
    (*d).offset = (*e).iVal;
  }
  return d;
  return (d);
}
AST_Decl Decls_OpenScope(void);
AST_Decl Decls_OpenScope(void) {
  AST_Decl d;
  AST_Decl oldScope;
  Decls_NewDecl(&(d), 0);
  (*d).kind = 1001;
  (*d).next = Decls_scope;
  oldScope = Decls_scope;
  Decls_scope = d;
  return oldScope;
  return (oldScope);
}
void Decls_AddFormalParamsToScope(const Lex_Lexer  *l, AST_Decl procDecl);
void Decls_AddFormalParamsToScope(const Lex_Lexer  *l, AST_Decl procDecl) {
  AST_Decl formal;
  AST_Decl actual;
  assert(((*procDecl).kind == 5));
  assert(((*(*procDecl).typ).kind == 12));
  formal = (*(*procDecl).typ).fields;
  while (formal != 0 /*NULL*/) {
    actual = Decls_AddScopeDecl(&((*l)), (*formal).qname.name);
    (*actual).kind = (*formal).kind;
    (*actual).typ = (*formal).typ;
    formal = (*formal).next;
  }
}
void AST_CheckReturnStatement(const Lex_Lexer  *l, AST_Decl procDecl);
void AST_CheckReturnStatement(const Lex_Lexer  *l, AST_Decl procDecl) {
  if (((*(*(*procDecl).typ).base).kind != 1) && ((*procDecl).expr == 0 /*NULL*/)) {
    Lex_ErrorLn(&((*l)), "Missing RETURN statement", 25);
  }
}
AST_Decl Decls_CurrentScope(void);
AST_Decl Decls_CurrentScope(void) {
  return Decls_scope;
  return (Decls_scope);
}
void Decls_CloseScope(AST_Decl s);
void Decls_CloseScope(AST_Decl s) {
  Decls_scope = s;
}
void Parse_ParseProcedureBody(AST_Decl procDecl);
void Parse_ParseProcedureBody(AST_Decl procDecl) {
  AST_Decl oldScope;
  AST_Decl oldProcDecl;
  oldScope = Decls_OpenScope();
  oldProcDecl = Parse_currentProcDecl;
  Parse_currentProcDecl = procDecl;
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
  AST_CheckReturnStatement(&(Parse_l), procDecl);
  (*procDecl).procVars = Decls_CurrentScope();
  Parse_nesting--;
  Parse_currentProcDecl = oldProcDecl;
  Decls_CloseScope(oldScope);
}
void Parse_ParseProcedureDeclaration(void);
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
    Lex_PrintLnAndHalt("]", 2);
  }
}
void Parse_ParseDeclarationSequence0(void);
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
void Decls_AddTypeDecl(Lex_Lexer  *l, INTEGER name, AST_Type t);
void Decls_AddTypeDecl(Lex_Lexer  *l, INTEGER name, AST_Type t) {
  AST_Decl d;
  d = Decls_AddDecl(&((*l)), &(Decls_scope), name);
  (*d).kind = 3;
  (*d).typ = t;
  if ((*(*d).typ).decl == 0 /*NULL*/) {
    (*(*d).typ).decl = d;
  }
}
void Decls_AddBuiltin(Lex_Lexer  *l, INTEGER name, AST_BuiltinResolver callback);
void Decls_AddBuiltin(Lex_Lexer  *l, INTEGER name, AST_BuiltinResolver callback) {
  AST_Decl d;
  d = Decls_AddDecl(&((*l)), &(Decls_scope), name);
  (*d).kind = 9;
  (*d).typ = Decls_nilType;
  (*d).resolver = callback;
}
AST_Expr Decls_builtinAbs(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinAbs(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 1;
  (*e).rhs = args;
  if ((args == 0 /*NULL*/) || ((*args).next != 0 /*NULL*/)) {
    Lex_ErrorLn(&((*l)), "ABS expects 1 argument", 23);
  }
  if ((1 << (*(*args).typ).kind) & 12) {
    (*e).typ = (*args).typ;
  } else {
    Lex_ErrorLn(&((*l)), "ABS expects INTEGER or REAL", 28);

  }
  return e;
  return (e);
}
AST_Expr Decls_builtinInc(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinInc(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 8;
  (*e).rhs = args;
  if ((args == 0 /*NULL*/) || (((*args).next != 0 /*NULL*/) && ((*(*args).next).next != 0 /*NULL*/))) {
    Lex_ErrorLn(&((*l)), "INC expects 1 or 2 arguments", 29);
  }
  if (!((*args).assignable)) {
    Lex_ErrorLn(&((*l)), "First argument to INC must be assignable", 41);
  }
  if (((*args).next != 0 /*NULL*/) && ((*(*(*args).next).typ).kind != 2)) {
    Lex_ErrorLn(&((*l)), "Second arg to INC must be an INTEGER", 37);
  }
  return e;
  return (e);
}
AST_Expr Decls_builtinDec(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinDec(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 4;
  (*e).rhs = args;
  if ((args == 0 /*NULL*/) || (((*args).next != 0 /*NULL*/) && ((*(*args).next).next != 0 /*NULL*/))) {
    Lex_ErrorLn(&((*l)), "DEC expects 1 or 2 arguments", 29);
  }
  if (!((*args).assignable)) {
    Lex_ErrorLn(&((*l)), "First argument to DEC must be assignable", 41);
  }
  if (((*args).next != 0 /*NULL*/) && ((*(*(*args).next).typ).kind != 2)) {
    Lex_ErrorLn(&((*l)), "Second arg to DEC must be an INTEGER", 37);
  }
  return e;
  return (e);
}
AST_Expr Decls_builtinAssert(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinAssert(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 2;
  (*e).rhs = args;
  if ((args == 0 /*NULL*/) || ((*args).next != 0 /*NULL*/)) {
    Lex_ErrorLn(&((*l)), "ASSERT expects 1 argument", 26);
  }
  if ((*(*args).typ).kind == 4) {
    (*e).typ = (*args).typ;
  } else {
    Lex_ErrorLn(&((*l)), "ASSERT expects a BOOLEAN", 25);

  }
  return e;
  return (e);
}
AST_Expr Decls_builtinOrd(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinOrd(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 11;
  (*e).rhs = args;
  if (AST_IsConst((*e).rhs)) {
    AST_CoerceToChar(&((*l)), (*e).rhs, Decls_charType);
  }
  if ((args == 0 /*NULL*/) || ((*args).next != 0 /*NULL*/)) {
    Lex_ErrorLn(&((*l)), "ORD expects 1 argument", 23);
  }
  if (((1 << (*(*args).typ).kind) & 112) || (((*(*args).typ).kind == 7) && Lex_IsOneChar(&((*l)), (*args).iVal))) {
    (*e).typ = Decls_integerType;
  } else {
    Lex_ErrorLn(&((*l)), "ORD expects CHAR, BOOLEAN, or SET", 34);

  }
  return e;
  return (e);
}
AST_Expr Decls_builtinChr(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinChr(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 3;
  (*e).rhs = args;
  if ((args == 0 /*NULL*/) || ((*args).next != 0 /*NULL*/)) {
    Lex_ErrorLn(&((*l)), "CHR expects 1 argument", 23);
  }
  if ((*(*args).typ).kind == 2) {
    (*e).typ = Decls_charType;
  } else {
    Lex_ErrorLn(&((*l)), "CHR expects an INTEGER", 23);

  }
  return e;
  return (e);
}
AST_Expr Decls_builtinFloor(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinFloor(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 5;
  (*e).rhs = args;
  if ((args == 0 /*NULL*/) || ((*args).next != 0 /*NULL*/)) {
    Lex_ErrorLn(&((*l)), "FLOOR expects 1 argument", 25);
  }
  if ((*(*args).typ).kind == 3) {
    (*e).typ = Decls_integerType;
  } else {
    Lex_ErrorLn(&((*l)), "FLOOR expects a REAL", 21);

  }
  return e;
  return (e);
}
AST_Expr Decls_builtinFlt(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinFlt(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 6;
  (*e).rhs = args;
  if ((args == 0 /*NULL*/) || ((*args).next != 0 /*NULL*/)) {
    Lex_ErrorLn(&((*l)), "FLT expects 1 argument", 23);
  }
  if ((*(*args).typ).kind == 2) {
    (*e).typ = Decls_realType;
  } else {
    Lex_ErrorLn(&((*l)), "FLT expects an INTEGER", 23);

  }
  return e;
  return (e);
}
AST_Expr Decls_builtinLen(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinLen(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 9;
  (*e).rhs = args;
  if ((args == 0 /*NULL*/) || ((*args).next != 0 /*NULL*/)) {
    Lex_ErrorLn(&((*l)), "LEN expects 1 argument", 23);
  }
  if ((1 << (*(*args).typ).kind) & 1536) {
    (*e).typ = Decls_integerType;
  } else {
    Lex_ErrorLn(&((*l)), "LEN expects an ARRAY", 21);

  }
  return e;
  return (e);
}
AST_Expr Decls_builtinNew(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinNew(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 10;
  (*e).rhs = args;
  if ((args == 0 /*NULL*/) || ((*args).next != 0 /*NULL*/)) {
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
  return e;
  return (e);
}
AST_Expr Decls_builtinInit(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinInit(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 7;
  (*e).rhs = args;
  if (((args == 0 /*NULL*/) || ((*args).next == 0 /*NULL*/)) || ((*(*args).next).next != 0 /*NULL*/)) {
    Lex_ErrorLn(&((*l)), "NEW_ARRAY expects 2 arguments", 30);
  }
  if ((*(*(*args).next).typ).kind != 2) {
    Lex_ErrorLn(&((*l)), "Second arg to NEW_ARRAY must be an INTEGER", 43);
  }
  if ((*(*args).typ).kind == 10) {
    (*e).typ = Decls_nilType;
  } else {
    Lex_ErrorLn(&((*l)), "First arg to NEW_ARRAY expects an ARRAY *", 42);

  }
  return e;
  return (e);
}
AST_Expr Decls_builtinPush(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinPush(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 12;
  (*e).rhs = args;
  if (((args == 0 /*NULL*/) || ((*args).next == 0 /*NULL*/)) || ((*(*args).next).next != 0 /*NULL*/)) {
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
  return e;
  return (e);
}
AST_Expr Decls_builtinReadInt(const Lex_Lexer  *l, AST_Expr args);
AST_Expr Decls_builtinReadInt(const Lex_Lexer  *l, AST_Expr args) {
  AST_Expr e;
  AST_NewExpr(&(e), 11, Decls_nilType);
  (*e).iVal = 13;
  (*e).rhs = args;
  if ((args == 0 /*NULL*/) || ((*args).next != 0 /*NULL*/)) {
    Lex_ErrorLn(&((*l)), "ReadInt expects 1 argument", 27);
  }
  if (!((*args).assignable)) {
    Lex_ErrorLn(&((*l)), "Argument to ReadInt must be assignable", 39);
  }
  return e;
  return (e);
}
void Decls_InitGlobalScope(Lex_Lexer  *l);
void Decls_InitGlobalScope(Lex_Lexer  *l) {
  Decls_fwds = ((Decls_Forward)0 /*NULL*/);
  if (Decls_globalScope == 0 /*NULL*/) {
    Decls_scope = ((AST_Decl)0 /*NULL*/);
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
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "FLOOR", 6), Decls_builtinFloor);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "FLT", 4), Decls_builtinFlt);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "LEN", 4), Decls_builtinLen);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "NEW", 4), Decls_builtinNew);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "NEW_ARRAY", 10), Decls_builtinInit);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "PUSH", 5), Decls_builtinPush);
    Decls_AddBuiltin(&((*l)), Lex_Intern(&((*l)), "ReadInt", 8), Decls_builtinReadInt);
    if (Lex_ignoreKeywordCase) {
      Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "nil", 4), Decls_nilType);
      Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "integer", 8), Decls_integerType);
      Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "real", 5), Decls_realType);
      Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "boolean", 8), Decls_booleanType);
      Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "char", 5), Decls_charType);
      Decls_AddTypeDecl(&((*l)), Lex_Intern(&((*l)), "set", 4), Decls_setType);
    }
    Decls_globalScope = Decls_scope;
    Decls_modInitName = Lex_Intern(&((*l)), "_module_init_", 14);
  }
  Decls_scope = Decls_globalScope;
}
INTEGER AST_SetModuleName(INTEGER name);
INTEGER AST_SetModuleName(INTEGER name) {
  INTEGER oldModuleName;
  oldModuleName = AST_currentModuleName;
  AST_currentModuleName = name;
  return oldModuleName;
  return (oldModuleName);
}
void Lex_ImportHelper(Lex_Lexer  *l, INTEGER moduleName, Lex_LexCallback callback);
void Lex_ImportHelper(Lex_Lexer  *l, INTEGER moduleName, Lex_LexCallback callback) {
  CHAR savedBuf[65536];
  INTEGER savedFileName;
  CHAR fileName[128];
  INTEGER savedPos;
  INTEGER i;
  Lex_Token savedToken;
  strncpy(savedBuf, (*l).buf, 65536);
  savedFileName = (*l).fileName;
  savedPos = (*l).pos;
  savedToken = (*l).t;
  i = 0;
  while ((*l).sp.buf[(moduleName + i)] != 0) {
    fileName[i] = (*l).sp.buf[(moduleName + i)];
    i++;
  }
  fileName[i] = '.';
  fileName[(i + 1)] = 'o';
  fileName[(i + 2)] = 'b';
  fileName[(i + 3)] = 0;
  Out_ReadFile(fileName, 128, (*l).buf, 65536);
  (*l).fileName = Lex_StringIntern(&((*l).sp), fileName, 128);
  (*l).pos = 0;
  callback();
  (*l).t = savedToken;
  (*l).pos = savedPos;
  (*l).fileName = savedFileName;
  strncpy((*l).buf, savedBuf, 65536);
}
AST_Decl Parse_GetModuleImports(INTEGER moduleName);
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
    assert((Parse_importCacheEnd < 128));
    Lex_ImportHelper(&(Parse_l), moduleName, Parse_importCallback);
    d = Parse_lastModuleDecls;
    Parse_importCache[Parse_importCacheEnd].name = moduleName;
    Parse_importCache[Parse_importCacheEnd].decls = d;
    Parse_importCacheEnd++;

  }
  return d;
  return (d);
}
void Decls_AddImportDecl(const Lex_Lexer  *l, INTEGER name, AST_Decl decls);
void Decls_AddImportDecl(const Lex_Lexer  *l, INTEGER name, AST_Decl decls) {
  AST_Decl d;
  d = Decls_AddScopeDecl(&((*l)), name);
  (*d).kind = 1;
  Decls_NewType(&((*d).typ), 13);
  (*(*d).typ).fields = decls;
}
void Parse_ParseImport(void);
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
void Parse_ParseImportList(void);
void Parse_ParseImportList(void) {
  Parse_ExpectToken(16);
  Parse_ParseImport();
  while (Parse_MatchToken(49)) {
    Parse_ParseImport();
  }
  Parse_ExpectToken(50);
}
void Decls_NewModuleInitDecl(AST_Stmt body);
void Decls_NewModuleInitDecl(AST_Stmt body) {
  AST_Decl d;
  Decls_NewDecl(&(d), Decls_modInitName);
  (*d).kind = 5;
  (*d).typ = Decls_NewProcedureType();
  (*d).body = body;
  (*d).next = Decls_scope;
  Decls_scope = d;
}
void Parse_ParseModule(void);
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
    Decls_NewModuleInitDecl(0 /*NULL*/);

  }
  Parse_ExpectToken(12);
  e = Parse_ExpectIdentifier();
  if (s != e) {
    Lex_Error(&(Parse_l), "Module end name [", 18);
    Lex_OutStr(&(Parse_l), e);
    Lex_Str("] must match start name [", 26);
    Lex_OutStr(&(Parse_l), s);
    Lex_PrintLnAndHalt("]", 2);
  }
  Parse_ExpectToken(48);
  Parse_lastModuleDecls = Decls_CurrentScope();
  AST_SetModuleName(oldModule);
  Decls_CloseScope(d);
}
void Parse_ImportHelper(void);
void Parse_ImportHelper(void) {
  AST_Decl savedScope;
  savedScope = Decls_CurrentScope();
  Lex_NextToken(&(Parse_l));
  Parse_ParseModule();
  Decls_CloseScope(savedScope);
}
void Parse__module_init_(void);
void Parse__module_init_(void) {
  Parse_importCacheEnd = 0;
  Parse_currentProcDecl = ((AST_Decl)0 /*NULL*/);
  Parse_ParseExpression = Parse_ParseExpression0;
  Parse_ParseStatementSequence = Parse_ParseStatementSequence0;
  Parse_ParseType = Parse_ParseType0;
  Parse_ParseDeclarationSequence = Parse_ParseDeclarationSequence0;
  Parse_importCallback = Parse_ImportHelper;
  Parse_allowLanguageExtensions = 1;
}
void Lex_PoolInit(Lex_StringPool  *sp);
void Lex_PoolInit(Lex_StringPool  *sp) {
  INTEGER i;
  for (i = 0; i <= 65535; i++) {
    (*sp).buf[i] = 0;
  }
  (*sp).last = 0;
  for (i = 0; i <= 4095; i++) {
    (*sp).buckets[i] = -1;
  }
}
void Lex_InfoPrintLn(const CHAR  *s, INTEGER s__len);
void Lex_InfoPrintLn(const CHAR  *s, INTEGER s__len) {
  (void)s__len;
  Out_Str(s, s__len);
  Out_Ln();
}
void Lex_TestPool(void);
void Lex_TestPool(void) {
  Lex_StringPool sp;
  CHAR s[25];
  INTEGER i;
  INTEGER j;
  Lex_PoolInit(&(sp));
  assert((11 == Lex_StringLen("Hello world", 12)));
  strncpy(s, "Hello world", 25);
  assert(Lex_StrEq(s, 25, 0, "Hello world", 12, 0, 11));
  assert(!(Lex_StrEq(s, 25, 0, "Hello", 6, 0, 11)));
  assert(Lex_StrEq(s, 25, 1, "Hello world", 12, 1, 10));
  assert((11 == Lex_StringLen(s, 25)));
  assert((Lex_StringIntern(&(sp), s, 25) == 0));
  strncpy(s, "Yello world", 25);
  assert((Lex_StringIntern(&(sp), s, 25) == 12));
  i = Lex_StringInternRange(&(sp), "Hellooo", 8, 1, 4);
  assert((i == Lex_StringIntern(&(sp), "ello", 5)));
  j = Lex_StringInternRange(&(sp), s, 25, 0, 0);
  assert((i != j));
  assert((Lex_StringIntern(&(sp), "", 1) == j));
  s[0] = 'A';
  s[1] = 0;
  assert((Lex_StringIntern(&(sp), s, 25) == Lex_StringIntern(&(sp), "A", 2)));
  assert((Lex_StringIntern(&(sp), s, 25) != Lex_StringIntern(&(sp), "B", 2)));
  Lex_PoolInit(&(sp));
  for (i = 1; i <= 4000; i++) {
    Lex_MakeDummy(i, s, 25);
    Lex_StringIntern(&(sp), s, 25);
  }
  for (i = 1; i <= 4000; i++) {
    Lex_MakeDummy(i, s, 25);
    assert((Lex_StringIntern(&(sp), s, 25) == ((i - 1) * 6)));
  }
  assert((sp.last == 24000));
  Lex_PoolInit(&(sp));
  Lex_StringInternRange(&(sp), "A", 2, 0, 9);
  Lex_StringInternRange(&(sp), "PROCEDURE", 10, 0, 9);
  Lex_StringInternRange(&(sp), "B", 2, 0, 9);
  assert((Lex_StringIntern(&(sp), "A", 2) == 0));
  assert((Lex_StringIntern(&(sp), "PROCEDURE", 10) == 10));
  assert((Lex_StringIntern(&(sp), "B", 2) == 20));
  Lex_InfoPrintLn("PASS: String pool test", 23);
}
void Lex_Mute(void);
void Lex_Mute(void) {
  Lex_fatal = 0;
}
void Lex_AddKeywords(Lex_StringPool  *sp);
void Lex_AddKeywords(Lex_StringPool  *sp) {
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
  if (Lex_ignoreKeywordCase) {
    Lex_StringInternRange(&((*sp)), "array", 6, 0, 9);
    Lex_StringInternRange(&((*sp)), "begin", 6, 0, 9);
    Lex_StringInternRange(&((*sp)), "bitand", 7, 0, 9);
    Lex_StringInternRange(&((*sp)), "bitor", 6, 0, 9);
    Lex_StringInternRange(&((*sp)), "bitxor", 7, 0, 9);
    Lex_StringInternRange(&((*sp)), "by", 3, 0, 9);
    Lex_StringInternRange(&((*sp)), "case", 5, 0, 9);
    Lex_StringInternRange(&((*sp)), "const", 6, 0, 9);
    Lex_StringInternRange(&((*sp)), "div", 4, 0, 9);
    Lex_StringInternRange(&((*sp)), "do", 3, 0, 9);
    Lex_StringInternRange(&((*sp)), "else", 5, 0, 9);
    Lex_StringInternRange(&((*sp)), "elsif", 6, 0, 9);
    Lex_StringInternRange(&((*sp)), "end", 4, 0, 9);
    Lex_StringInternRange(&((*sp)), "false", 6, 0, 9);
    Lex_StringInternRange(&((*sp)), "for", 4, 0, 9);
    Lex_StringInternRange(&((*sp)), "if", 3, 0, 9);
    Lex_StringInternRange(&((*sp)), "import", 7, 0, 9);
    Lex_StringInternRange(&((*sp)), "in", 3, 0, 9);
    Lex_StringInternRange(&((*sp)), "is", 3, 0, 9);
    Lex_StringInternRange(&((*sp)), "mod", 4, 0, 9);
    Lex_StringInternRange(&((*sp)), "module", 7, 0, 9);
    Lex_StringInternRange(&((*sp)), "native", 7, 0, 9);
    Lex_StringInternRange(&((*sp)), "nil", 4, 0, 9);
    Lex_StringInternRange(&((*sp)), "of", 3, 0, 9);
    Lex_StringInternRange(&((*sp)), "or", 3, 0, 9);
    Lex_StringInternRange(&((*sp)), "pointer", 8, 0, 9);
    Lex_StringInternRange(&((*sp)), "procedure", 10, 0, 9);
    Lex_StringInternRange(&((*sp)), "record", 7, 0, 9);
    Lex_StringInternRange(&((*sp)), "repeat", 7, 0, 9);
    Lex_StringInternRange(&((*sp)), "return", 7, 0, 9);
    Lex_StringInternRange(&((*sp)), "then", 5, 0, 9);
    Lex_StringInternRange(&((*sp)), "to", 3, 0, 9);
    Lex_StringInternRange(&((*sp)), "true", 5, 0, 9);
    Lex_StringInternRange(&((*sp)), "type", 5, 0, 9);
    Lex_StringInternRange(&((*sp)), "until", 6, 0, 9);
    Lex_StringInternRange(&((*sp)), "var", 4, 0, 9);
    Lex_StringInternRange(&((*sp)), "while", 6, 0, 9);
  }
}
void Lex_LexerInitFromString(Lex_Lexer  *l, const CHAR  *s, INTEGER s__len);
void Lex_LexerInitFromString(Lex_Lexer  *l, const CHAR  *s, INTEGER s__len) {
  (void)s__len;
  Lex_PoolInit(&((*l).sp));
  Lex_AddKeywords(&((*l).sp));
  strncpy((*l).buf, s, 65536);
  (*l).fileName = Lex_StringIntern(&((*l).sp), "<string>", 9);
  (*l).pos = 0;
}
void Lex_Unmute(void);
void Lex_Unmute(void) {
  Lex_fatal = 1;
}
void Lex_LexerInitFromFile(Lex_Lexer  *l, const CHAR  *fileName, INTEGER fileName__len);
void Lex_LexerInitFromFile(Lex_Lexer  *l, const CHAR  *fileName, INTEGER fileName__len) {
  (void)fileName__len;
  Lex_PoolInit(&((*l).sp));
  Lex_AddKeywords(&((*l).sp));
  Out_ReadFile(fileName, fileName__len, (*l).buf, 65536);
  (*l).fileName = Lex_StringIntern(&((*l).sp), fileName, fileName__len);
  (*l).pos = 0;
}
void Lex_TestLexer(void);
void Lex_TestLexer(void) {
  Lex_Lexer l;
  INTEGER k;
  Lex_fatal = 0;
  Lex_ignoreKeywordCase = 0;
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
  Lex_LexerInitFromString(&(l), "\n      Test Hello World Test alpha..beta\n  ARRAY       BEGIN       BITAND      BITOR       BITXOR\n  BY          CASE        CONST       DIV         DO\n  ELSE        ELSIF       END         FALSE       FOR\n  IF          IMPORT      IN          IS          MOD\n  MODULE      NATIVE      NIL         OF          OR\n  POINTER     PROCEDURE   RECORD      REPEAT      RETURN\n  THEN        TO          TRUE        TYPE        UNTIL\n  VAR         WHILE\n      0FFD2H 041X\n      101 102 (103)Wow 104Whoa\n      0.1 0.1E4 0.08E-3 12.825e1\n      + - * / ~ & . , ; | ( ) [ ] { } := ^ = # < >\n      <= >=  .. 10..20\n      (* totally (* skipped *)*)\n      BITXOR\n  ", 650);
  l.buf[11] = '"';
  l.buf[23] = '"';
  Lex_NextToken(&(l));
  assert((l.t.kind == 37));
  assert((l.t.sVal == Lex_StringIntern(&(l.sp), "Test", 5)));
  Lex_NextToken(&(l));
  assert((l.t.kind == 39));
  assert((l.t.sVal == Lex_StringIntern(&(l.sp), "Hello World", 12)));
  Lex_NextToken(&(l));
  assert((l.t.kind == 37));
  assert((l.t.sVal == Lex_StringIntern(&(l.sp), "Test", 5)));
  Lex_NextToken(&(l));
  assert((l.t.kind == 37));
  assert((l.t.sVal == Lex_StringIntern(&(l.sp), "alpha", 6)));
  Lex_NextToken(&(l));
  assert((l.t.kind == 66));
  Lex_NextToken(&(l));
  assert((l.t.kind == 37));
  assert((l.t.sVal == Lex_StringIntern(&(l.sp), "beta", 5)));
  for (k = 0; k <= 36; k++) {
    Lex_NextToken(&(l));
    assert((l.t.kind == k));
  }
  Lex_NextToken(&(l));
  assert((l.t.kind == 40));
  assert((l.t.iVal == 65490));
  assert((l.t.iVal == 65490));
  Lex_NextToken(&(l));
  assert((l.t.kind == 39));
  assert((l.sp.buf[l.t.sVal] == 'A'));
  Lex_NextToken(&(l));
  assert((l.t.kind == 40));
  assert((l.t.iVal == 101));
  Lex_NextToken(&(l));
  assert((l.t.kind == 40));
  assert((l.t.iVal == 102));
  Lex_NextToken(&(l));
  assert((l.t.kind == 52));
  Lex_NextToken(&(l));
  assert((l.t.kind == 40));
  assert((l.t.iVal == 103));
  Lex_NextToken(&(l));
  assert((l.t.kind == 53));
  Lex_NextToken(&(l));
  assert((l.t.kind == 37));
  Lex_NextToken(&(l));
  assert((l.t.kind == 40));
  assert((l.t.iVal == 104));
  Lex_NextToken(&(l));
  assert((l.t.kind == 37));
  Lex_NextToken(&(l));
  assert((l.t.kind == 41));
  assert((oberon_abs((l.t.rVal - 0.100000)) < 0.000010));
  Lex_NextToken(&(l));
  assert((l.t.kind == 41));
  assert((oberon_abs((l.t.rVal - 1000.000000)) < 0.000010));
  Lex_NextToken(&(l));
  assert((l.t.kind == 41));
  assert((oberon_abs((l.t.rVal - 0.000080)) < 0.000010));
  Lex_NextToken(&(l));
  assert((l.t.kind == 41));
  assert((oberon_abs((l.t.rVal - 128.250000)) < 0.000010));
  for (k = 42; k <= 66; k++) {
    Lex_NextToken(&(l));
    assert((l.t.kind == k));
  }
  Lex_NextToken(&(l));
  assert((l.t.kind == 40));
  assert((l.t.iVal == 10));
  Lex_NextToken(&(l));
  assert((l.t.kind == 66));
  Lex_NextToken(&(l));
  assert((l.t.kind == 40));
  assert((l.t.iVal == 20));
  Lex_NextToken(&(l));
  assert((l.t.kind == 4));
  Lex_NextToken(&(l));
  assert((l.t.kind == 70));
  Lex_NextToken(&(l));
  assert((l.t.kind == 70));
  Lex_ignoreKeywordCase = 1;
  Lex_LexerInitFromString(&(l), "\n  lower case testing\n  array       begin       bitand      bitor       bitxor\n  by          case        const       div         do\n  else        elsif       end         false       for\n  if          import      in          is          mod\n  module      native      nil         of          or\n  pointer     procedure   record      repeat      return\n  then        to          true        type        until\n  var         while\n  ", 429);
  Lex_NextToken(&(l));
  assert((l.t.kind == 37));
  assert((l.t.sVal == Lex_StringIntern(&(l.sp), "lower", 6)));
  Lex_NextToken(&(l));
  assert((l.t.kind == 6));
  Lex_NextToken(&(l));
  assert((l.t.kind == 37));
  assert((l.t.sVal == Lex_StringIntern(&(l.sp), "testing", 8)));
  for (k = 0; k <= 36; k++) {
    Lex_NextToken(&(l));
    assert((l.t.kind == k));
  }
  Lex_ignoreKeywordCase = 0;
  Lex_LexerInitFromString(&(l), "upper case testing", 19);
  Lex_NextToken(&(l));
  assert((l.t.kind == 37));
  assert((l.t.sVal == Lex_StringIntern(&(l.sp), "upper", 6)));
  Lex_NextToken(&(l));
  assert((l.t.kind == 37));
  assert((l.t.sVal == Lex_StringIntern(&(l.sp), "case", 5)));
  Lex_NextToken(&(l));
  assert((l.t.kind == 37));
  assert((l.t.sVal == Lex_StringIntern(&(l.sp), "testing", 8)));
  Lex_LexerInitFromFile(&(l), "Lex.ob", 7);
  do {
    Lex_NextToken(&(l));
  } while (!(l.t.kind == 70));

  Lex_InfoPrintLn("PASS: Lexer test", 17);
}
void Lex_RunTests(void);
void Lex_RunTests(void) {
  Lex_TestPool();
  Lex_TestLexer();
}
void Decls_TestCleanup(void);
void Decls_TestCleanup(void) {
  Decls_scope = ((AST_Decl)0 /*NULL*/);
  Decls_globalScope = ((AST_Decl)0 /*NULL*/);
}
void Decls_TestDecls(void);
void Decls_TestDecls(void) {
  Lex_Lexer l;
  AST_Decl d;
  AST_Type t;
  Lex_LexerInitFromString(&(l), "", 1);
  d = ((AST_Decl)0 /*NULL*/);
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
  assert((Decls_LookupDecl(&(l), 20) != 0 /*NULL*/));
  assert((Decls_LookupDecl(&(l), 100) == 0 /*NULL*/));
  Lex_Unmute();
  Decls_InitGlobalScope(&(l));
  assert((Decls_LookupDecl(&(l), Lex_Intern(&(l), "NIL", 4)) != 0 /*NULL*/));
  d = Decls_LookupDecl(&(l), Lex_Intern(&(l), "NIL", 4));
  assert(((*d).kind == 3));
  assert(((*(*d).typ).kind == 1));
  d = Decls_LookupDecl(&(l), Lex_Intern(&(l), "INTEGER", 8));
  assert(((*d).kind == 3));
  t = (*d).typ;
  d = Decls_LookupDecl(&(l), Lex_Intern(&(l), "BYTE", 5));
  assert((t == (*d).typ));
  Decls_TestCleanup();
  Lex_InfoPrintLn("PASS: Decls test", 17);
}
void Decls_RunTests(void);
void Decls_RunTests(void) {
  Decls_TestDecls();
}
void Parse_InitFromFile(const CHAR  *fileName, INTEGER fileName__len);
void Parse_InitFromFile(const CHAR  *fileName, INTEGER fileName__len) {
  (void)fileName__len;
  Lex_LexerInitFromFile(&(Parse_l), fileName, fileName__len);
  Lex_NextToken(&(Parse_l));
}
void Parse_TestParse(void);
void Parse_TestParse(void) {
  Parse_InitFromFile("Parse.ob", 9);
  Parse_ParseModule();
  Lex_InfoPrintLn("PASS: Parser test", 18);
}
void Parse_RunTests(void);
void Parse_RunTests(void) {
  Parse_TestParse();
}
void Compiler_RunTests(void);
void Compiler_RunTests(void) {
  Lex_RunTests();
  Decls_RunTests();
  Parse_RunTests();
}
void CCodegen_EnableBoundsChecks(void);
void CCodegen_EnableBoundsChecks(void) {
  CCodegen_addBoundsChecks = 1;
}
void CCodegen_EnableCPlusPlus(void);
void CCodegen_EnableCPlusPlus(void) {
  CCodegen_genCPlusPlus = 1;
}
INTEGER CCodegen_GenTypeinfoEntry(INTEGER tid, INTEGER count);
INTEGER CCodegen_GenTypeinfoEntry(INTEGER tid, INTEGER count) {
  if (AST_recordToParent[tid] != 0) {
    count = CCodegen_GenTypeinfoEntry(AST_recordToParent[tid], (count + 1));
    CCodegen_GenInt(AST_recordToParent[tid]);
    CCodegen_GenStr(", ", 3);
  }
  return (count);
}
void CCodegen_GenTypeinfos(void);
void CCodegen_GenTypeinfos(void) {
  INTEGER i;
  INTEGER c;
  CCodegen_GenStr("typedef int oberon_typeid;", 27);
  CCodegen_GenLn();
  CCodegen_GenStr("oberon_typeid oberon_typeinfos[1];", 35);
  CCodegen_GenLn();
  CCodegen_GenStr("typedef struct oberon_typedesc { int parent[6]; } oberon_typedesc;", 67);
  CCodegen_GenLn();
  CCodegen_GenStr("oberon_typedesc oberon_typedescs[] = {", 39);
  CCodegen_GenLn();
  CCodegen_indent++;
  for (i = 0; i <= AST_nextTypeId; i++) {
    CCodegen_GenI();
    CCodegen_GenStr("{ {", 4);
    c = CCodegen_GenTypeinfoEntry(i, 0);
    CCodegen_GenInt(i);
    CCodegen_GenStr(", ", 3);
    while (c < 5) {
      CCodegen_GenStr("-1, ", 5);
      c++;
    }
    CCodegen_GenStr("} },", 5);
    CCodegen_GenLn();
  }
  CCodegen_indent--;
  CCodegen_GenStr("};", 3);
  CCodegen_GenLn();
  CCodegen_GenStr("#include ", 10);
  CCodegen_GenStr("\"", 2);
  CCodegen_GenStr("runtime.c", 10);
  CCodegen_GenStr("\"", 2);
  CCodegen_GenLn();
}
void CCodegen_GenTypedef(const Lex_Lexer  *l, AST_Decl d);
void CCodegen_GenTypedef(const Lex_Lexer  *l, AST_Decl d) {
  if ((*(*d).typ).kind != 1) {
    CCodegen_GenI();
    CCodegen_GenStr("typedef ", 9);
    CCodegen_GenType(&((*l)), (*d).typ, &((*d).qname), 1, 0);
    CCodegen_GenStr(";", 2);
    CCodegen_GenLn();
  }
}
void CCodegen_GenVar(const Lex_Lexer  *l, AST_Decl d);
void CCodegen_GenVar(const Lex_Lexer  *l, AST_Decl d) {
  CCodegen_GenType(&((*l)), (*d).typ, &((*d).qname), 0, 0);
  CCodegen_GenStr(";", 2);
  CCodegen_GenLn();
}
void CCodegen_RenameInnerProc(Lex_Lexer  *l, AST_Decl d);
void CCodegen_RenameInnerProc(Lex_Lexer  *l, AST_Decl d) {
  CHAR name[10];
  Lex_MakeDummy(CCodegen_innerProcCount, name, 10);
  (*d).qname.name = Lex_Intern(&((*l)), name, 10);
  CCodegen_innerProcCount++;
}
void CCodegen_GenParenExpr(const Lex_Lexer  *l, AST_Expr e);
void CCodegen_GenParenExpr(const Lex_Lexer  *l, AST_Expr e) {
  if ((*e).kind == 3) {
    CCodegen_GenExpr(&((*l)), e);
  } else {
    CCodegen_GenStr("(", 2);
    CCodegen_GenExpr(&((*l)), e);
    CCodegen_GenStr(")", 2);

  }
}
BOOLEAN CCodegen_ForForwards(AST_Expr e);
BOOLEAN CCodegen_ForForwards(AST_Expr e) {
  return (((e == 0 /*NULL*/) || (((*(*e).typ).kind == 2) && ((*e).iVal > 0))) || (((*(*e).typ).kind == 3) && ((*e).rVal > 0.000000)));
  return ((((e == 0 /*NULL*/) || (((*(*e).typ).kind == 2) && ((*e).iVal > 0))) || (((*(*e).typ).kind == 3) && ((*e).rVal > 0.000000))));
}
void CCodegen_GenStatements(const Lex_Lexer  *l, AST_Stmt s);
void CCodegen_GenStatements(const Lex_Lexer  *l, AST_Stmt s) {
  AST_Expr e;
  INTEGER fromVal;
  INTEGER toVal;
  BOOLEAN useChar;
  while (s != 0 /*NULL*/) {
    assert(((*s).kind >= 1));
    assert(((*s).kind <= 13));
    if (!(((1 << (*s).kind) & 8576))) {
      CCodegen_GenI();
    }
switch ((*s).kind) {
      case 1:
      case 2:
        CCodegen_GenExpr(&((*l)), (*s).cond);
        CCodegen_GenStr(";", 2);
        break;

      case 12:
        CCodegen_GenStr("return ", 8);
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
        if ((*s).elsifs == 0 /*NULL*/) {
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
        if ((*(*(*s).cond).next).next == 0 /*NULL*/) {
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
        assert(((*s).next == 0 /*NULL*/));
        assert(((*(*s).cond).kind == 3));
        e = (*s).cond;
        while (e != 0 /*NULL*/) {
          assert((((*e).op == 60) || ((*e).op == 69)));
          if ((*e).op == 60) {
            assert(AST_IsConst((*e).rhs));
            useChar = ((*(*(*e).rhs).typ).kind == 5);
            fromVal = (*(*e).rhs).iVal;
            toVal = fromVal;
          } else {
            assert(AST_IsConst((*(*e).lhs).rhs));
            assert(AST_IsConst((*(*e).rhs).rhs));
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
        assert(((*s).next == 0 /*NULL*/));
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
        assert(((*s).elsifs == 0 /*NULL*/));
        assert(((*s).next == 0 /*NULL*/));
        CCodegen_GenStr("} else {", 9);
        CCodegen_GenLn();
        CCodegen_indent++;
        CCodegen_GenStatements(&((*l)), (*s).body);
        CCodegen_indent--;
        break;
    }
    if (!(((1 << (*s).kind) & 8576))) {
      CCodegen_GenLn();
    }
    s = (*s).next;
  }
}
void CCodegen_GenProc(Lex_Lexer  *l, AST_Decl d);
void CCodegen_GenProc(Lex_Lexer  *l, AST_Decl d) {
  AST_Decl p;
  AST_QName q;
  q.moduleName = 0;
  CCodegen_GenType(&((*l)), (*d).typ, &((*d).qname), 0, 1);
  CCodegen_GenStr(";", 2);
  CCodegen_GenLn();
  if ((*d).procVars != 0 /*NULL*/) {
    p = (*d).procVars;
    while ((*p).kind != 1001) {
      if ((*p).kind == 5) {
        CCodegen_RenameInnerProc(&((*l)), p);
        CCodegen_GenProc(&((*l)), p);
      } else if ((*p).kind == 3) {
        CCodegen_GenTypedef(&((*l)), p);
        CCodegen_GenLn();

      }
      p = (*p).next;
    }
  }
  CCodegen_GenType(&((*l)), (*d).typ, &((*d).qname), 0, 1);
  CCodegen_GenStr(" {", 3);
  CCodegen_GenLn();
  CCodegen_indent++;
  if ((*d).procVars != 0 /*NULL*/) {
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
      } else if ((AST_NeedsTypeInfo((*p).typ) && ((*(*p).typ).kind == 11)) && (((*p).kind == 7) || ((*p).kind == 6))) {
        CCodegen_GenI();
        CCodegen_GenStr("(void)", 7);
        CCodegen_GenQName(&((*l)), &(q));
        CCodegen_GenStr("__typeid;", 10);
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
  if ((*d).expr != 0 /*NULL*/) {
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
void CCodegen_Generate(Lex_Lexer  *l, AST_Decl d);
void CCodegen_Generate(Lex_Lexer  *l, AST_Decl d) {
  if ((*d).nesting == 0) {
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
void CCodegen_GenStartMain(void);
void CCodegen_GenStartMain(void) {
  CCodegen_GenStr("int main(int argc, const char **argv) {", 40);
  CCodegen_GenLn();
  CCodegen_indent++;
  CCodegen_GenI();
  CCodegen_GenStr("InitArgs(argc, argv);", 22);
  CCodegen_GenLn();
}
void CCodegen_GenCall(const Lex_Lexer  *l, const AST_QName  *name);
void CCodegen_GenCall(const Lex_Lexer  *l, const AST_QName  *name) {
  CCodegen_GenI();
  CCodegen_GenQName(&((*l)), &((*name)));
  CCodegen_GenStr("();", 4);
  CCodegen_GenLn();
}
void CCodegen_GenEndMain(void);
void CCodegen_GenEndMain(void) {
  CCodegen_indent--;
  CCodegen_GenI();
  CCodegen_GenStr("}", 2);
  CCodegen_GenLn();
}
void Compiler_CompileFile(void);
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
    } else {
      gotFile = 1;


    }
    i++;
  } while (!gotFile);

  Parse_InitFromFile(fileName, 256);
  Parse_ParseModule();
  l = Parse_l;
  Decls_VisitDecl(Parse_lastModuleDecls);
  p = Decls_reachableDecls;
  CCodegen_GenTypeinfos();
  while (p != 0 /*NULL*/) {
    if (((*(*p).d).kind == 3) && ((*(*(*p).d).typ).kind == 8)) {
      CCodegen_Generate(&(l), (*p).d);
    }
    p = (*p).next;
  }
  p = Decls_reachableDecls;
  while (p != 0 /*NULL*/) {
    if (((*(*p).d).kind == 3) && ((*(*(*p).d).typ).kind != 8)) {
      CCodegen_Generate(&(l), (*p).d);
    }
    p = (*p).next;
  }
  p = Decls_reachableDecls;
  while (p != 0 /*NULL*/) {
    if ((*(*p).d).kind == 4) {
      CCodegen_Generate(&(l), (*p).d);
    }
    p = (*p).next;
  }
  p = Decls_reachableDecls;
  while (p != 0 /*NULL*/) {
    if (((*(*p).d).kind == 5) && !((*(*p).d).isNative)) {
      CCodegen_Generate(&(l), (*p).d);
    }
    p = (*p).next;
  }
  CCodegen_GenStartMain();
  p = Decls_reachableDecls;
  while (p != 0 /*NULL*/) {
    if ((*(*p).d).qname.name == Decls_modInitName) {
      CCodegen_GenCall(&(l), &((*(*p).d).qname));
    }
    p = (*p).next;
  }
  CCodegen_GenEndMain();
}
void Compiler__module_init_(void);
void Compiler__module_init_(void) {
  if (Args_Count() == 1) {
    Compiler_RunTests();
  } else {
    Compiler_CompileFile();

  }
}
int main(int argc, const char **argv) {
  InitArgs(argc, argv);
  Args__module_init_();
  Out__module_init_();
  Lex__module_init_();
  AST__module_init_();
  CCodegen__module_init_();
  Decls__module_init_();
  Parse__module_init_();
  Compiler__module_init_();
}
