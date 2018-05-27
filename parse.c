typedef struct IdentDef {
  const char *name;
  bool is_exported;
} IdentDef;

Decl *get_imported_decls(const char *moduleName);

#define IMPORT_CACHE_SIZE 100
struct {
  Decl import[IMPORT_CACHE_SIZE];
  size_t size;
} importCache;

Type *parse_type(void);
Expr *parse_expression(void);
void parse_declaration_sequence(void);
Statement *parse_statement_sequence(void);

bool is_imported_module(const char *name) {
  Decl *d = lookup_decl(name);
  return d && d->kind == DECL_IMPORT;
}

Decl *parse_possibly_undeclared_qualident(void) {
  Loc loc = token.pos;
  const char *ident = expect_identifier();
  Decl *d = NULL;
  if (is_imported_module(ident)) {
    const char *moduleName = ident;
    expect_token(TOKEN_DOT);
    ident = expect_identifier();
    d = lookup_module_import(moduleName, ident);
  } else {
    d = lookup_decl(ident);
  }
  if (!d) {
    d = new_decl_incomplete(ident, loc);
  }
  return d;
}

Decl *parse_qualident(void) {
  const char *ident = expect_identifier();
  const char *moduleName = NULL;
  Decl *d = NULL;
  if (is_imported_module(ident)) {
    moduleName = ident;
    expect_token(TOKEN_DOT);
    ident = expect_identifier();
    d = lookup_module_import(moduleName, ident);
  } else {
    d = lookup_decl(ident);
  }
  if (!d) {
    error("%s undefined", ident);
  }
  return d;
}

Type *parse_qualident_and_get_type(void) {
  Decl *d = parse_qualident();
  if (d->kind == DECL_TYPE || d->kind == DECL_INCOMPLETE) {
    return d->type;
  } else {
    error("%s is not a type", d->name);
  }
  return NULL;
}

Expr *parse_set_element(void) {
  Loc loc = token.pos;
  Expr *e = parse_expression();
  if (match_token(TOKEN_DOTDOT)) {
    e = new_expr_binary(TOKEN_DOTDOT, e, parse_expression(), loc);
  } else {
    e = new_expr_unary(TOKEN_AS_SET_ELT, e, loc);
  }
  return e;
}

Expr *parse_set() {
  Loc loc = token.pos;
  Expr *e = NULL;
  expect_token(TOKEN_LBRACE);
  if (is_token(TOKEN_RBRACE)) {
    e = new_expr_emptyset(loc);
  } else {
    e = parse_set_element();
    while (match_token(TOKEN_COMMA)) {
      e = new_expr_binary(TOKEN_PLUS, e, parse_set_element(), loc);
    }
  }
  expect_token(TOKEN_RBRACE);
  return e;
}

bool symbol_is_type_guard(Type *t, Decl *d) {
  return (t && t->kind == TYPE_POINTER) || (d && d->kind == DECL_VARPARAM);
}

Expr *parse_designator(void) {
  Loc loc = token.pos;
  Decl *d = parse_qualident();
  assert(d);
  Type *t = d->type;

  Expr *e = new_expr_identref(d->name, d->package_name, loc);

  while (is_token(TOKEN_DOT) || is_token(TOKEN_LBRACK) ||
         is_token(TOKEN_CARET) ||
         (symbol_is_type_guard(t, d) && is_token(TOKEN_LPAREN))) {
    loc = token.pos;
    if (match_token(TOKEN_DOT)) {
      const char *fieldName = expect_identifier();
      t = lookup_field(t, fieldName);
      d = NULL;
      e = new_expr_fieldref(fieldName, e, loc);
    } else if (match_token(TOKEN_LBRACK)) {
      e = new_expr_arrayref(parse_expression(), e, loc);
      while (match_token(TOKEN_COMMA)) {
        e = new_expr_arrayref(parse_expression(), e, loc);
      }
      expect_token(TOKEN_RBRACK);
    } else if (match_token(TOKEN_CARET)) {
      e = new_expr_pointerderef(e, loc);
    } else if (symbol_is_type_guard(t, d) && match_token(TOKEN_LPAREN)) {
      Decl *guarded = parse_qualident();
      t = guarded->type;
      e = new_expr_typeguard(t, e, loc);
      expect_token(TOKEN_RPAREN);
    } else {
      assert(0);
    }
  }
  return e;
}

Expr **parse_actual_parameters(void) {
  Expr **args = NULL;
  match_token(TOKEN_LPAREN);
  if (!is_token(TOKEN_RPAREN)) {
    buf_push(args, parse_expression());
    while (match_token(TOKEN_COMMA)) {
      buf_push(args, parse_expression());
    }
  }
  match_token(TOKEN_RPAREN);
  return args;
}

Expr *parse_factor(void) {
  Loc loc = token.pos;
  Expr *e = NULL;
  if (is_token(TOKEN_INT)) {
    e = new_expr_integer(token.iVal, loc);
    match_token(TOKEN_INT);
  } else if (is_token(TOKEN_REAL)) {
    e = new_expr_real(token.rVal, loc);
    match_token(TOKEN_REAL);
  } else if (is_token(TOKEN_STRING)) {
    e = new_expr_string(token.sVal, loc);
    match_token(TOKEN_STRING);
  } else if (match_keyword(keyword_nil)) {
    e = new_expr_nil(loc);
  } else if (match_keyword(keyword_true)) {
    e = new_expr_true(loc);
  } else if (match_keyword(keyword_false)) {
    e = new_expr_false(loc);
  } else if (is_token(TOKEN_LBRACE)) {
    e = parse_set();
  } else if (is_token(TOKEN_IDENT)) {
    e = parse_designator();
    if (is_token(TOKEN_LPAREN)) {
      e = new_expr_proccall(e, parse_actual_parameters(), loc);
    }
  } else if (match_token(TOKEN_LPAREN)) {
    e = parse_expression();
    expect_token(TOKEN_RPAREN);
  } else if (match_token(TOKEN_TILDE)) {
    e = new_expr_unary(TOKEN_TILDE, parse_factor(), loc);
  } else {
    error("Factor expected");
  }
  return e;
}

bool is_mul_operator(void) {
  return is_token(TOKEN_STAR) || is_token(TOKEN_SLASH) || is_token(TOKEN_DIV) ||
         is_token(TOKEN_MOD) || is_token(TOKEN_AMP) || is_token(TOKEN_XOR);
}

Expr *parse_term(void) {
  Loc loc = token.pos;
  Expr *e = parse_factor();
  while (is_mul_operator()) {
    loc = token.pos;
    TokenKind op = token.kind;
    next_token();
    e = new_expr_binary(op, e, parse_factor(), loc);
  }
  return e;
}

bool is_add_operator(void) {
  return is_token(TOKEN_PLUS) || is_token(TOKEN_MINUS) || is_token(TOKEN_OR);
}

Expr *parse_simple_expression(void) {
  Loc loc = token.pos;
  bool unary_plus = false;
  bool unary_minus = false;
  if (match_token(TOKEN_PLUS)) {
    unary_plus = true;
  } else if (match_token(TOKEN_MINUS)) {
    unary_minus = true;
  }
  Expr *e = parse_term();
  if (unary_plus) {
    e = new_expr_unary(TOKEN_PLUS, e, loc);
  }
  if (unary_minus) {
    e = new_expr_unary(TOKEN_MINUS, e, loc);
  }
  while (is_add_operator()) {
    loc = token.pos;
    TokenKind op = token.kind;
    next_token();
    e = new_expr_binary(op, e, parse_term(), loc);
  }
  return e;
}

bool is_relation() {
  return is_token(TOKEN_EQ) || is_token(TOKEN_POUND) || is_token(TOKEN_LT) ||
         is_token(TOKEN_LTEQ) || is_token(TOKEN_GT) || is_token(TOKEN_GTEQ) ||
         is_token(TOKEN_IN) || is_token(TOKEN_IS);
}

Expr *parse_expression(void) {
  Loc loc = token.pos;
  Expr *e = parse_simple_expression();
  if (is_relation()) {
    loc = token.pos;
    TokenKind op = token.kind;
    next_token();
    e = new_expr_binary(op, e, parse_simple_expression(), loc);
  }
  return e;
}

Statement parse_if_statement(void) {
  Loc loc = token.pos;
  expect_keyword(keyword_if);
  Expr *cond = parse_expression();
  expect_keyword(keyword_then);
  Statement *then_clause = parse_statement_sequence();
  ElseIf *elseifs = NULL;
  Statement *else_clause = NULL;
  while (match_keyword(keyword_elsif)) {
    ElseIf e;
    e.cond = parse_expression();
    expect_keyword(keyword_then);
    e.body = parse_statement_sequence();
    buf_push(elseifs, e);
  }
  if (match_keyword(keyword_else)) {
    else_clause = parse_statement_sequence();
  }
  expect_keyword(keyword_end);
  return new_stmt_if(loc, cond, then_clause, elseifs, else_clause);
}

Expr *parse_case_label(void) {
  Expr *e = NULL;
  if (is_token(TOKEN_INT) || is_token(TOKEN_STRING) || is_token(TOKEN_IDENT)) {
    e = parse_factor();
  } else {
    error("Case label (integer, string, identifier) expected");
  }
  return e;
}

Expr *parse_case_label_range(void) {
  Expr *label = parse_case_label();
  if (match_token(TOKEN_DOTDOT)) {
    label = new_expr_binary(TOKEN_CASE_DOTDOT, label, parse_case_label(),
                            label->loc);
  }
  return label;
}

Expr **parse_case_label_list(void) {
  Expr **labels = NULL;
  buf_push(labels, parse_case_label_range());
  while (match_token(TOKEN_COMMA)) {
    buf_push(labels, parse_case_label_range());
  }
  return labels;
}

Case parse_case(void) {
  Case c = {NULL, NULL};
  if (is_token(TOKEN_INT) || is_token(TOKEN_STRING) || is_token(TOKEN_IDENT)) {
    Expr **labels = parse_case_label_list();
    expect_token(TOKEN_COLON);
    Statement *body = parse_statement_sequence();
    return new_case(labels, body);
  }
  return c;
}

Statement parse_case_statement(void) {
  Loc loc = token.pos;
  expect_keyword(keyword_case);
  Expr *cond = parse_expression();
  Case *cases = NULL;
  expect_keyword(keyword_of);
  Case c = parse_case();
  if (c.cond) {
    buf_push(cases, c);
  }
  while (match_token(TOKEN_VBAR)) {
    c = parse_case();
    if (c.cond) {
      buf_push(cases, c);
    }
  }
  expect_keyword(keyword_end);
  return new_stmt_case(loc, cond, cases);
}

Statement parse_while_statement(void) {
  Loc loc = token.pos;
  expect_keyword(keyword_while);
  Expr *cond = parse_expression();
  expect_keyword(keyword_do);
  Statement *body = parse_statement_sequence();
  ElseIf *elseifs = NULL;
  while (match_keyword(keyword_elsif)) {
    ElseIf e;
    e.cond = parse_expression();
    expect_keyword(keyword_do);
    e.body = parse_statement_sequence();
    buf_push(elseifs, e);
  }
  expect_keyword(keyword_end);
  return new_stmt_while(loc, cond, body, elseifs);
}

Statement parse_repeat_statement(void) {
  Loc loc = token.pos;
  expect_keyword(keyword_repeat);
  Statement *body = parse_statement_sequence();
  expect_keyword(keyword_until);
  Expr *cond = parse_expression();
  return new_stmt_repeat(loc, cond, body);
}

Statement parse_for_statement(void) {
  Loc loc = token.pos;
  expect_keyword(keyword_for);
  const char *ident = expect_identifier();
  expect_token(TOKEN_ASSIGN);
  Expr *start = parse_expression();
  expect_keyword(keyword_to);
  Expr *end = parse_expression();
  Expr *increment = NULL;
  if (match_keyword(keyword_by)) {
    // Really ConstExpression
    increment = parse_expression();
  }
  expect_keyword(keyword_do);
  Statement *body = parse_statement_sequence();
  expect_keyword(keyword_end);
  return new_stmt_for(loc, ident, start, end, increment, body);
}

Statement parse_assign_or_proc_call(void) {
  Loc loc = token.pos;
  Expr *lvalue = parse_designator();
  if (match_token(TOKEN_ASSIGN)) {
    // Assignment
    Expr *rvalue = parse_expression();
    return new_stmt_assignment(loc, lvalue, rvalue);
  } else {
    // Procedure call
    Expr **args = NULL;
    if (is_token(TOKEN_LPAREN)) {
      args = parse_actual_parameters();
    }
    return new_stmt_proccall(loc, lvalue, args);
  }
}

Statement parse_statement(void) {
  if (is_keyword(keyword_if)) {
    return parse_if_statement();
  } else if (is_keyword(keyword_case)) {
    return parse_case_statement();
  } else if (is_keyword(keyword_while)) {
    return parse_while_statement();
  } else if (is_keyword(keyword_repeat)) {
    return parse_repeat_statement();
  } else if (is_keyword(keyword_for)) {
    return parse_for_statement();
  } else if (is_token(TOKEN_IDENT)) {
    return parse_assign_or_proc_call();
  } else {
    return new_stmt_empty();
  }
}

Statement *parse_statement_sequence(void) {
  Statement *body = NULL;
  buf_push(body, parse_statement());
  while (match_token(TOKEN_SEMI)) {
    buf_push(body, parse_statement());
  }
  return body;
}

void parse_ident_def(const char **name, bool *is_exported) {
  *name = expect_identifier();
  *is_exported = match_token(TOKEN_STAR);
}

IdentDef *parse_ident_list(void) {
  IdentDef *idents = NULL;
  const char *name;
  bool is_exported;
  parse_ident_def(&name, &is_exported);
  buf_push(idents, (IdentDef){name, is_exported});
  while (match_token(TOKEN_COMMA)) {
    parse_ident_def(&name, &is_exported);
    buf_push(idents, (IdentDef){name, is_exported});
  }
  return idents;
}

Type *parse_array_type(void) {
  expect_keyword(keyword_array);
  Type *outerArray = new_type_array(parse_expression());
  Type *lastArray = outerArray;
  while (match_token(TOKEN_COMMA)) {
    Type *newArray = new_type_array(parse_expression());
    lastArray->array_type.element_type = newArray;
    lastArray = newArray;
  }
  expect_keyword(keyword_of);
  Type *elementType = parse_type();
  lastArray->array_type.element_type = elementType;
  return outerArray;
}

Type *parse_record_type(void) {
  Type *baseType = NULL;
  RecordField *fields = NULL;
  expect_keyword(keyword_record);
  if (match_token(TOKEN_LPAREN)) {
    baseType = parse_qualident_and_get_type();
    expect_token(TOKEN_RPAREN);
  }
  if (is_token(TOKEN_IDENT)) {
    if (is_token(TOKEN_IDENT)) {
      IdentDef *defs = parse_ident_list();
      expect_token(TOKEN_COLON);
      Type *fieldType = parse_type();
      for (size_t i = 0; i < buf_len(defs); i++) {
        buf_push(fields,
                 (RecordField){defs[i].name, fieldType, defs[i].is_exported});
      }
      buf_free(defs);
    }
    while (match_token(TOKEN_SEMI)) {
      if (is_token(TOKEN_IDENT)) {
        IdentDef *defs = parse_ident_list();
        expect_token(TOKEN_COLON);
        Type *fieldType = parse_type();
        for (size_t i = 0; i < buf_len(defs); i++) {
          buf_push(fields,
                   (RecordField){defs[i].name, fieldType, defs[i].is_exported});
        }
        buf_free(defs);
      }
    }
  }
  expect_keyword(keyword_end);
  return new_type_record(baseType, fields);
}

Type *parse_pointer_type(void) {
  expect_keyword(keyword_pointer);
  expect_keyword(keyword_to);
  // Pointers are a special case. They can be forward declared. This,
  // POINTER TO <qualident> needs to be handled separately
  Type *t;
  if (is_token(TOKEN_IDENT)) {
    Decl *d = parse_possibly_undeclared_qualident();
    t = d->type;
  } else {
    t = parse_type();
  }
  assert(t);
  return new_type_pointer(t);
}

FormalParameter *parse_fp_section(FormalParameter *params) {
  const char **idents = NULL;
  bool isVarParam = match_keyword(keyword_var);
  bool isOpenArray = false;
  buf_push(idents, expect_identifier());

  while (match_token(TOKEN_COMMA)) {
    buf_push(idents, expect_identifier());
  }
  expect_token(TOKEN_COLON);
  // FormalType
  if (match_keyword(keyword_array)) {
    // ARRAY OF ...
    expect_keyword(keyword_of);
    isOpenArray = true;
  }
  Type *varType = parse_qualident_and_get_type();
  if (isOpenArray) {
    Type *t = new_type_array(NULL);
    t->array_type.element_type = varType;
    varType = t;
  }
  for (size_t i = 0; i < buf_len(idents); i++) {
    buf_push(params,
             (FormalParameter){idents[i], varType, isVarParam, isOpenArray});
  }
  return params;
}

Type *parse_formal_parameters(void) {
  FormalParameter *params = NULL;
  Type *returnType = NULL;
  if (match_token(TOKEN_LPAREN)) {
    if (is_keyword(keyword_var) || is_token(TOKEN_IDENT)) {
      params = parse_fp_section(params);
    }
    while (match_token(TOKEN_SEMI)) {
      params = parse_fp_section(params);
    }
    expect_token(TOKEN_RPAREN);
    if (match_token(TOKEN_COLON)) {
      returnType = parse_qualident_and_get_type();
    }
  }
  return new_type_procedure(params, returnType);
}

Type *parse_procedure_type(void) {
  Type *t = NULL;
  expect_keyword(keyword_procedure);
  t = parse_formal_parameters();
  return t;
}

Type *parse_type(void) {
  Type *t = NULL;
  if (is_token(TOKEN_IDENT)) {
    t = parse_qualident_and_get_type();
  } else if (is_keyword(keyword_array)) {
    t = parse_array_type();
  } else if (is_keyword(keyword_record)) {
    t = parse_record_type();
  } else if (is_keyword(keyword_pointer)) {
    t = parse_pointer_type();
  } else if (is_keyword(keyword_procedure)) {
    t = parse_procedure_type();
  } else {
    error("identifier, ARRAY, RECORD, POINTER, or PROCEDURE expected");
  }
  return t;
}

void parse_const_declaration(void) {
  Loc loc = token.pos;
  const char *name;
  bool is_exported;
  parse_ident_def(&name, &is_exported);
  expect_token(TOKEN_EQ);
  new_decl_const(name, loc, parse_expression(), is_exported);
}

void parse_type_declaration(void) {
  Loc loc = token.pos;
  const char *name;
  bool is_exported;
  parse_ident_def(&name, &is_exported);
  expect_token(TOKEN_EQ);
  Type *t = parse_type();
  assert(t);
  new_decl_type(name, loc, t, is_exported);
}

void parse_var_declaration(void) {
  Loc loc = token.pos;
  IdentDef *defs = parse_ident_list();
  expect_token(TOKEN_COLON);
  Type *varType = parse_type();
  for (size_t i = 0; i < buf_len(defs); i++) {
    new_decl_var(defs[i].name, loc, varType, defs[i].is_exported);
  }
}

void populate_procedure_scope(Decl *d) {
  assert(d);
  Type *t = d->type;
  assert(t->kind == TYPE_PROCEDURE);
  for (size_t i = 0; i < buf_len(t->procedure_type.params); i++) {
    Loc loc = token.pos;
    const char *paramName = t->procedure_type.params[i].name;
    Type *paramType = t->procedure_type.params[i].type;
    if (t->procedure_type.params[i].is_var_parameter) {
      new_decl_varparam(paramName, loc, paramType);
    } else {
      new_decl_param(paramName, loc, paramType);
    }
  }
}

void parse_procedure_body(Decl *procDecl) {
  const char *parentPackage = current_package_name;
  Scope scope;
  scope.decls = NULL;
  enter_scope(&scope, string_intern(""));
  populate_procedure_scope(procDecl);
  // Nested procedure declarations could be avoided here,
  // since nested procedures can't really access their
  // outer scopes anyway
  parse_declaration_sequence();
  Statement *body = NULL;
  Expr *returnVal = NULL;
  if (match_keyword(keyword_begin)) {
    body = parse_statement_sequence();
  }
  if (match_keyword(keyword_return)) {
    returnVal = parse_expression();
  }
  expect_keyword(keyword_end);
  assert(procDecl->proc_decl.decls == NULL);
  assert(procDecl->proc_decl.body == NULL);
  procDecl->proc_decl.decls = scope.decls;
  procDecl->proc_decl.body = body;
  procDecl->proc_decl.ret_val = returnVal;
  exit_scope(parentPackage);
}

Decl *parse_procedure_heading(void) {
  Loc loc = token.pos;
  bool native = false;
  if (match_keyword(keyword_native)) {
    native = true;
  }
  expect_keyword(keyword_procedure);
  const char *name;
  bool is_exported;
  parse_ident_def(&name, &is_exported);
  Type *params = parse_formal_parameters();
  params->procedure_type.native = native;
  return new_decl_proc(name, loc, params, is_exported);
}

void parse_procedure_declaration(void) {
  Decl *d = parse_procedure_heading();
  expect_token(TOKEN_SEMI);
  parse_procedure_body(d);
  const char *endName = expect_identifier();
  if (d->name != endName) {
    error("Procedure name %s must match end name %s", d->name, endName);
  }
}

void parse_declaration_sequence(void) {
  if (match_keyword(keyword_const)) {
    while (is_token(TOKEN_IDENT)) {
      parse_const_declaration();
      expect_token(TOKEN_SEMI);
    }
  }
  if (match_keyword(keyword_type)) {
    while (is_token(TOKEN_IDENT)) {
      parse_type_declaration();
      expect_token(TOKEN_SEMI);
    }
  }
  if (match_keyword(keyword_var)) {
    while (is_token(TOKEN_IDENT)) {
      parse_var_declaration();
      expect_token(TOKEN_SEMI);
    }
  }
  while (is_keyword(keyword_procedure) || is_keyword(keyword_native)) {
    parse_procedure_declaration();
    expect_token(TOKEN_SEMI);
  }
}

void parse_import(void) {
  Loc loc = token.pos;
  const char *importName = expect_identifier();
  Decl *decls = NULL;
  if (match_token(TOKEN_ASSIGN)) {
    const char *canonicalName = expect_identifier();
    decls = get_imported_decls(canonicalName);
  } else {
    decls = get_imported_decls(importName);
  }
  assert(decls);
  new_decl_import(importName, loc, decls);
}

void parse_import_list(void) {
  expect_keyword(keyword_import);
  parse_import();
  while (match_token(TOKEN_COMMA)) {
    parse_import();
  }
  expect_token(TOKEN_SEMI);
}

Module *parse_module(void) {
  const char *parentPackage = current_package_name;
  expect_keyword(keyword_module);
  const char *moduleName = expect_identifier();
  Scope scope;
  scope.decls = NULL;
  enter_scope(&scope, moduleName);
  Statement *body = NULL;
  expect_token(TOKEN_SEMI);
  if (is_keyword(keyword_import)) {
    parse_import_list();
  }
  parse_declaration_sequence();
  if (match_keyword(keyword_begin)) {
    body = parse_statement_sequence();
  }
  expect_keyword(keyword_end);
  const char *endModuleName = expect_identifier();
  if (moduleName != endModuleName) {
    error("Module name %s must match end name %s", moduleName, endModuleName);
  }
  expect_token(TOKEN_DOT);
  Module *m = new_module(moduleName, scope.decls, body);
  exit_scope(parentPackage);
  return m;
}

void dbg_dump_scope(Module *m) {
  printf("MODULE %s:\n", m->name);
  for (size_t i = 0; i < buf_len(m->decls); i++) {
    printf("  Name: %s Pos: %s:%d Kind: %s Exported: %s\n", m->decls[i].name,
           m->decls[i].loc.file_name, m->decls[i].loc.line,
           decl_kind_names[m->decls[i].kind],
           m->decls[i].is_exported ? "true" : "false");
    if (m->decls[i].kind == DECL_PROC) {
      for (size_t j = 0; j < buf_len(m->decls[i].proc_decl.decls); j++) {
        Decl *d = &m->decls[i].proc_decl.decls[j];
        printf("    Name: %s Pos: %s:%d Kind: %s Exported: %s\n", d->name,
               d->loc.file_name, d->loc.line, decl_kind_names[d->kind],
               d->is_exported ? "true" : "false");
      }
      stmt_indent += 4;
      dbg_dump_stmts(m->decls[i].proc_decl.body);
      stmt_indent -= 4;
    }
  }
  if (m->initializer) {
    dbg_dump_stmts(m->initializer->proc_decl.body);
  }
}

Decl *get_imported_decls(const char *moduleName) {
  for (size_t i = 0; i < importCache.size; i++) {
    if (importCache.import[i].name == moduleName) {
      if (importCache.import[i].kind == DECL_INCOMPLETE) {
        error("%s creates a circular import dependency", moduleName);
      } else {
        printf("using cached module import %s\n", moduleName);
        return importCache.import[i].imported_decls;
      }
    }
  }
  size_t index = importCache.size++;
  assert(index <= IMPORT_CACHE_SIZE);
  importCache.import[index].name = moduleName;
  importCache.import[index].kind = DECL_INCOMPLETE;
  char fileName[1024];
  snprintf(fileName, sizeof(fileName), "%s.ob", moduleName);
  printf("Importing %s.\n", fileName);
  char *contents = read_file(fileName);
  assert(contents);
  Token oldToken = token;
  const char *oldStream = stream;
  // This works because the current scope has to me the module
  // scope (we've only parsed imports), and thus the parent
  // scope is the global scope
  Scope *oldScope = current_scope;
  current_scope = current_scope->parent;
  init_stream(fileName, contents);
  next_token();
  Module *m = parse_module();
  assert(m);
  free(contents);
  init_stream(oldToken.pos.file_name, oldStream);
  token = oldToken;
  current_scope = oldScope;
  importCache.import[index].kind = DECL_IMPORT;
  importCache.import[index].imported_decls = m->decls;
  free(m);
  return importCache.import[index].imported_decls;
}

Module *parse_test_file(const char *fileName) {
  char *contents = read_file(fileName);
  assert(contents);
  init_stream(fileName, contents);
  next_token();
  Module *m = parse_module();
  dbg_dump_scope(m);
  free(contents);
  return m;
}

void init_global_defs(void) {
  char *contents = read_file("builtin.defs");
  assert(contents);
  init_stream(NULL, contents);
  next_token();
  parse_declaration_sequence();
  free(contents);
}

void parse_test(void) {
  Scope globalScope;
  globalScope.decls = NULL;
  enter_scope(&globalScope, "");
  init_global_types();
  init_global_defs();
  init_stream("",
              "MODULE abc; CONST k=1*2+3+4; TYPE MySet* = SET; FooRec = ARRAY "
              "5, 10, 15, 20 OF INTEGER; q* = INTEGER; r = q; END abc.");
  next_token();
  dbg_dump_scope(parse_module());
  assert(current_scope == &globalScope);
  parse_test_file("Test.ob");
  exit_scope("");
  assert(current_scope == NULL);
}
