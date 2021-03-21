#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT assert
#define oberon_abs(x) ((x) < 0) ? -(x) : (x)

#ifdef __cplusplus
#define oberon_buf_init(bbuf, bcap, btyp) \
    (bbuf).buf = new btyp[bcap]; \
    (bbuf).cap = (bcap); \
    (bbuf).len = 0;
#define oberon_buf_push(bbuf, val, btyp) \
    if ((bbuf).len == (bbuf).cap) { \
      btyp *newBuf = new btyp[(bbuf).cap*2]; \
      for (size_t i=0; i < (bbuf).len; i++) { \
        newBuf[i] = (bbuf).buf[i]; \
      } \
      delete (bbuf).buf; \
      (bbuf).buf = newBuf; \
      (bbuf).cap *= 2; \
    } \
    (bbuf).buf[(bbuf).len++] = val;
#else
#define oberon_buf_init(bbuf, bcap, btyp) \
    (bbuf).buf = malloc(sizeof(btyp)*bcap); \
    (bbuf).cap = (bcap); \
    (bbuf).len = 0;
#define oberon_buf_push(bbuf, val, btyp) \
    if ((bbuf).len == (bbuf).cap) { \
      btyp *newBuf = malloc(sizeof(btyp)*(bbuf).cap*2); \
      for (size_t i=0; i < (bbuf).len; i++) { \
        newBuf[i] = (bbuf).buf[i]; \
      } \
      free((bbuf).buf); \
      (bbuf).buf = newBuf; \
      (bbuf).cap *= 2; \
    } \
    (bbuf).buf[(bbuf).len++] = val;
#endif

int checkbounds(int i, int len) {
  assert(i >= 0 && i < len);
  return i;
}

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

void Out_Char(char c) {
  if (!Out_muted) {
    putchar(c);
  }
}

void Out_Str(const char *s, size_t q) {
  (void)q;
  if (!Out_muted) {
    fputs(s, stdout);
  }
}

void Out_StrI(const char *s, size_t q, int offset) {
  (void)q;
  if (!Out_muted) {
    fputs(s + offset, stdout);
  }
}

void Out_Ln(void) {
  if (!Out_muted) {
    puts("");
  }
}

void Out_ErrInt(int i) {
  if (!Out_muted) {
    fprintf(stderr, "%d", i);
  }
}

void Out_ErrReal(float r) {
  if (!Out_muted) {
    fprintf(stderr, "%g", r);
  }
}

void Out_ErrChar(char c) {
  if (!Out_muted) {
    fputc(c, stderr);
  }
}

void Out_ErrStr(const char *s, size_t q) {
  (void)q;
  if (!Out_muted) {
    fputs(s, stderr);
  }
}

void Out_ErrStrI(const char *s, size_t q, int offset) {
  (void)q;
  if (!Out_muted) {
    fputs(s + offset, stderr);
  }
}

void Out_ErrLn(void) {
  if (!Out_muted) {
    fputs("", stderr);
  }
}

void Out_Mute(void) { Out_muted = true; }

void Out_Unmute(void) { Out_muted = false; }

void Out_ReadFile(const char *fileName, size_t q, char *buf, size_t r) {
  (void)q;
  (void)r;
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

void Out_Halt(void) { exit(1); }

int saved_argc;
const char **saved_argv;

void InitArgs(int argc, const char **argv) {
  saved_argc = argc;
  saved_argv = argv;
}

int Args_Count(void) {
  return saved_argc;
}

void Args_GetArg(char *s, size_t sLen, int arg) {
  assert(arg >= 0);
  assert(arg < saved_argc);
  assert(strlen(saved_argv[arg]) < sLen);
  strncpy(s, saved_argv[arg], sLen);
}

typedef struct LangExtensionsTest_NatBuf_Native {
  int nativeQ;
  int nativeR;
} LangExtensionsTest_NatBuf_Native;

typedef struct LangExtensionsTest_NatBuf LangExtensionsTest_NatBuf;

void LangExtensionsTest_SetNativeVal(LangExtensionsTest_NatBuf *b, int val) {
  ((LangExtensionsTest_NatBuf_Native*)b)->nativeQ = val;
  ((LangExtensionsTest_NatBuf_Native*)b)->nativeR = val + 1;
}

void LangExtensionsTest_CallNative(LangExtensionsTest_NatBuf *b) {
  printf("Native code called, buf was %p.\n", (void*)b);

  LangExtensionsTest_NatBuf_Native* nat = (LangExtensionsTest_NatBuf_Native*)b;
  printf("Native code called, buf.nativeQ = %d, nativeR = %d.\n", nat->nativeQ, nat->nativeR);
}
