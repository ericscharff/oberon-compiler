int indent = 0;

void dbg_enter(const char *name) {
  for (int i=0; i < indent; i++) {
    printf("  ");
  }
  printf("Entering %s", name);
  indent++;
}

void dbg_exit(void) {
  indent--;
}

void parse_type(void);
void parse_expression(void);
void parse_declaration_sequence(void);

bool is_imported_module(const char *name) {
  // TODO
  return name[0] >= 'A' && name[0] <= 'Z';
}
void parse_qualident(void) {
  const char *ident = expect_identifier();
  const char *moduleName = "";
  if (is_imported_module(ident)) {
    moduleName = ident;
    expect_token(TOKEN_DOT);
    ident = expect_identifier();
  }
  printf("Identifier %s.%s\n", moduleName, ident);
}

void parse_set_element(void) {
  parse_expression();
  if (match_token(TOKEN_DOTDOT)) {
    parse_expression();
  }
}

void parse_set() {
  expect_token(TOKEN_LBRACE);
  parse_set_element();
  while (match_token(TOKEN_COMMA)) {
    parse_set_element();
  }
  expect_token(TOKEN_RBRACE);
}

void parse_exp_list(void) {
  parse_expression();
  while (match_token(TOKEN_COMMA)) {
    parse_expression();
  }
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
}

void parse_actual_parameters(void) {
  match_token(TOKEN_LPAREN);
  parse_exp_list();
  match_token(TOKEN_RPAREN);
}

void parse_factor(void) {
  if (match_token(TOKEN_INT)) {
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
}

bool match_mul_operator(void) {
  return match_token(TOKEN_STAR) ||
    match_token(TOKEN_SLASH) ||
    match_keyword(keyword_div) ||
    match_keyword(keyword_mod) ||
    match_token(TOKEN_AMP);
}

void parse_term(void) {
  parse_factor();
  while (match_mul_operator()) {
    parse_factor();
  }
}

bool match_add_operator(void) {
  return match_token(TOKEN_PLUS) ||
    match_token(TOKEN_MINUS) ||
    match_token(TOKEN_VBAR);
}

void parse_simple_expression(void) {
  if (match_token(TOKEN_PLUS)) {
    printf("Unary plus\n");
  } else if (match_token(TOKEN_MINUS)) {
    printf("Unary minus\n");
  }
  parse_term();
  while (match_add_operator()) {
    parse_term();
  }
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
  parse_simple_expression();
  if (match_relation()) {
    parse_simple_expression();
  }
}

void parse_statement_sequence(void) {
  // TODO
}

void parse_ident_def(void) {
  expect_identifier();
  match_token(TOKEN_STAR);
}

void parse_ident_list(void) {
  parse_ident_def();
  while (match_token(TOKEN_COMMA)) {
    parse_ident_def();
  }
}

void parse_array_type(void) {
  expect_keyword(keyword_array);
  parse_expression();
  while (match_token(TOKEN_COMMA)) {
    parse_expression();
  }
  expect_keyword(keyword_of);
  parse_type();
}

void parse_field_list(void) {
  parse_ident_list();
  expect_token(TOKEN_COLON);
  parse_type();
}

void parse_field_list_sequence(void) {
  parse_field_list();
  while (match_token(TOKEN_SEMI)) {
    parse_field_list();
  }
}

void parse_record_type(void) {
  expect_keyword(keyword_record);
  if (match_token(TOKEN_LPAREN)) {
    parse_qualident();
    expect_token(TOKEN_RPAREN);
  }
  if (is_token(TOKEN_IDENT)) {
    parse_field_list_sequence();
  }
  expect_keyword(keyword_end);
}

void parse_pointer_type(void) {
  expect_keyword(keyword_pointer);
  expect_keyword(keyword_to);
  parse_type();
}

void parse_fp_section(void) {
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
}

void parse_formal_parameters(void) {
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
}

void parse_procedure_type(void) {
  expect_keyword(keyword_procedure);
  if (is_token(TOKEN_LPAREN)) {
    parse_formal_parameters();
  }
}

void parse_type(void) {
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
}

void parse_const_declaration(void) {
  parse_ident_def();
  expect_token(TOKEN_EQ);
  parse_expression();
}

void parse_type_declaration(void) {
  parse_ident_def();
  expect_token(TOKEN_EQ);
  parse_type();
}

void parse_var_declaration(void) {
  parse_ident_list();
  expect_token(TOKEN_COLON);
  parse_type();
}

void parse_procedure_body(void) {
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
}

void parse_procedure_heading(void) {
  expect_keyword(keyword_procedure);
  parse_ident_def();
  if (is_token(TOKEN_LPAREN)) {
    parse_formal_parameters();
  }
}
void parse_procedure_declaration(void) {
  parse_procedure_heading();
  expect_token(TOKEN_SEMI);
  parse_procedure_body();
  expect_identifier();
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
  while (is_keyword(keyword_procedure)) {
    parse_procedure_declaration();
    expect_token(TOKEN_SEMI);
  }
}

void parse_import(void) {
  const char *importName = expect_identifier();
  if (match_token(TOKEN_ASSIGN)) {
    const char *canonicalName = expect_identifier();
    printf("import %s as %s\n", canonicalName, importName);
  } else {
    printf("import %s\n", importName);
  }
}

void parse_import_list(void) {
  expect_keyword(keyword_import);
  parse_import();
  while (match_token(TOKEN_COMMA)) {
    parse_import();
  }
  expect_token(TOKEN_SEMI);
}

void parse_module(void) {
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
}

void parse_test(void) {
  init_stream("", "MODULE abc; IMPORT a, b := aliased, c, d; CONST k=1; END abc.");
  next_token();
  parse_module();
}
