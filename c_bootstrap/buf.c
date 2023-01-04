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

// Stretchy buffers from github/pervognsen/bitwise

// Stretchy buffers, invented (?) by Sean Barrett

typedef struct BufHdr {
  size_t len;
  size_t cap;
  char buf[];
} BufHdr;

#define MIN(x, y) ((x) <= (y) ? (x) : (y))
#define MAX(x, y) ((x) >= (y) ? (x) : (y))
#define CLAMP_MIN(x, min) MAX(x, min)
#define CLAMP_MAX(x, max) MIN(x, max)

#define buf__hdr(b) ((BufHdr *)((char *)(b)-offsetof(BufHdr, buf)))

#define buf_len(b) ((b) ? buf__hdr(b)->len : 0)
#define buf_cap(b) ((b) ? buf__hdr(b)->cap : 0)
#define buf_end(b) ((b) + buf_len(b))
#define buf_sizeof(b) ((b) ? buf_len(b) * sizeof(*b) : 0)

#define buf_free(b) ((b) ? (free(buf__hdr(b)), (b) = NULL) : 0)
#define buf_fit(b, n) \
  ((n) <= buf_cap(b) ? 0 : ((b) = buf__grow((b), (n), sizeof(*(b)))))
#define buf_push(b, ...) \
  (buf_fit((b), 1 + buf_len(b)), (b)[buf__hdr(b)->len++] = (__VA_ARGS__))
#define buf_printf(b, ...) ((b) = buf__printf((b), __VA_ARGS__))
#define buf_clear(b) ((b) ? buf__hdr(b)->len = 0 : 0)

void *xrealloc(void *ptr, size_t num_bytes) {
  ptr = realloc(ptr, num_bytes);
  if (!ptr) {
    perror("xrealloc failed");
    exit(1);
  }
  return ptr;
}

void *xmalloc(size_t num_bytes) {
  void *ptr = malloc(num_bytes);
  if (!ptr) {
    perror("xmalloc failed");
    exit(1);
  }
  return ptr;
}

void *buf__grow(const void *buf, size_t new_len, size_t elem_size) {
  assert(buf_cap(buf) <= (SIZE_MAX - 1) / 2);
  size_t new_cap = CLAMP_MIN(2 * buf_cap(buf), MAX(new_len, 16));
  assert(new_len <= new_cap);
  assert(new_cap <= (SIZE_MAX - offsetof(BufHdr, buf)) / elem_size);
  size_t new_size = offsetof(BufHdr, buf) + new_cap * elem_size;
  BufHdr *new_hdr;
  if (buf) {
    new_hdr = xrealloc(buf__hdr(buf), new_size);
  } else {
    new_hdr = xmalloc(new_size);
    new_hdr->len = 0;
  }
  new_hdr->cap = new_cap;
  return new_hdr->buf;
}

char *buf__printf(char *buf, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  size_t cap = buf_cap(buf) - buf_len(buf);
  size_t n = 1 + vsnprintf(buf_end(buf), cap, fmt, args);
  va_end(args);
  if (n > cap) {
    buf_fit(buf, n + buf_len(buf));
    va_start(args, fmt);
    size_t new_cap = buf_cap(buf) - buf_len(buf);
    n = 1 + vsnprintf(buf_end(buf), new_cap, fmt, args);
    assert(n <= new_cap);
    va_end(args);
  }
  buf__hdr(buf)->len += n - 1;
  return buf;
}

void buf_test(void) {
  int *buf = NULL;
  assert(buf_len(buf) == 0);
  size_t n = 1024;
  for (size_t i = 0; i < n; i++) {
    buf_push(buf, i);
  }
  assert(buf_len(buf) == n);
  for (size_t i = 0; i < buf_len(buf); i++) {
    assert(buf[i] == (int)i);
  }
  buf_free(buf);
  assert(buf == NULL);
  assert(buf_len(buf) == 0);
  char *str = NULL;
  buf_printf(str, "One: %d\n", 1);
  assert(strcmp(str, "One: 1\n") == 0);
  buf_printf(str, "Hex: 0x%x\n", 0x12345678);
  assert(strcmp(str, "One: 1\nHex: 0x12345678\n") == 0);
  buf_free(str);
  assert(str == NULL);
  printf("PASS: buf_test\n");
}
