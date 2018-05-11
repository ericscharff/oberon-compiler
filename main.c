#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buf.c"
#include "lex.c"
#include "type.c"
#include "ast.c"
#include "parse.c"
#include "resolve.c"

void run_tests(void) {
  buf_test();
  lex_test();
  type_test();
  ast_test();
  parse_test();
  resolve_test();
}

int main(void) {
  init_string_pool();
  init_builtin_types();
  run_tests();
  return 0;
}
