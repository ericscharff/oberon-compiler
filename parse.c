int indent = 0;

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

void dbg_print_int(int x) {
  for (int i = 0; i < indent; i++) {
    printf("  ");
  }
  printf("%d\n", x);
}

void dbg_print_str(const char *s) {
  for (int i = 0; i < indent; i++) {
    printf("  ");
  }
  printf("%s\n", s);
}

void dbg_enter(const char *name) {
  for (int i = 0; i < indent; i++) {
    printf("  ");
  }
  printf("%s:%d: Entering %s\n", token.pos.file_name, token.pos.line, name);
  indent++;
}

void dbg_exit(void) { indent--; }

Type *parse_type(void);
void parse_expression(void);
void parse_declaration_sequence(void);
void parse_statement_sequence(void);

bool is_imported_module(const char *name) {
  Decl *d = lookup_decl(name);
  return d && d->kind == DECL_IMPORT;
}

Decl *parse_possibly_undeclared_qualident(void) {
  dbg_enter("qualident");
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
    d = add_incomplete_decl(ident);
  }
  dbg_exit();
  return d;
}

Decl *parse_qualident(void) {
  dbg_enter("qualident");
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
  dbg_exit();
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

void parse_set_element(void) {
  dbg_enter("set_element");
  parse_expression();
  if (match_token(TOKEN_DOTDOT)) {
    parse_expression();
  }
  dbg_exit();
}

void parse_set() {
  dbg_enter("set");
  expect_token(TOKEN_LBRACE);
  if (!is_token(TOKEN_RBRACE)) {
    parse_set_element();
    while (match_token(TOKEN_COMMA)) {
      parse_set_element();
    }
  }
  expect_token(TOKEN_RBRACE);
  dbg_exit();
}

void parse_exp_list(void) {
  dbg_enter("exp_list");
  parse_expression();
  while (match_token(TOKEN_COMMA)) {
    parse_expression();
  }
  dbg_exit();
}

bool symbol_is_type_guard(Decl *d) {
  return d->kind == DECL_VARPARAM || d->type->kind == TYPE_POINTER;
}

void parse_designator(void) {
  dbg_enter("designator");
  Decl *d = parse_qualident();
  while (is_token(TOKEN_DOT) || is_token(TOKEN_LBRACK) ||
         is_token(TOKEN_CARET) ||
         (symbol_is_type_guard(d) && is_token(TOKEN_LPAREN))) {
    if (match_token(TOKEN_DOT)) {
      expect_identifier();
    } else if (match_token(TOKEN_LBRACK)) {
      parse_exp_list();
      expect_token(TOKEN_RBRACK);
    } else if (match_token(TOKEN_CARET)) {
    } else if (symbol_is_type_guard(d) && match_token(TOKEN_LPAREN)) {
      dbg_print_str("found type guard");
      parse_qualident();
      expect_token(TOKEN_RPAREN);
    } else {
      assert(0);
    }
  }
  dbg_exit();
}

void parse_actual_parameters(void) {
  dbg_enter("actual_parameters");
  match_token(TOKEN_LPAREN);
  if (!is_token(TOKEN_RPAREN)) {
    parse_exp_list();
  }
  match_token(TOKEN_RPAREN);
  dbg_exit();
}

void parse_factor(void) {
  dbg_enter("factor");
  if (is_token(TOKEN_INT)) {
    dbg_print_int(token.iVal);
    match_token(TOKEN_INT);
  } else if (match_token(TOKEN_REAL)) {
  } else if (match_token(TOKEN_STRING)) {
  } else if (match_keyword(keyword_nil)) {
  } else if (match_keyword(keyword_true)) {
  } else if (match_keyword(keyword_false)) {
  } else if (is_token(TOKEN_LBRACE)) {
    parse_set();
  } else if (is_token(TOKEN_IDENT)) {
    parse_designator();
    if (is_token(TOKEN_LPAREN)) {
      parse_actual_parameters();
    }
  } else if (match_token(TOKEN_LPAREN)) {
    parse_expression();
    expect_token(TOKEN_RPAREN);
  } else if (match_token(TOKEN_TILDE)) {
    parse_factor();
  } else {
    error("Factor expected");
  }
  dbg_exit();
}

bool match_mul_operator(void) {
  return match_token(TOKEN_STAR) || match_token(TOKEN_SLASH) ||
         match_keyword(keyword_div) || match_keyword(keyword_mod) ||
         match_token(TOKEN_AMP);
}

void parse_term(void) {
  dbg_enter("term");
  parse_factor();
  while (match_mul_operator()) {
    parse_factor();
  }
  dbg_exit();
}

bool match_add_operator(void) {
  return match_token(TOKEN_PLUS) || match_token(TOKEN_MINUS) ||
         match_keyword(keyword_or);
}

void parse_simple_expression(void) {
  dbg_enter("simple_expression");
  if (match_token(TOKEN_PLUS)) {
    printf("Unary plus\n");
  } else if (match_token(TOKEN_MINUS)) {
    printf("Unary minus\n");
  }
  parse_term();
  while (match_add_operator()) {
    parse_term();
  }
  dbg_exit();
}

bool match_relation() {
  return match_token(TOKEN_EQ) || match_token(TOKEN_POUND) ||
         match_token(TOKEN_LT) || match_token(TOKEN_LTEQ) ||
         match_token(TOKEN_GT) || match_token(TOKEN_GTEQ) ||
         match_keyword(keyword_in) || match_keyword(keyword_is);
}

void parse_expression(void) {
  dbg_enter("expression");
  parse_simple_expression();
  if (match_relation()) {
    parse_simple_expression();
  }
  dbg_exit();
}

void parse_if_statement(void) {
  dbg_enter("if");
  expect_keyword(keyword_if);
  parse_expression();
  expect_keyword(keyword_then);
  parse_statement_sequence();
  while (match_keyword(keyword_elsif)) {
    parse_expression();
    expect_keyword(keyword_then);
    parse_statement_sequence();
  }
  if (match_keyword(keyword_else)) {
    parse_statement_sequence();
  }
  expect_keyword(keyword_end);
  dbg_exit();
}

void parse_case_label(void) {
  dbg_enter("case_label");
  if (match_token(TOKEN_INT)) {
  } else if (match_token(TOKEN_STRING)) {
  } else if (is_token(TOKEN_IDENT)) {
    parse_qualident();
  } else {
    error("Case label (integer, string, identifier) expected");
  }
  dbg_exit();
}

void parse_case_label_range(void) {
  dbg_enter("case_label_range");
  parse_case_label();
  if (match_token(TOKEN_DOTDOT)) {
    parse_case_label();
  }
  dbg_exit();
}

void parse_case_label_list(void) {
  dbg_enter("case_label_list");
  parse_case_label_range();
  while (match_token(TOKEN_COMMA)) {
    parse_case_label_range();
  }
  dbg_exit();
}

void parse_case(void) {
  dbg_enter("case");
  if (is_token(TOKEN_INT) || is_token(TOKEN_STRING) || is_token(TOKEN_IDENT)) {
    parse_case_label_list();
    expect_token(TOKEN_COLON);
    parse_statement_sequence();
  }
  dbg_exit();
}

void parse_case_statement(void) {
  dbg_enter("case_statement");
  expect_keyword(keyword_case);
  parse_expression();
  expect_keyword(keyword_of);
  parse_case();
  while (match_token(TOKEN_VBAR)) {
    parse_case();
  }
  expect_keyword(keyword_end);
  dbg_exit();
}

void parse_while_statement(void) {
  dbg_enter("while");
  expect_keyword(keyword_while);
  parse_expression();
  expect_keyword(keyword_do);
  parse_statement_sequence();
  while (match_keyword(keyword_elsif)) {
    parse_expression();
    expect_keyword(keyword_do);
    parse_statement_sequence();
  }
  expect_keyword(keyword_end);
  dbg_exit();
}

void parse_repeat_statement(void) {
  dbg_enter("repeat");
  expect_keyword(keyword_repeat);
  parse_statement_sequence();
  expect_keyword(keyword_until);
  parse_expression();
  dbg_exit();
}

void parse_for_statement(void) {
  dbg_enter("for");
  expect_keyword(keyword_for);
  expect_identifier();
  expect_token(TOKEN_ASSIGN);
  parse_expression();
  expect_keyword(keyword_to);
  parse_expression();
  if (match_keyword(keyword_by)) {
    // Really ConstExpression
    parse_expression();
  }
  expect_keyword(keyword_do);
  parse_statement_sequence();
  expect_keyword(keyword_end);
  dbg_exit();
}

void parse_assign_or_proc_call(void) {
  dbg_enter("assign_or_proc_call");
  parse_designator();
  if (match_token(TOKEN_ASSIGN)) {
    // Assignment
    dbg_enter("assign");
    parse_expression();
    dbg_exit();
  } else {
    // Procedure call
    dbg_enter("proc_call");
    if (is_token(TOKEN_LPAREN)) {
      parse_actual_parameters();
    }
    dbg_exit();
  }
  dbg_exit();
}

void parse_statement(void) {
  dbg_enter("statement");
  if (is_keyword(keyword_if)) {
    parse_if_statement();
  } else if (is_keyword(keyword_case)) {
    parse_case_statement();
  } else if (is_keyword(keyword_while)) {
    parse_while_statement();
  } else if (is_keyword(keyword_repeat)) {
    parse_repeat_statement();
  } else if (is_keyword(keyword_for)) {
    parse_for_statement();
  } else if (is_token(TOKEN_IDENT)) {
    parse_assign_or_proc_call();
  }
  dbg_exit();
}

void parse_statement_sequence(void) {
  dbg_enter("statement_sequence");
  parse_statement();
  while (match_token(TOKEN_SEMI)) {
    parse_statement();
  }
  dbg_exit();
}

void parse_ident_def(const char **name, bool *is_exported) {
  dbg_enter("ident_def");
  *name = expect_identifier();
  *is_exported = match_token(TOKEN_STAR);
  dbg_exit();
}

IdentDef *parse_ident_list(void) {
  dbg_enter("ident_list");
  IdentDef *idents = NULL;
  const char *name;
  bool is_exported;
  parse_ident_def(&name, &is_exported);
  buf_push(idents, (IdentDef){name, is_exported});
  while (match_token(TOKEN_COMMA)) {
    parse_ident_def(&name, &is_exported);
    buf_push(idents, (IdentDef){name, is_exported});
  }
  dbg_exit();
  return idents;
}

Type *parse_array_type(void) {
  dbg_enter("array_type");
  Type *innerArray = make_array_type(NULL, 0);
  Type *outerArray = innerArray;
  expect_keyword(keyword_array);
  parse_expression();
  while (match_token(TOKEN_COMMA)) {
    parse_expression();
    outerArray = make_array_type(outerArray, 0);
  }
  expect_keyword(keyword_of);
  Type *elementType = parse_type();
  innerArray->array_type.element_type = elementType;
  dbg_exit();
  return outerArray;
}

Type *parse_record_type(void) {
  dbg_enter("record_type");
  Type *baseType = NULL;
  RecordField *fields = NULL;
  expect_keyword(keyword_record);
  if (match_token(TOKEN_LPAREN)) {
    baseType = parse_qualident_and_get_type();
    expect_token(TOKEN_RPAREN);
  }
  if (is_token(TOKEN_IDENT)) {
    dbg_enter("field_list_sequence");
    dbg_enter("field_list");
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
    dbg_exit();
    while (match_token(TOKEN_SEMI)) {
      dbg_enter("field_list");
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
      dbg_exit();
    }
    dbg_exit();
  }
  expect_keyword(keyword_end);
  dbg_exit();
  return make_record_type(baseType, fields);
}

Type *parse_pointer_type(void) {
  dbg_enter("pointer_type");
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
  dbg_exit();
  return make_pointer_type(t);
}

FormalParameter *parse_fp_section(FormalParameter *params) {
  dbg_enter("fp_section");
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
  for (size_t i = 0; i < buf_len(idents); i++) {
    buf_push(params,
             (FormalParameter){idents[i], varType, isVarParam, isOpenArray});
  }
  dbg_exit();
  return params;
}

Type *parse_formal_parameters(void) {
  dbg_enter("formal_parameters");
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
  dbg_exit();
  return make_procedure_type(params, returnType);
}

Type *parse_procedure_type(void) {
  Type *t = NULL;
  dbg_enter("procedure_type");
  expect_keyword(keyword_procedure);
  t = parse_formal_parameters();
  dbg_exit();
  return t;
}

Type *parse_type(void) {
  Type *t = NULL;
  dbg_enter("type");
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
  dbg_exit();
  return t;
}

void parse_const_declaration(void) {
  dbg_enter("const_declaration");
  const char *name;
  bool is_exported;
  parse_ident_def(&name, &is_exported);
  expect_token(TOKEN_EQ);
  parse_expression();
  // Placeholder INT type just to get code to parse
  add_const_decl(name, &integerType, is_exported);
  dbg_exit();
}

void parse_type_declaration(void) {
  dbg_enter("type_declaration");
  const char *name;
  bool is_exported;
  parse_ident_def(&name, &is_exported);
  expect_token(TOKEN_EQ);
  Type *t = parse_type();
  assert(t);
  t->name = name;
  add_type_decl(name, t, is_exported);
  dbg_exit();
}

void parse_var_declaration(void) {
  dbg_enter("var_declaration");
  IdentDef *defs = parse_ident_list();
  expect_token(TOKEN_COLON);
  Type *varType = parse_type();
  for (size_t i = 0; i < buf_len(defs); i++) {
    add_var_decl(defs[i].name, varType, defs[i].is_exported);
  }
  dbg_exit();
}

void populate_procedure_scope(const char *procName) {
  Decl *d = lookup_decl(procName);
  assert(d);
  Type *t = d->type;
  assert(t->kind == TYPE_PROCEDURE);
  for (size_t i = 0; i < buf_len(t->procedure_type.params); i++) {
    const char *paramName = t->procedure_type.params[i].name;
    Type *paramType = t->procedure_type.params[i].type;
    // TODO - handle open arrays somehow
    if (t->procedure_type.params[i].is_var_parameter) {
      add_varparam_decl(paramName, paramType);
    } else {
      add_param_decl(paramName, paramType);
    }
  }
}

void parse_procedure_body(const char *procName) {
  Scope scope;
  enter_scope(&scope);
  populate_procedure_scope(procName);
  dbg_enter("procedure_body");
  // Nested procedure declarations could be avoided here,
  // since nested procedures can't really access their
  // outer scopes anyway
  parse_declaration_sequence();
  if (match_keyword(keyword_begin)) {
    parse_statement_sequence();
  }
  if (match_keyword(keyword_return)) {
    parse_expression();
  }
  expect_keyword(keyword_end);
  dbg_exit();
  exit_scope();
}

const char *parse_procedure_heading(void) {
  dbg_enter("procedure_heading");
  expect_keyword(keyword_procedure);
  const char *name;
  bool is_exported;
  parse_ident_def(&name, &is_exported);
  Type *params = parse_formal_parameters();
  add_proc_decl(name, params, is_exported);
  dbg_exit();
  return name;
}
void parse_procedure_declaration(void) {
  dbg_enter("procedure_declaration");
  const char *name = parse_procedure_heading();
  expect_token(TOKEN_SEMI);
  parse_procedure_body(name);
  const char *endName = expect_identifier();
  if (name != endName) {
    error("Procedure name %s must match end name %s", name, endName);
  }
  dbg_exit();
}

void parse_declaration_sequence(void) {
  dbg_enter("declaration_sequence");
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
  while (is_keyword(keyword_procedure)) {
    parse_procedure_declaration();
    expect_token(TOKEN_SEMI);
  }
  dbg_exit();
}

void parse_import(void) {
  dbg_enter("import");
  const char *importName = expect_identifier();
  Decl *decls = NULL;
  if (match_token(TOKEN_ASSIGN)) {
    const char *canonicalName = expect_identifier();
    decls = get_imported_decls(canonicalName);
  } else {
    decls = get_imported_decls(importName);
  }
  assert(decls);
  add_import_decl(importName, decls);
  dbg_exit();
}

void parse_import_list(void) {
  dbg_enter("import_list");
  expect_keyword(keyword_import);
  parse_import();
  while (match_token(TOKEN_COMMA)) {
    parse_import();
  }
  expect_token(TOKEN_SEMI);
  dbg_exit();
}

Module *parse_module(void) {
  Scope scope;
  enter_scope(&scope);
  dbg_enter("module");
  expect_keyword(keyword_module);
  const char *moduleName = expect_identifier();
  expect_token(TOKEN_SEMI);
  if (is_keyword(keyword_import)) {
    parse_import_list();
  }
  parse_declaration_sequence();
  if (match_keyword(keyword_begin)) {
    parse_statement_sequence();
  }
  expect_keyword(keyword_end);
  const char *endModuleName = expect_identifier();
  if (moduleName != endModuleName) {
    error("Module name %s must match end name %s", moduleName, endModuleName);
  }
  expect_token(TOKEN_DOT);
  dbg_print_str(moduleName);
  dbg_exit();
  exit_scope();
  return make_module(moduleName, &scope);
}

void dbg_dump_scope(Module *m) {
  printf("MODULE %s:\n", m->name);
  for (size_t i = 0; i < buf_len(m->decls); i++) {
    printf("  Name: %s Kind: %s Exported: %s ", m->decls[i].name,
           decl_kind_names[m->decls[i].kind],
           m->decls[i].is_exported ? "true" : "false");
    dbg_dump_type(m->decls[i].type);
    printf("\n");
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
  snprintf(fileName, sizeof(fileName), "%s.Mod", moduleName);
  printf("Importing %s.\n", fileName);
  char *contents = read_file(fileName);
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

void parse_test_file(const char *fileName) {
  char *contents = read_file(fileName);
  init_stream(fileName, contents);
  next_token();
  dbg_dump_scope(parse_module());
  free(contents);
}

void parse_test(void) {
  Scope globalScope;
  enter_scope(&globalScope);
  init_global_types();
#if 0
  init_stream("", "MODULE abc; IMPORT A, B := aliased, C, D; CONST k=1+2+B.wow+3; TYPE MySet = SET; FooRec = ARRAY 5, 10, 15, 20 OF INTEGER; q* = INTEGER; r = q; END abc.");
  next_token();
  parse_module();
#endif
  parse_test_file("Test.Mod");
  exit_scope();
}
