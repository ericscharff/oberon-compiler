typedef struct Decl Decl;
typedef struct Expr expr;
typedef struct Statement Statement;

#define MODULE_INIT string_intern("<module_init>")

typedef enum {
  DECL_UNKNOWN,
  DECL_INCOMPLETE,
  DECL_IMPORT,
  DECL_CONST,
  DECL_TYPE,
  DECL_VAR,
  DECL_PARAM,
  DECL_VARPARAM,
  DECL_PROC,
} DeclKind;

const char *decl_kind_names[] = {
    [DECL_UNKNOWN] = "<unknown>", [DECL_INCOMPLETE] = "<incomplete>",
    [DECL_IMPORT] = "IMPORT",     [DECL_CONST] = "CONST",
    [DECL_TYPE] = "TYPE",         [DECL_VAR] = "VAR",
    [DECL_PARAM] = "PARAM",       [DECL_VARPARAM] = "VARPARAM",
    [DECL_PROC] = "PROC",
};

typedef enum {
  DECLSTATE_UNRESOLVED,
  DECLSTATE_RESOLVING,
  DECLSTATE_RESOLVED,
} DeclState;

const char *decl_state_names[] = {
    [DECLSTATE_UNRESOLVED] = "UNRESOLVED",
    [DECLSTATE_RESOLVING] = "RESOLVING",
    [DECLSTATE_RESOLVED] = "RESOLVED",
};

typedef struct Decl {
  DeclKind kind;
  const char *name;
  const char *package_name;
  Loc loc;
  union {
    Decl *imported_decls;  // Only for DECL_IMPORT
    Type *type;            // for everything else
  };
  bool is_exported;
  union {
    struct {
      Expr *expr;  // Only for DECL_CONST
    } const_val;
    struct {
      Decl *decls;      // buf
      Statement *body;  // buf
      Expr *ret_val;
    } proc_decl;
  };
  DeclState state;  // Populated by resolver
} Decl;

typedef enum {
  VAL_UNKNOWN,
  VAL_INTEGER,
  VAL_REAL,
  VAL_SET,
  VAL_BOOLEAN,
  VAL_STRING,
  VAL_NIL,
} ValKind;

typedef struct Val {
  ValKind kind;
  union {
    int iVal;
    float rVal;
    uint32_t setVal;
    bool bVal;
    const char *sVal;
  };
} Val;

typedef enum {
  EXPR_UNKNOWN,
  EXPR_UNARY,
  EXPR_BINARY,
  EXPR_IDENTREF,
  EXPR_PROCCALL,
  EXPR_FIELDREF,
  EXPR_POINTERDEREF,
  EXPR_ARRAYREF,
  EXPR_TYPEGUARD,
  EXPR_INTEGER,
  EXPR_REAL,
  EXPR_STRING,
  EXPR_NIL,
  EXPR_TRUE,
  EXPR_FALSE,
  EXPR_EMPTYSET,
} ExprKind;

const char *expr_kind_names[] = {
    [EXPR_UNKNOWN] = "UNKNOWN",
    [EXPR_UNARY] = "UNARY",
    [EXPR_BINARY] = "BINARY",
    [EXPR_IDENTREF] = "IDENTREF",
    [EXPR_PROCCALL] = "PROCCALL",
    [EXPR_FIELDREF] = "FIELDREF",
    [EXPR_POINTERDEREF] = "POINTERDEREF",
    [EXPR_ARRAYREF] = "ARRAYREF",
    [EXPR_TYPEGUARD] = "TYPEGUARD",
    [EXPR_INTEGER] = "INTEGER",
    [EXPR_REAL] = "REAL",
    [EXPR_STRING] = "STRING",
    [EXPR_NIL] = "NIL",
    [EXPR_TRUE] = "TRUE",
    [EXPR_FALSE] = "FALSE",
    [EXPR_EMPTYSET] = "EMPTYSET",
};

typedef struct Expr {
  ExprKind kind;
  Loc loc;
  union {
    struct {
      TokenKind op;
      Expr *expr;
    } unary;
    struct {
      TokenKind op;
      Expr *lhs;
      Expr *rhs;
    } binary;
    struct {
      const char *name;
      const char *package_name;
    } identref;
    struct {
      Expr *proc;
      Expr **args;  // buf
    } proccall;
    struct {
      const char *field_name;
      Expr *expr;
    } fieldref;
    struct {
      Expr *expr;
    } pointerderef;
    struct {
      Expr *array_index;
      Expr *expr;
    } arrayref;
    struct {
      Decl *type_defn;
      Expr *expr;
    } typeguard;
    struct {
      int iVal;
    } integer;
    struct {
      float rVal;
    } real;
    struct {
      const char *sVal;
    } string;
  };
  bool is_const;       // Populated by resolver
  Type *type;          // Populated by resolver
  Val val;             // Populated by resolver
  bool is_assignable;  // Populated by resolver
  bool is_var_param;   // Populated by resolver
} Expr;

void dbg_print_expr(Expr *e) {
  assert(e);
  printf("(%s ", expr_kind_names[e->kind]);
  switch (e->kind) {
    case EXPR_UNKNOWN:
      break;
    case EXPR_UNARY:
      printf("op: %s ", op_name(e->unary.op));
      dbg_print_expr(e->unary.expr);
      break;
    case EXPR_BINARY:
      printf("op: %s ", op_name(e->binary.op));
      dbg_print_expr(e->binary.lhs);
      printf(" ");
      dbg_print_expr(e->binary.rhs);
      break;
    case EXPR_IDENTREF:
      printf("var: %s.%s ", e->identref.package_name, e->identref.name);
      break;
    case EXPR_PROCCALL:
      dbg_print_expr(e->proccall.proc);
      printf(" ");
      for (size_t i = 0; i < buf_len(e->proccall.args); i++) {
        dbg_print_expr(e->proccall.args[i]);
        printf(" ");
      }
      break;
    case EXPR_FIELDREF:
      printf("field: %s ", e->fieldref.field_name);
      dbg_print_expr(e->fieldref.expr);
      break;
    case EXPR_POINTERDEREF:
      dbg_print_expr(e->pointerderef.expr);
      break;
    case EXPR_ARRAYREF:
      printf("array: ");
      dbg_print_expr(e->arrayref.expr);
      printf("index: ");
      dbg_print_expr(e->arrayref.array_index);
      break;
    case EXPR_TYPEGUARD:
      printf("type: %s.%s ", e->typeguard.type_defn->package_name,
             e->typeguard.type_defn->name);
      dbg_print_expr(e->typeguard.expr);
      break;
    case EXPR_INTEGER:
      printf("%d", e->integer.iVal);
      break;
    case EXPR_REAL:
      printf("%f", e->real.rVal);
      break;
    case EXPR_STRING:
      printf("%s", e->string.sVal);
      break;
    case EXPR_NIL:
      break;
    case EXPR_TRUE:
      break;
    case EXPR_FALSE:
      break;
    case EXPR_EMPTYSET:
      break;
    default:
      assert(0);
      break;
  }
  printf(")");
}

void dbg_print_val(Val val) {
  switch (val.kind) {
    case VAL_INTEGER:
      printf("%d", val.iVal);
      break;
    case VAL_REAL:
      printf("%f", val.rVal);
      break;
    case VAL_SET: {
      uint32_t bit = 1 << 31;
      int bitCount = 0;
      while (bit) {
        printf("%c", val.setVal & bit ? '1' : '0');
        bitCount++;
        if (bitCount == 4) {
          bitCount = 0;
          printf(" ");
        }
        bit >>= 1;
      }
      break;
    }
    case VAL_BOOLEAN:
      printf("%s", val.bVal ? "TRUE" : "FALSE");
      break;
    case VAL_STRING:
      printf("%s", val.sVal);
      break;
    case VAL_NIL:
      printf("NIL");
      break;
    default:
      assert(0);
      break;
  }
}

typedef struct ElseIf {
  Expr *cond;
  Statement *body;  // buf
} ElseIf;

typedef struct Case {
  Expr *cond;
  Statement *body;  // buf
} Case;

typedef enum {
  STMT_UNKNOWN,
  STMT_IF,
  STMT_CASE,
  STMT_WHILE,
  STMT_REPEAT,
  STMT_FOR,
  STMT_ASSIGNMENT,
  STMT_PROCCALL,
  STMT_EMPTY,
} StatementKind;

const char *statement_kind_names[] = {
    [STMT_UNKNOWN] = "STMT_UNKNOWN",
    [STMT_IF] = "STMT_IF",
    [STMT_CASE] = "STMT_CASE",
    [STMT_WHILE] = "STMT_WHILE",
    [STMT_REPEAT] = "STMT_REPEAT",
    [STMT_FOR] = "STMT_FOR",
    [STMT_ASSIGNMENT] = "STMT_ASSIGNMENT",
    [STMT_PROCCALL] = "STMT_PROCCALL",
    [STMT_EMPTY] = "STMT_EMPTY",
};

typedef struct Statement {
  StatementKind kind;
  Loc loc;
  union {
    struct {
      Expr *cond;
      Statement *then_clause;  // buf
      ElseIf *elseifs;         // buf
      Statement *else_clause;  // buf
    } if_stmt;
    struct {
      Expr *cond;
      Case *case_cases;  // buf
    } case_stmt;
    struct {
      Expr *cond;
      Statement *body;  // buf
      ElseIf *elseifs;  // buf
    } while_stmt;
    struct {
      Expr *cond;
      Statement *body;  // buf
    } repeat_stmt;
    struct {
      const char *ident;
      Expr *start;
      Expr *end;
      Expr *increment;
      Statement *body;  // buf
    } for_stmt;
    struct {
      Expr *lvalue;
      Expr *rvalue;
    } assignment_stmt;
    struct {
      Expr *proc;
      Expr **args;  // buf
    } proc_call_stmt;
  };
} Statement;

typedef struct Module {
  const char *name;
  Decl *decls;  // buf
  Decl *initializer;
} Module;

typedef struct Scope Scope;
typedef struct Scope {
  Decl *decls;  // buf
  Scope *parent;
} Scope;

// Typically, the current scope is stack allocated. E.g, when a procedure is
// defined, the function parsing the procedure allocates a new scope on the
// stack, and when it leaves, sets the global scope back. Thus, It is not safe
// to save Decl objects, but Types are persisted.
Scope *current_scope = NULL;
const char *current_package_name = NULL;

void enter_scope(Scope *scope, const char *packageName) {
  assert(scope);
  assert(packageName);
  assert(scope->decls == NULL);
  scope->parent = current_scope;
  current_scope = scope;
  current_package_name = packageName;
}

void exit_scope(const char *newPackageName) {
  current_scope = current_scope->parent;
  current_package_name = newPackageName;
}

Decl *lookup_decl(const char *name) {
  for (Scope *s = current_scope; s != NULL; s = s->parent) {
    for (size_t i = 0; i < buf_len(s->decls); i++) {
      if (s->decls[i].name == name) {
        return &s->decls[i];
      }
    }
  }
  return NULL;
}

Decl *lookup_module_import(const char *moduleName, const char *name) {
  Decl *m = lookup_decl(moduleName);
  if (m) {
    if (m->kind == DECL_IMPORT) {
      for (size_t i = 0; i < buf_len(m->imported_decls); i++) {
        if (m->imported_decls[i].name == name) {
          if (m->imported_decls[i].is_exported) {
            return &m->imported_decls[i];
          } else {
            error("%s.%s is not exported", moduleName, name);
          }
        }
      }
      error("%s.%s is undefined", moduleName, name);
    } else {
      error("%s is not an imported module", moduleName);
    }
  } else {
    error("%s undefined", moduleName);
  }
  printf("Looking up %s.%s\n", moduleName, name);
  return NULL;
}

Decl *internal_new_decl(const char *name, Loc loc) {
  assert(name);
  assert(current_scope);
  for (size_t i = 0; i < buf_len(current_scope->decls); i++) {
    if (current_scope->decls[i].name == name) {
      if (current_scope->decls[i].kind == DECL_INCOMPLETE) {
        return &current_scope->decls[i];
      } else {
        error("%s redefined", name);
      }
    }
  }
  Decl d;
  d.name = name;
  d.package_name = current_package_name;
  d.loc = loc;
  d.kind = DECL_UNKNOWN;
  d.type = NULL;
  d.state = DECLSTATE_UNRESOLVED;
  size_t index = buf_len(current_scope->decls);
  buf_push(current_scope->decls, d);
  assert(index + 1 == buf_len(current_scope->decls));
  return current_scope->decls + index;
}

void new_decl_import(const char *name, Loc loc, Decl *decls) {
  Decl *d = internal_new_decl(name, loc);
  d->kind = DECL_IMPORT;
  d->imported_decls = decls;
  d->is_exported = false;
}

Decl *new_decl_incomplete(const char *name, Loc loc) {
  Decl *d = internal_new_decl(name, loc);
  d->kind = DECL_INCOMPLETE;
  d->type = new_type_incomplete();
  d->is_exported = false;
  return d;
}

void new_decl_const(const char *name, Loc loc, Expr *expr, bool is_exported) {
  Decl *d = internal_new_decl(name, loc);
  d->kind = DECL_CONST;
  d->const_val.expr = expr;
  // NULL const type will be fixed by resolver.
  d->type = NULL;
  d->is_exported = is_exported;
}

void new_decl_type(const char *name, Loc loc, Type *type, bool is_exported) {
  if (type->name == NULL && type->package_name == NULL) {
    type->name = name;
    type->package_name = current_package_name;
  }
  Decl *d = internal_new_decl(name, loc);
  if (d->kind == DECL_INCOMPLETE) {
    assert(d->type);
    assert(d->type->kind == TYPE_INCOMPLETE);
    *d->type = *type;
  } else {
    d->type = type;
  }
  d->kind = DECL_TYPE;
  d->is_exported = is_exported;
}

void new_decl_var(const char *name, Loc loc, Type *type, bool is_exported) {
  Decl *d = internal_new_decl(name, loc);
  d->kind = DECL_VAR;
  d->type = type;
  d->is_exported = is_exported;
}

void new_decl_param(const char *name, Loc loc, Type *type) {
  Decl *d = internal_new_decl(name, loc);
  d->kind = DECL_PARAM;
  d->type = type;
  d->is_exported = false;
}

void new_decl_varparam(const char *name, Loc loc, Type *type) {
  Decl *d = internal_new_decl(name, loc);
  d->kind = DECL_VARPARAM;
  d->type = type;
  d->is_exported = false;
}

Decl *new_decl_proc(const char *name, Loc loc, Type *type, bool is_exported) {
  Decl *d = internal_new_decl(name, loc);
  d->kind = DECL_PROC;
  d->type = type;
  d->proc_decl.decls = NULL;
  d->proc_decl.body = NULL;
  d->is_exported = is_exported;
  return d;
}

Expr *new_expr(ExprKind kind, Loc loc) {
  Expr *e = xmalloc(sizeof(Expr));
  e->kind = kind;
  e->loc = loc;
  e->is_const = false;
  e->type = NULL;
  e->is_assignable = false;
  e->is_var_param = false;
  return e;
}

Expr *new_expr_unary(TokenKind op, Expr *base, Loc loc) {
  Expr *e = new_expr(EXPR_UNARY, loc);
  e->unary.op = op;
  e->unary.expr = base;
  return e;
}

Expr *new_expr_binary(TokenKind op, Expr *lhs, Expr *rhs, Loc loc) {
  Expr *e = new_expr(EXPR_BINARY, loc);
  e->binary.op = op;
  e->binary.lhs = lhs;
  e->binary.rhs = rhs;
  return e;
}

Expr *new_expr_identref(const char *name, const char *packageName, Loc loc) {
  Expr *e = new_expr(EXPR_IDENTREF, loc);
  e->identref.name = name;
  e->identref.package_name = packageName;
  return e;
}

Expr *new_expr_proccall(Expr *proc, Expr **args, Loc loc) {
  Expr *e = new_expr(EXPR_PROCCALL, loc);
  e->proccall.proc = proc;
  e->proccall.args = args;
  return e;
}

Expr *new_expr_fieldref(const char *fieldName, Expr *base, Loc loc) {
  Expr *e = new_expr(EXPR_FIELDREF, loc);
  e->fieldref.field_name = fieldName;
  e->fieldref.expr = base;
  return e;
}

Expr *new_expr_pointerderef(Expr *base, Loc loc) {
  Expr *e = new_expr(EXPR_POINTERDEREF, loc);
  e->pointerderef.expr = base;
  return e;
}

Expr *new_expr_arrayref(Expr *arrayIndex, Expr *arrayRef, Loc loc) {
  Expr *e = new_expr(EXPR_ARRAYREF, loc);
  e->arrayref.array_index = arrayIndex;
  e->arrayref.expr = arrayRef;
  return e;
}

Expr *new_expr_typeguard(Decl *type_defn, Expr *base, Loc loc) {
  Expr *e = new_expr(EXPR_TYPEGUARD, loc);
  e->typeguard.type_defn = type_defn;
  e->typeguard.expr = base;
  return e;
}

Expr *new_expr_integer(int iVal, Loc loc) {
  Expr *e = new_expr(EXPR_INTEGER, loc);
  e->integer.iVal = iVal;
  return e;
}

Expr *new_expr_real(float rVal, Loc loc) {
  Expr *e = new_expr(EXPR_REAL, loc);
  e->real.rVal = rVal;
  return e;
}

Expr *new_expr_string(const char *s, Loc loc) {
  Expr *e = new_expr(EXPR_STRING, loc);
  e->string.sVal = s;
  return e;
}

Expr *new_expr_nil(Loc loc) { return new_expr(EXPR_NIL, loc); }

Expr *new_expr_true(Loc loc) { return new_expr(EXPR_TRUE, loc); }

Expr *new_expr_false(Loc loc) { return new_expr(EXPR_FALSE, loc); }

Expr *new_expr_emptyset(Loc loc) { return new_expr(EXPR_EMPTYSET, loc); }

Statement new_stmt_empty(void) {
  Statement s;
  s.kind = STMT_EMPTY;
  return s;
}

Statement new_stmt_if(Loc loc, Expr *cond, Statement *then_clause,
                      ElseIf *elseifs, Statement *else_clause) {
  Statement s;
  s.kind = STMT_IF;
  s.loc = loc;
  s.if_stmt.cond = cond;
  s.if_stmt.then_clause = then_clause;
  s.if_stmt.elseifs = elseifs;
  s.if_stmt.else_clause = else_clause;
  return s;
}

Statement new_stmt_case(Loc loc, Expr *cond, Case *case_cases) {
  Statement s;
  s.kind = STMT_CASE;
  s.loc = loc;
  s.case_stmt.cond = cond;
  s.case_stmt.case_cases = case_cases;
  return s;
}

Statement new_stmt_while(Loc loc, Expr *cond, Statement *body,
                         ElseIf *elseifs) {
  Statement s;
  s.kind = STMT_WHILE;
  s.loc = loc;
  s.while_stmt.cond = cond;
  s.while_stmt.body = body;
  s.while_stmt.elseifs = elseifs;
  return s;
}

Statement new_stmt_repeat(Loc loc, Expr *cond, Statement *body) {
  Statement s;
  s.kind = STMT_REPEAT;
  s.loc = loc;
  s.repeat_stmt.cond = cond;
  s.repeat_stmt.body = body;
  return s;
}

Statement new_stmt_for(Loc loc, const char *ident, Expr *start, Expr *end,
                       Expr *increment, Statement *body) {
  Statement s;
  s.kind = STMT_FOR;
  s.loc = loc;
  s.for_stmt.ident = ident;
  s.for_stmt.start = start;
  s.for_stmt.end = end;
  s.for_stmt.increment = increment;
  s.for_stmt.body = body;
  return s;
}

Statement new_stmt_assignment(Loc loc, Expr *lvalue, Expr *rvalue) {
  Statement s;
  s.kind = STMT_ASSIGNMENT;
  s.loc = loc;
  s.assignment_stmt.lvalue = lvalue;
  s.assignment_stmt.rvalue = rvalue;
  return s;
}

Statement new_stmt_proccall(Loc loc, Expr *proc, Expr **args) {
  Statement s;
  s.kind = STMT_PROCCALL;
  s.loc = loc;
  s.proc_call_stmt.proc = proc;
  s.proc_call_stmt.args = args;
  return s;
}

size_t stmt_indent = 0;
void indenty(void) {
  for (size_t indent = 0; indent < stmt_indent; indent++) {
    printf("  ");
  }
}

void dbg_dump_stmts(Statement *s) {
  stmt_indent++;
  for (size_t i = 0; i < buf_len(s); i++) {
    indenty();
    printf("%s: ", statement_kind_names[s[i].kind]);
    switch (s[i].kind) {
      case STMT_IF:
        dbg_print_expr(s[i].if_stmt.cond);
        printf("\n");
        dbg_dump_stmts(s[i].if_stmt.then_clause);
        for (size_t e = 0; e < buf_len(s[i].if_stmt.elseifs); e++) {
          printf("\n");
          indenty();
          printf("ELSEIF ");
          dbg_print_expr(s[i].if_stmt.elseifs[e].cond);
          printf("\n");
          dbg_dump_stmts(s[i].if_stmt.elseifs[e].body);
        }
        printf("\n");
        indenty();
        printf("ELSE\n");
        dbg_dump_stmts(s[i].if_stmt.else_clause);
        break;
      case STMT_WHILE:
        dbg_print_expr(s[i].while_stmt.cond);
        printf("\n");
        dbg_dump_stmts(s[i].while_stmt.body);
        break;
      case STMT_REPEAT:
        dbg_print_expr(s[i].repeat_stmt.cond);
        printf("\n");
        dbg_dump_stmts(s[i].repeat_stmt.body);
        break;
      case STMT_ASSIGNMENT:
        dbg_print_expr(s[i].assignment_stmt.lvalue);
        dbg_print_expr(s[i].assignment_stmt.rvalue);
        break;
      case STMT_PROCCALL:
        dbg_print_expr(s[i].proc_call_stmt.proc);
        printf("(");
        for (size_t arg = 0; arg < buf_len(s[i].proc_call_stmt.args); arg++) {
          dbg_print_expr(s[i].proc_call_stmt.args[arg]);
          printf(", ");
        }
        printf(")");
        break;
      case STMT_EMPTY:
        break;
      default:
        assert(0);
        break;
    }
    printf("\n");
  }
  stmt_indent--;
}

Module *new_module(const char *name, Decl *decls, Statement *body) {
  assert(current_scope->decls == decls);
  Module *m = xmalloc(sizeof(Module));
  if (body) {
    Decl *d = new_decl_proc(MODULE_INIT, body->loc,
                            new_type_procedure(NULL, NULL), false);
    d->package_name = name;
    d->proc_decl.ret_val = NULL;
    d->proc_decl.body = body;
    m->initializer = d;
  } else {
    m->initializer = NULL;
  }
  m->name = name;
  m->decls = current_scope->decls;
  return m;
}

void init_global_types() {
  Loc loc = {"<global>", 0};
  current_package_name = string_intern("");
  assert(booleanType.kind == TYPE_BOOLEAN);
  new_decl_type(string_intern("BOOLEAN"), loc, &booleanType, true);
  new_decl_type(string_intern("BYTE"), loc, &byteType, true);
  new_decl_type(string_intern("CHAR"), loc, &charType, true);
  new_decl_type(string_intern("INTEGER"), loc, &integerType, true);
  new_decl_type(string_intern("REAL"), loc, &realType, true);
  new_decl_type(string_intern("SET"), loc, &setType, true);
  nilType.name = string_intern("<NIL>");
  stringType.name = string_intern("<STRING>");
}

void ast_test(void) {
  Scope outer;
  Scope inner;
  outer.decls = NULL;
  inner.decls = NULL;
  Loc loc = {"<TEST>", 10};
  const char *outerScopeName = string_intern("<outer_scope>");
  const char *innerScopeName = string_intern("<inner_scope>");

  enter_scope(&outer, outerScopeName);
  assert(current_scope == &outer);
  new_decl_var(string_intern("outer1"), loc, &integerType, false);
  new_decl_var(string_intern("outer2"), loc, &integerType, true);
  assert(buf_len(current_scope->decls) == 2);
  Decl *o1 = lookup_decl(string_intern("outer1"));
  assert(o1->kind == DECL_VAR);
  assert(o1->name == string_intern("outer1"));
  assert(is_integer_type(o1->type));
  assert(o1->is_exported == false);
  Decl *o2 = lookup_decl(string_intern("outer2"));
  assert(o2->kind == DECL_VAR);
  assert(o2->name == string_intern("outer2"));
  assert(is_integer_type(o2->type));
  assert(o2->is_exported == true);

  enter_scope(&inner, innerScopeName);
  assert(current_scope == &inner);
  assert(current_scope->parent == &outer);
  new_decl_var(string_intern("inner1"), loc, &realType, true);
  Decl *i1 = lookup_decl(string_intern("inner1"));
  assert(i1->kind == DECL_VAR);
  assert(i1->name == string_intern("inner1"));
  assert(i1->type == &realType);
  assert(i1->is_exported == true);
  Decl *oRef = lookup_decl(string_intern("outer1"));
  assert(oRef == o1);
  exit_scope(outerScopeName);
  assert(current_scope == &outer);
  exit_scope(NULL);
  assert(current_scope == NULL);
}
