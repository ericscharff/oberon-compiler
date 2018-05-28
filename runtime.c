#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT assert

int make_set_range(int s, int e) {
  int r = 0;
  while (s <= e) {
    r |= 1 << s;
    s++;
  }
  return r;
}

void Out_Int(int i) {
  printf("%d", i);
}

void Out_Str(const char *s) {
  fputs(s, stdout);
}

void Out_Ln(void) {
  puts("");
}
