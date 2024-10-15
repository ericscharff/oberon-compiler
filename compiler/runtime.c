/*
 * This file is part of oberon-compiler
 *
 * Copyright (C) 2018-2023  Eric Scharff
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT assert
#define oberon_abs(x) ((x) < 0) ? -(x) : (x)

#ifndef OBERON_INTEGER
#define OBERON_INTEGER int
#endif

#ifndef OBERON_REAL
#define OBERON_REAL double
#endif

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

OBERON_REAL FLT(int x) { return x; }

void Out_Int(int i) {
  printf("%d", i);
}

void Out_Real(OBERON_REAL r) {
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

void Out_ErrReal(OBERON_REAL r) {
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

void Out_ReadFile(const char *fileName, size_t q, char *buf, int r) {
  (void)q;
  FILE *file = fopen(fileName, "rb");
  if (!file) {
    char errMsg[1024];
    snprintf(errMsg, 1024, "Error reading %s", fileName);;
    perror(errMsg);
    assert(0);
  }
  fseek(file, 0, SEEK_END);
  long len = ftell(file);
  fseek(file, 0, SEEK_SET);
  assert(len < 65535);
  assert(len <= r);
  if (len && fread(buf, len, 1, file) != 1) {
    fclose(file);
    free(buf);
    assert(0);
  }
  fclose(file);
  buf[len] = 0;
}

void Out_Halt(void) { exit(1); }

int Out_RealAsInt(OBERON_REAL d) {
  float f = d;
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
  OBERON_INTEGER nativeQ;
  OBERON_INTEGER nativeR;
} LangExtensions_NatBuf_Native;

typedef struct LangExtensions_NatBuf LangExtensions_NatBuf;

typedef void (*LangExtensions_CallbackFuncNative)(OBERON_INTEGER);

void LangExtensions_SetNativeVal(LangExtensions_NatBuf *b, OBERON_INTEGER val) {
  ((LangExtensions_NatBuf_Native*)b)->nativeQ = val;
  ((LangExtensions_NatBuf_Native*)b)->nativeR = val + 1;
}

void LangExtensions_CallNative(LangExtensions_NatBuf *b) {
  LangExtensions_NatBuf_Native* nat = (LangExtensions_NatBuf_Native*)b;
  printf("Native code called, buf.nativeQ = %d, nativeR = %d.\n", nat->nativeQ, nat->nativeR);
}

void LangExtensions_NativeCallback(OBERON_INTEGER i, LangExtensions_CallbackFuncNative f) {
  printf("About to call callback with i=%d.\n", i+1);
  f(i+1);
  printf("NativeCallback completed\n");
}
