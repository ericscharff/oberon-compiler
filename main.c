#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "lex.c"

void run_tests(void) {
  lex_test();
}

int main(void) {
  run_tests();
  return 0;
}
