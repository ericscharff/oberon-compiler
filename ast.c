typedef enum {
  DECL_IMPORT,
  DECL_TYPE,
  DECL_CONST,
  DECL_VAR,
  DECL_PROC,
} DeclKind;

typedef struct Decl {
  DeclKind kind;
  const char *name;
  bool is_exported;
  Type *type;
} Decl;

#define SCOPE_SIZE 512
typedef struct Scope {
  Decl decls[SCOPE_SIZE];
  // Number of valid decls
  int size;
  struct Scope *parent;
} Scope;

// Typically, the current scope is stack allocated. E.g, when a procedure is defined, the function parsing
// the procedure allocates a new scope on the stack, and when it leaves, sets the global scope back. Thus,
// It is not safe to save Decl objects, but Types are persisted.
Scope *current_scope = NULL;

void enter_scope(Scope *scope) {
  scope->parent = current_scope;
  current_scope = scope;
  current_scope->size = 0;
}

void exit_scope(void) {
  current_scope = current_scope->parent;
}

Decl *lookup_decl(const char *name) {
  for (Scope *s = current_scope; s != NULL; s = s->parent) {
    for (int i=0; i < s->size; i++) {
      if (s->decls[i].name == name) {
        return &s->decls[i];
      }
    }
  }
  return NULL;
}

Decl *internal_add_decl(const char *name) {
  assert(name);
  assert(current_scope);
  assert(current_scope->size < SCOPE_SIZE);
  for (int i=0; i < current_scope->size; i++) {
    if (current_scope->decls[i].name == name) {
      error("%s redefined", name);
    }
  }
  Decl *d = &current_scope->decls[current_scope->size++];
  d->name = name;
  return d;
}

void add_var_decl(const char *name, Type *type, bool is_exported) {
  Decl *d = internal_add_decl(name);
  d->kind = DECL_VAR;
  d->type = type;
  d->is_exported = is_exported;
}

void ast_test(void) {
  Scope outer;
  Scope inner;

  enter_scope(&outer);
  assert(current_scope == &outer);
  add_var_decl(string_intern("outer1"), &integerType, false);
  add_var_decl(string_intern("outer2"), &integerType, true);
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
  Decl *oRef = lookup_decl(string_intern("outer1"));
  assert(oRef == o1);
  exit_scope();
  assert(current_scope == &outer);
  exit_scope();
  assert(current_scope == NULL);
}
