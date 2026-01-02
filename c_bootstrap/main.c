/*
 * This file is part of oberon-compiler
 *
 * Copyright (C) 2018-2026  Eric Scharff
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
#include "type.c"
#include "ast.c"
#include "parse.c"
#include "resolve.c"
#include "c_codegen.c"

void run_tests(void) {
  buf_test();
  lex_test();
  type_test();
  ast_test();
  parse_test();
  resolve_test();
  gen_test();
}

int main(void) {
  init_string_pool();
  init_builtin_types();
  run_tests();
  return 0;
}
