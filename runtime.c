#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT assert
#define oberon_abs(x) ((x) < 0) ? -(x) : (x)

// Does the runtime type of a extend b
bool does_type_extend(oberon_typeid a, oberon_typeid b) {
  while (a) {
    if (a == b) {
      return true;
    }
    a = oberon_typeinfos[a];
  }
  return false;
}

int make_set_range(int s, int e) {
  int r = 0;
  while (s <= e) {
    r |= 1 << s;
    s++;
  }
  return r;
}

float FLT(int x) { return x; }

static bool Out_muted = false;

void Out_Int(int i) {
  if (!Out_muted) {
    printf("%d", i);
  }
}

void Out_Real(float r) {
  if (!Out_muted) {
    printf("%g", r);
  }
}

void Out_Str(const char *s) {
  if (!Out_muted) {
    fputs(s, stdout);
  }
}

void Out_StrI(const char *s, int offset) {
  if (!Out_muted) {
    fputs(s + offset, stdout);
  }
}

void Out_Ln(void) {
  if (!Out_muted) {
    puts("");
  }
}

void Out_Mute(void) { Out_muted = true; }

void Out_Unmute(void) { Out_muted = false; }

void Out_ReadFile(const char *fileName, char *buf) {
  FILE *file = fopen(fileName, "rb");
  if (!file) {
    assert(0);
  }
  fseek(file, 0, SEEK_END);
  long len = ftell(file);
  fseek(file, 0, SEEK_SET);
  assert(len < 65535);
  if (len && fread(buf, len, 1, file) != 1) {
    fclose(file);
    free(buf);
    assert(0);
  }
  fclose(file);
  buf[len] = 0;
}
