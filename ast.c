typedef struct Decl Decl;
typedef struct Expr expr;

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
    [DECL_VARPARAM] = "VARPARAM", [DECL_PROC] = "PROC",
};

typedef struct Qualident {
  const char *package_name; // can be null
  const char *name;
} Qualident;

typedef struct Decl {
  DeclKind kind;
  const char *name;
  union {
    Decl *imported_decls;  // Only for DECL_IMPORT
    Type *type;                   // for everything else
  };
  bool is_exported;
  Qualident qualident;
  Expr *expr; // Only for DECL_CONST
} Decl;

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
  [EXPR_UNKNOWN] = "EXPR_UNKNOWN",
  [EXPR_UNARY] = "EXPR_UNARY",
  [EXPR_BINARY] = "EXPR_BINARY",
  [EXPR_IDENTREF] = "EXPR_IDENTREF",
  [EXPR_PROCCALL] = "EXPR_PROCCALL",
  [EXPR_FIELDREF] = "EXPR_FIELDREF",
  [EXPR_POINTERDEREF] = "EXPR_POINTERDEREF",
  [EXPR_ARRAYREF] = "EXPR_ARRAYREF",
  [EXPR_TYPEGUARD] = "EXPR_TYPEGUARD",
  [EXPR_INTEGER] = "EXPR_INTEGER",
  [EXPR_REAL] = "EXPR_REAL",
  [EXPR_STRING] = "EXPR_STRING",
  [EXPR_NIL] = "EXPR_NIL",
  [EXPR_TRUE] = "EXPR_TRUE",
  [EXPR_FALSE] = "EXPR_FALSE",
  [EXPR_EMPTYSET] = "EXPR_EMPTYSET",
};


typedef struct Expr {
  ExprKind kind;
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
      Qualident qualident;
    } identref;
    struct {
      Expr *proc;
      Expr **args; // buf
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
      Qualident type_name;
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
} Expr;

const char *dbg_null_to_empty(const char *s) {
  return s ? s : "";
}

void dbg_print_expr(Expr *e) {
  assert(e);
  printf("(%s ", expr_kind_names[e->kind]);
  switch (e->kind) {
  case EXPR_UNKNOWN:
    break;
  case EXPR_UNARY:
    printf("op: %s ", token_kind_names[e->unary.op]);
    dbg_print_expr(e->unary.expr);
    break;
  case EXPR_BINARY:
    printf("op: %s ", token_kind_names[e->binary.op]);
    dbg_print_expr(e->binary.lhs);
    printf(" ");
    dbg_print_expr(e->binary.rhs);
    break;
  case EXPR_IDENTREF:
    printf("var: %s.%s ", dbg_null_to_empty(e->identref.qualident.package_name), e->identref.qualident.name);
    break;
  case EXPR_PROCCALL:
    dbg_print_expr(e->proccall.proc);
    printf(" ");
    for (size_t i=0; i < buf_len(e->proccall.args); i++) {
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
    printf("type: %s.%s ", dbg_null_to_empty(e->typeguard.type_name.package_name), e->typeguard.type_name.name);
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

typedef struct Module {
  const char *name;
  Decl *decls;  // buf
} Module;

#define SCOPE_SIZE 512
typedef struct Scope Scope;
typedef struct Scope {
  Decl decls[SCOPE_SIZE];
  // Number of valid decls
  size_t size;
  Scope *parent;
} Scope;

// Typically, the current scope is stack allocated. E.g, when a procedure is
// defined, the function parsing the procedure allocates a new scope on the
// stack, and when it leaves, sets the global scope back. Thus, It is not safe
// to save Decl objects, but Types are persisted.
Scope *current_scope = NULL;

void enter_scope(Scope *scope) {
  scope->parent = current_scope;
  current_scope = scope;
  current_scope->size = 0;
}

void exit_scope(void) { current_scope = current_scope->parent; }

Decl *lookup_decl(const char *name) {
  for (Scope *s = current_scope; s != NULL; s = s->parent) {
    for (size_t i = 0; i < s->size; i++) {
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

Decl *internal_new_decl(const char *name) {
  assert(name);
  assert(current_scope);
  assert(current_scope->size < SCOPE_SIZE);
  for (size_t i = 0; i < current_scope->size; i++) {
    if (current_scope->decls[i].name == name) {
      if (current_scope->decls[i].kind == DECL_INCOMPLETE) {
        return &current_scope->decls[i];
      } else {
        error("%s redefined", name);
      }
    }
  }
  Decl *d = &current_scope->decls[current_scope->size++];
  d->name = name;
  return d;
}

void new_import_decl(const char *name, Decl *decls) {
  Decl *d = internal_new_decl(name);
  d->kind = DECL_IMPORT;
  d->imported_decls = decls;
  d->is_exported = false;
}

Decl *new_incomplete_decl(const char *name) {
  Decl *d = internal_new_decl(name);
  d->kind = DECL_INCOMPLETE;
  d->type = new_incomplete_type();
  d->is_exported = false;
  return d;
}

void new_const_decl(const char *name, Expr *expr, bool is_exported) {
  Decl *d = internal_new_decl(name);
  d->kind = DECL_CONST;
  d->expr = expr;
  // NULL const type will be fixed by resolver.
  d->type = NULL;
  d->is_exported = is_exported;
}

void new_type_decl(const char *name, Type *type, bool is_exported) {
  Decl *d = internal_new_decl(name);
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

void new_var_decl(const char *name, Type *type, bool is_exported) {
  Decl *d = internal_new_decl(name);
  d->kind = DECL_VAR;
  d->type = type;
  d->is_exported = is_exported;
}

void new_param_decl(const char *name, Type *type) {
  Decl *d = internal_new_decl(name);
  d->kind = DECL_PARAM;
  d->type = type;
  d->is_exported = false;
}

void new_varparam_decl(const char *name, Type *type) {
  Decl *d = internal_new_decl(name);
  d->kind = DECL_VARPARAM;
  d->type = type;
  d->is_exported = false;
}

void new_proc_decl(const char *name, Type *type, bool is_exported) {
  Decl *d = internal_new_decl(name);
  d->kind = DECL_PROC;
  d->type = type;
  d->is_exported = is_exported;
}

Expr *new_expr(ExprKind kind) {
  Expr *e = xmalloc(sizeof(Expr));
  e->kind = kind;
  return e;
}

Expr *new_expr_unary(TokenKind op, Expr *base) {
  Expr *e = new_expr(EXPR_UNARY);
  e->unary.op = op;
  e->unary.expr = base;
  return e;
}

Expr *new_expr_binary(TokenKind op, Expr *lhs, Expr *rhs) {
  Expr *e = new_expr(EXPR_BINARY);
  e->binary.op = op;
  e->binary.lhs = lhs;
  e->binary.rhs = rhs;
  return e;
}

Expr *new_expr_identref(Qualident qualident) {
  Expr *e = new_expr(EXPR_IDENTREF);
  e->identref.qualident = qualident;
  return e;
}

Expr *new_expr_proccall(Expr *proc, Expr **args) {
  Expr *e = new_expr(EXPR_PROCCALL);
  e->proccall.proc = proc;
  e->proccall.args = args;
  return e;
}

Expr *new_expr_fieldref(const char *fieldName, Expr *base) {
  Expr *e = new_expr(EXPR_FIELDREF);
  e->fieldref.field_name = fieldName;
  e->fieldref.expr = base;
  return e;
}

Expr *new_expr_pointerderef(Expr *base) {
  Expr *e = new_expr(EXPR_POINTERDEREF);
  e->pointerderef.expr = base;
  return e;
}

Expr *new_expr_arrayref(Expr *arrayIndex, Expr *arrayRef) {
  Expr *e = new_expr(EXPR_ARRAYREF);
  e->arrayref.array_index = arrayIndex;
  e->arrayref.expr = arrayRef;
  return e;
}

Expr *new_expr_typeguard(Qualident typeName, Expr *base) {
  Expr *e = new_expr(EXPR_TYPEGUARD);
  e->typeguard.type_name = typeName;
  e->typeguard.expr = base;
  return e;
}

Expr *new_expr_integer(int iVal) {
  Expr *e = new_expr(EXPR_INTEGER);
  e->integer.iVal = iVal;
  return e;
}

Expr *new_expr_real(float rVal) {
  Expr *e = new_expr(EXPR_REAL);
  e->real.rVal = rVal;
  return e;
}

Expr *new_expr_string(const char *s) {
  Expr *e = new_expr(EXPR_STRING);
  e->string.sVal = s;
  return e;
}

Expr *new_expr_nil(void) {
  return new_expr(EXPR_NIL);
}

Expr *new_expr_true(void) {
  return new_expr(EXPR_TRUE);
}

Expr *new_expr_false(void) {
  return new_expr(EXPR_FALSE);
}

Expr *new_expr_emptyset(void) {
  return new_expr(EXPR_EMPTYSET);
}

Module *new_module(const char *name, Scope *s) {
  Module *m = xmalloc(sizeof(Module));
  m->name = name;
  m->decls = NULL;
  for (size_t i = 0; i < s->size; i++) {
    buf_push(m->decls, s->decls[i]);
  }
  return m;
}

void init_global_types() {
  assert(booleanType.kind == TYPE_BOOLEAN);
  new_type_decl(string_intern("BOOLEAN"), &booleanType, true);
  new_type_decl(string_intern("BYTE"), &byteType, true);
  new_type_decl(string_intern("CHAR"), &charType, true);
  new_type_decl(string_intern("INTEGER"), &integerType, true);
  new_type_decl(string_intern("REAL"), &realType, true);
  new_type_decl(string_intern("SET"), &setType, true);
}

void ast_test(void) {
  Scope outer;
  Scope inner;

  enter_scope(&outer);
  assert(current_scope == &outer);
  new_var_decl(string_intern("outer1"), &integerType, false);
  new_var_decl(string_intern("outer2"), &integerType, true);
  assert(current_scope->size == 2);
  Decl *o1 = lookup_decl(string_intern("outer1"));
  assert(o1->kind == DECL_VAR);
  assert(o1->name == string_intern("outer1"));
  assert(o1->type == &integerType);
  assert(o1->is_exported == false);
  Decl *o2 = lookup_decl(string_intern("outer2"));
  assert(o2->kind == DECL_VAR);
  assert(o2->name == string_intern("outer2"));
  assert(o2->type == &integerType);
  assert(o2->is_exported == true);

  enter_scope(&inner);
  assert(current_scope == &inner);
  assert(current_scope->parent == &outer);
  new_var_decl(string_intern("inner1"), &realType, true);
  Decl *i1 = lookup_decl(string_intern("inner1"));
  assert(i1->kind == DECL_VAR);
  assert(i1->name == string_intern("inner1"));
  assert(i1->type == &realType);
  assert(i1->is_exported == true);
  Decl *oRef = lookup_decl(string_intern("outer1"));
  assert(oRef == o1);
  exit_scope();
  assert(current_scope == &outer);
  exit_scope();
  assert(current_scope == NULL);
}
