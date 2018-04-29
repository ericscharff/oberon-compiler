int indent = 0;

void dbg_print_int(int x) {
  for (int i=0; i < indent; i++) {
    printf("  ");
  }
  printf("%d\n", x);
}

void dbg_print_str(const char *s) {
  for (int i=0; i < indent; i++) {
    printf("  ");
  }
  printf("%s\n", s);
}

void dbg_enter(const char *name) {
  for (int i=0; i < indent; i++) {
    printf("  ");
  }
  printf("Entering %s\n", name);
  indent++;
}

void dbg_exit(void) {
  indent--;
}

void parse_type(void);
void parse_expression(void);
void parse_declaration_sequence(void);
void parse_statement_sequence(void);

bool is_imported_module(const char *name) {
  // TODO
  return name[0] >= 'A' && name[0] <= 'Z';
}
void parse_qualident(void) {
  dbg_enter("qualident");
  const char *ident = expect_identifier();
  const char *moduleName = "";
  if (is_imported_module(ident)) {
    moduleName = ident;
    expect_token(TOKEN_DOT);
    ident = expect_identifier();
  }
  if (*moduleName) {
    dbg_print_str(moduleName);
  }
  dbg_print_str(ident);
  dbg_exit();
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
  parse_set_element();
  while (match_token(TOKEN_COMMA)) {
    parse_set_element();
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

bool symbol_type_is_pointer(void) {
  // TODO
  return false;
}

bool symbol_is_var_parameter(void) {
  // TODO
  return false;
}
void parse_designator(void) {
  dbg_enter("designator");
  parse_qualident();
  while (is_token(TOKEN_DOT) || is_token(TOKEN_LBRACK) || is_token(TOKEN_CARET) || is_token(TOKEN_LPAREN)) {
    if (match_token(TOKEN_DOT)) {
      expect_identifier();
    } else if (match_token(TOKEN_LBRACK)) {
      parse_exp_list();
      expect_token(TOKEN_RBRACK);
    } else if (match_token(TOKEN_CARET)) {
    } else if ((symbol_type_is_pointer() || symbol_is_var_parameter()) && match_token(TOKEN_LPAREN)) {
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
  parse_exp_list();
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
  return match_token(TOKEN_STAR) ||
    match_token(TOKEN_SLASH) ||
    match_keyword(keyword_div) ||
    match_keyword(keyword_mod) ||
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
  return match_token(TOKEN_PLUS) ||
    match_token(TOKEN_MINUS) ||
    match_token(TOKEN_VBAR);
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
  return match_token(TOKEN_EQ) ||
    match_token(TOKEN_POUND) ||
    match_token(TOKEN_LT) ||
    match_token(TOKEN_LTEQ) ||
    match_token(TOKEN_GT) ||
    match_token(TOKEN_GTEQ) ||
    match_keyword(keyword_in) ||
    match_keyword(keyword_is);
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
  } else {
    expect_token(TOKEN_IDENT);
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

void parse_ident_def(void) {
  dbg_enter("ident_def");
  expect_identifier();
  match_token(TOKEN_STAR);
  dbg_exit();
}

void parse_ident_list(void) {
  dbg_enter("ident_list");
  parse_ident_def();
  while (match_token(TOKEN_COMMA)) {
    parse_ident_def();
  }
  dbg_exit();
}

void parse_array_type(void) {
  dbg_enter("array_type");
  expect_keyword(keyword_array);
  parse_expression();
  while (match_token(TOKEN_COMMA)) {
    parse_expression();
  }
  expect_keyword(keyword_of);
  parse_type();
  dbg_exit();
}

void parse_field_list(void) {
  dbg_enter("field_list");
  parse_ident_list();
  expect_token(TOKEN_COLON);
  parse_type();
  dbg_exit();
}

void parse_field_list_sequence(void) {
  dbg_enter("field_list_sequence");
  parse_field_list();
  while (match_token(TOKEN_SEMI)) {
    parse_field_list();
  }
  dbg_exit();
}

void parse_record_type(void) {
  dbg_enter("record_type");
  expect_keyword(keyword_record);
  if (match_token(TOKEN_LPAREN)) {
    parse_qualident();
    expect_token(TOKEN_RPAREN);
  }
  if (is_token(TOKEN_IDENT)) {
    parse_field_list_sequence();
  }
  expect_keyword(keyword_end);
  dbg_exit();
}

void parse_pointer_type(void) {
  dbg_enter("pointer_type");
  expect_keyword(keyword_pointer);
  expect_keyword(keyword_to);
  parse_type();
  dbg_exit();
}

void parse_fp_section(void) {
  dbg_enter("fp_section");
  match_keyword(keyword_var);
  expect_identifier();
  while (match_token(TOKEN_COMMA)) {
    expect_identifier();
  }
  expect_token(TOKEN_COLON);
  // FormalType
  if (match_keyword(keyword_array)) {
    // ARRAY OF ...
    expect_keyword(keyword_of);
  }
  parse_qualident();
  dbg_exit();
}

void parse_formal_parameters(void) {
  dbg_enter("formal_parameters");
  expect_token(TOKEN_LPAREN);
  if (is_keyword(keyword_var) || is_token(TOKEN_IDENT)) {
    parse_fp_section();
  }
  while (match_token(TOKEN_SEMI)) {
    parse_fp_section();
  }
  expect_token(TOKEN_RPAREN);
  if (match_token(TOKEN_COLON)) {
    parse_qualident();
  }
  dbg_exit();
}

void parse_procedure_type(void) {
  dbg_enter("procedure_type");
  expect_keyword(keyword_procedure);
  if (is_token(TOKEN_LPAREN)) {
    parse_formal_parameters();
  }
  dbg_exit();
}

void parse_type(void) {
  dbg_enter("type");
  if (is_token(TOKEN_IDENT)) {
    parse_qualident();
  } else if (is_keyword(keyword_array)) {
    parse_array_type();
  } else if (is_keyword(keyword_record)) {
    parse_record_type();
  } else if (is_keyword(keyword_pointer)) {
    parse_pointer_type();
  } else if (is_keyword(keyword_procedure)) {
    parse_procedure_type();
  } else {
    error("identifier, ARRAY, RECORD, POINTER, or PROCEDURE expected");
  }
  dbg_exit();
}

void parse_const_declaration(void) {
  dbg_enter("const_declaration");
  parse_ident_def();
  expect_token(TOKEN_EQ);
  parse_expression();
  dbg_exit();
}

void parse_type_declaration(void) {
  dbg_enter("type_declaration");
  parse_ident_def();
  expect_token(TOKEN_EQ);
  parse_type();
  dbg_exit();
}

void parse_var_declaration(void) {
  dbg_enter("var_declaration");
  parse_ident_list();
  expect_token(TOKEN_COLON);
  parse_type();
  dbg_exit();
}

void parse_procedure_body(void) {
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
}

void parse_procedure_heading(void) {
  dbg_enter("procedure_heading");
  expect_keyword(keyword_procedure);
  parse_ident_def();
  if (is_token(TOKEN_LPAREN)) {
    parse_formal_parameters();
  }
  dbg_exit();
}
void parse_procedure_declaration(void) {
  dbg_enter("procedure_declaration");
  parse_procedure_heading();
  expect_token(TOKEN_SEMI);
  parse_procedure_body();
  expect_identifier();
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
  if (match_token(TOKEN_ASSIGN)) {
    const char *canonicalName = expect_identifier();
    printf("import %s as %s\n", canonicalName, importName);
  } else {
    printf("import %s\n", importName);
  }
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

void parse_module(void) {
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
  dbg_exit();
}

void parse_test(void) {
  init_stream("", "MODULE abc; IMPORT a, b := aliased, c, d; CONST k=1+2*c+3; END abc.");
  next_token();
  parse_module();
}
