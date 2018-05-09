#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.c"
#include "buf.c"
#include "lex.c"
#include "parse.c"
#include "type.c"

void run_tests(void) {
  buf_test();
  lex_test();
  type_test();
  ast_test();
  parse_test();
}

int main(void) {
  init_string_pool();
  init_builtin_types();
  run_tests();
  return 0;
}
