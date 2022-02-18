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
      for (INTEGER i=0; i < (bbuf).len; i++) { \
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
      for (INTEGER i=0; i < (bbuf).len; i++) { \
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

void Out_Int(int i) {
  printf("%d", i);
}

void Out_Real(float r) {
  printf("%f", r);
}

void Out_Char(char c) {
  putchar(c);
}

void Out_Str(const char *s, size_t q) {
  (void)q;
  fputs(s, stdout);
}

void Out_StrI(const char *s, size_t q, int offset) {
  (void)q;
  fputs(s + offset, stdout);
}

void Out_Ln(void) {
  puts("");
}

void Out_ErrInt(int i) {
  fprintf(stderr, "%d", i);
}

void Out_ErrReal(float r) {
  fprintf(stderr, "%g", r);
}

void Out_ErrChar(char c) {
  fputc(c, stderr);
}

void Out_ErrStr(const char *s, size_t q) {
  (void)q;
  fputs(s, stderr);
}

void Out_ErrStrI(const char *s, size_t q, int offset) {
  (void)q;
  fputs(s + offset, stderr);
}

void Out_ErrLn(void) {
  fputs("", stderr);
}

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
  assert(len < 69631);
  if (len && fread(buf, len, 1, file) != 1) {
    fclose(file);
    free(buf);
    assert(0);
  }
  fclose(file);
  buf[len] = 0;
}

void Out_Halt(void) { exit(1); }

int Out_RealAsInt(float f) {
  int i;
  memcpy(&i, &f, sizeof(i));
  return i;
}

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

typedef struct LangExtensions_NatBuf_Native {
  int nativeQ;
  int nativeR;
} LangExtensions_NatBuf_Native;

typedef struct LangExtensions_NatBuf LangExtensions_NatBuf;

typedef void (*LangExtensions_CallbackFuncNative)(int);

void LangExtensions_SetNativeVal(LangExtensions_NatBuf *b, int val) {
  ((LangExtensions_NatBuf_Native*)b)->nativeQ = val;
  ((LangExtensions_NatBuf_Native*)b)->nativeR = val + 1;
}

void LangExtensions_CallNative(LangExtensions_NatBuf *b) {
  LangExtensions_NatBuf_Native* nat = (LangExtensions_NatBuf_Native*)b;
  printf("Native code called, buf.nativeQ = %d, nativeR = %d.\n", nat->nativeQ, nat->nativeR);
}

void LangExtensions_NativeCallback(int i, LangExtensions_CallbackFuncNative f) {
  printf("About to call callback with i=%d.\n", i+1);
  f(i+1);
  printf("NativeCallback completed\n");
}
