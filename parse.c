void parse_statement_sequence(void) {
}

void parse_declaration_sequence(void) {
}

void parse_import_list(void) {
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
  init_stream("", "MODULE abc; END abc.");
  next_token();
  parse_module();
}
