#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "lex.c"
#include "parse.c"

void run_tests(void) {
  lex_test();
  parse_test();
}

int main(void) {
  init_string_pool();
  run_tests();
  return 0;
}
