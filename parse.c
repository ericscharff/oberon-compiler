void parse_statement_sequence(void) {
}

void parse_const_declaration(void) {
}

void parse_type_declaration(void) {
}

void parse_var_declaration(void) {
}

void parse_procedure_declaration(void) {
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
  init_stream("", "MODULE abc; IMPORT a, b := aliased, c, d; END abc.");
  next_token();
  parse_module();
}
