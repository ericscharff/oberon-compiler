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
#include "parse.c"

void run_tests(void) {
  buf_test();
  lex_test();
  parse_test();
}

int main(void) {
  init_string_pool();
  run_tests();
  return 0;
}
