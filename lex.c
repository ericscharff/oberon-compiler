#include <gmodule.h>

// Avoid dumb problems with const
#define G_HASH_INSERT(t, k, v) g_hash_table_insert(t, (void*)k, (void*)v)


typedef enum TokenKind {
  TOKEN_UNKNOWN,
  TOKEN_EOF,
  TOKEN_IDENT,
  TOKEN_KEYWORD,
  TOKEN_STRING,
  TOKEN_INT,
  TOKEN_REAL,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,
  TOKEN_TILDE,
  TOKEN_AMP,
  TOKEN_DOT,
  TOKEN_COMMA,
  TOKEN_SEMI,
  TOKEN_VBAR,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_LBRACK,
  TOKEN_RBRACK,
  TOKEN_LBRACE,
  TOKEN_RBRACE,
  TOKEN_ASSIGN,
  TOKEN_CARET,
  TOKEN_EQ,
  TOKEN_POUND,
  TOKEN_LT,
  TOKEN_GT,
  TOKEN_LTEQ,
  TOKEN_GTEQ,
  TOKEN_DOTDOT,
  TOKEN_COLON,
} TokenKind;


typedef struct Token {
  TokenKind kind;
  int line;
  const char *sVal;
  int iVal;
  float rVal;
} Token;

#define STRING_POOL_SIZE 256*1024
char string_pool[STRING_POOL_SIZE];
char *pool_current;
char *pool_end;
GHashTable *string_map;
GHashTable *lower_to_upper_keywords;
const char *stream;
Token token;

// options
bool use_lowercase_keywords = false;

// Keywords
const char *array_keyword;
const char *begin_keyword;
const char *by_keyword;
const char *case_keyword;
const char *const_keyword;
const char *div_keyword;
const char *do_keyword;
const char *else_keyword;
const char *elsif_keyword;
const char *end_keyword;
const char *false_keyword;
const char *for_keyword;
const char *if_keyword;
const char *import_keyword;
const char *in_keyword;
const char *is_keyword;
const char *mod_keyword;
const char *module_keyword;
const char *nil_keyword;
const char *of_keyword;
const char *or_keyword;
const char *pointer_keyword;
const char *procedure_keyword;
const char *record_keyword;
const char *repeat_keyword;
const char *return_keyword;
const char *then_keyword;
const char *to_keyword;
const char *true_keyword;
const char *type_keyword;
const char *until_keyword;
const char *var_keyword;
const char *while_keyword;

// optional keywords in lower case
const char *lc_array_keyword;
const char *lc_begin_keyword;
const char *lc_by_keyword;
const char *lc_case_keyword;
const char *lc_const_keyword;
const char *lc_div_keyword;
const char *lc_do_keyword;
const char *lc_else_keyword;
const char *lc_elsif_keyword;
const char *lc_end_keyword;
const char *lc_false_keyword;
const char *lc_for_keyword;
const char *lc_if_keyword;
const char *lc_import_keyword;
const char *lc_in_keyword;
const char *lc_is_keyword;
const char *lc_mod_keyword;
const char *lc_module_keyword;
const char *lc_nil_keyword;
const char *lc_of_keyword;
const char *lc_or_keyword;
const char *lc_pointer_keyword;
const char *lc_procedure_keyword;
const char *lc_record_keyword;
const char *lc_repeat_keyword;
const char *lc_return_keyword;
const char *lc_then_keyword;
const char *lc_to_keyword;
const char *lc_true_keyword;
const char *lc_type_keyword;
const char *lc_until_keyword;
const char *lc_var_keyword;
const char *lc_while_keyword;

// Insert into pool
const char *string_pool_insert(const char *begin, const char *end) {
  size_t len = end - begin;
  if ((pool_current + len) >= pool_end) {
    assert(0);
  }
  strncpy(pool_current, begin, len);
  pool_current[len] = '\0';
  return pool_current;
}

void string_pool_finish(const char *begin, const char *end) {
  pool_current += end - begin + 1;
}

const char *string_intern_range(const char *begin, const char *end) {
  // put temp copy in hash table to null terminate
  const char *target = string_pool_insert(begin, end);
  if (g_hash_table_contains(string_map, target)) {
    return g_hash_table_lookup(string_map, target);
  }
  string_pool_finish(begin, end);
  g_hash_table_add(string_map, (void*)target);
  return target;
}

const char *string_intern(const char *str) {
  return string_intern_range(str, str+strlen(str));
}

void init_keywords(void) {
  lower_to_upper_keywords = g_hash_table_new(g_str_hash, g_str_equal);

  array_keyword = string_intern("ARRAY");
  begin_keyword = string_intern("BEGIN");
  by_keyword = string_intern("BY");
  case_keyword = string_intern("CASE");
  const_keyword = string_intern("CONST");
  div_keyword = string_intern("DIV");
  do_keyword = string_intern("DO");
  else_keyword = string_intern("ELSE");
  elsif_keyword = string_intern("ELSIF");
  end_keyword = string_intern("END");
  false_keyword = string_intern("FALSE");
  for_keyword = string_intern("FOR");
  if_keyword = string_intern("IF");
  import_keyword = string_intern("IMPORT");
  in_keyword = string_intern("IN");
  is_keyword = string_intern("IS");
  mod_keyword = string_intern("MOD");
  module_keyword = string_intern("MODULE");
  nil_keyword = string_intern("NIL");
  of_keyword = string_intern("OF");
  or_keyword = string_intern("OR");
  pointer_keyword = string_intern("POINTER");
  procedure_keyword = string_intern("PROCEDURE");
  record_keyword = string_intern("RECORD");
  repeat_keyword = string_intern("REPEAT");
  return_keyword = string_intern("RETURN");
  then_keyword = string_intern("THEN");
  to_keyword = string_intern("TO");
  true_keyword = string_intern("TRUE");
  type_keyword = string_intern("TYPE");
  until_keyword = string_intern("UNTIL");
  var_keyword = string_intern("VAR");
  while_keyword = string_intern("WHILE");

  // optional lower case keywords
  lc_array_keyword = string_intern("array");
  lc_begin_keyword = string_intern("begin");
  lc_by_keyword = string_intern("by");
  lc_case_keyword = string_intern("case");
  lc_const_keyword = string_intern("const");
  lc_div_keyword = string_intern("div");
  lc_do_keyword = string_intern("do");
  lc_else_keyword = string_intern("else");
  lc_elsif_keyword = string_intern("elsif");
  lc_end_keyword = string_intern("end");
  lc_false_keyword = string_intern("false");
  lc_for_keyword = string_intern("for");
  lc_if_keyword = string_intern("if");
  lc_import_keyword = string_intern("import");
  lc_in_keyword = string_intern("in");
  lc_is_keyword = string_intern("is");
  lc_mod_keyword = string_intern("mod");
  lc_module_keyword = string_intern("module");
  lc_nil_keyword = string_intern("nil");
  lc_of_keyword = string_intern("of");
  lc_or_keyword = string_intern("or");
  lc_pointer_keyword = string_intern("pointer");
  lc_procedure_keyword = string_intern("procedure");
  lc_record_keyword = string_intern("record");
  lc_repeat_keyword = string_intern("repeat");
  lc_return_keyword = string_intern("return");
  lc_then_keyword = string_intern("then");
  lc_to_keyword = string_intern("to");
  lc_true_keyword = string_intern("true");
  lc_type_keyword = string_intern("type");
  lc_until_keyword = string_intern("until");
  lc_var_keyword = string_intern("var");
  lc_while_keyword = string_intern("while");

  G_HASH_INSERT(lower_to_upper_keywords, lc_array_keyword, lc_array_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_begin_keyword, begin_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_by_keyword, by_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_case_keyword, case_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_const_keyword, const_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_div_keyword, div_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_do_keyword, do_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_else_keyword, else_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_elsif_keyword, elsif_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_end_keyword, end_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_false_keyword, false_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_for_keyword, for_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_if_keyword, if_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_import_keyword, import_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_in_keyword, in_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_is_keyword, is_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_mod_keyword, mod_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_module_keyword, module_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_nil_keyword, nil_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_of_keyword, of_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_or_keyword, or_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_pointer_keyword, pointer_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_procedure_keyword, procedure_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_record_keyword, record_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_repeat_keyword, repeat_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_return_keyword, return_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_then_keyword, then_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_to_keyword, to_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_true_keyword, true_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_type_keyword, type_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_until_keyword, until_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_var_keyword, var_keyword);
  G_HASH_INSERT(lower_to_upper_keywords, lc_while_keyword, while_keyword);
}

void init_string_pool(void) {
  pool_current = string_pool;
  pool_end = pool_current + STRING_POOL_SIZE;
  string_map = g_hash_table_new(g_str_hash, g_str_equal);
  init_keywords();
}

void pool_test(void) {
  const char *s = "helloworldabcd";
  string_pool_insert(s, s+5);
  string_pool_finish(s, s+5);
  string_pool_insert(s+5, s+10);
  string_pool_finish(s+5, s+10);
  string_pool_insert(s+10, s+11);
  string_pool_finish(s+10, s+11);
  assert(!g_hash_table_contains(string_map, "one"));
  string_intern("one");
  assert(g_hash_table_contains(string_map, "one"));
  string_intern("two");
  assert(g_hash_table_contains(string_map, "two"));
  string_intern("three");
  assert(g_hash_table_contains(string_map, "three"));
  string_intern("four");
  assert(g_hash_table_contains(string_map, "four"));
  s = "onetwothreefour";
  const char *one = string_intern_range(s, s+3);
  assert(s != one);
}

void init_stream(const char *buf) {
  stream = buf;
  token.kind = TOKEN_UNKNOWN;
  token.line = 1;
}

char *read_file(const char *path) {
  FILE *file = fopen(path, "rb");
  if (!file) {
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  long len = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *buf = malloc(len + 1);
  if (len && fread(buf, len, 1, file) != 1) {
    fclose(file);
    free(buf);
    return NULL;
  }
  fclose(file);
  buf[len] = 0;
  return buf;
}

void error(const char *str) {
  fprintf(stderr, "Error: %s at line %d, stream char '%c'.\n", str, token.line, *stream);
}

bool string_is_keyword(const char *s) {
  return (s >= array_keyword && s <= while_keyword) ||
    (use_lowercase_keywords && s >= lc_array_keyword && s <= lc_while_keyword);
}

void scan_identifier(void) {
  const char *start = stream;
  token.kind = TOKEN_IDENT;
  // Already did first letter, so letter or digit
  while (*stream && (isalnum(*stream) || *stream == '_')) {
    stream++;
  }
  token.sVal = string_intern_range(start, stream);
  if (string_is_keyword(token.sVal)) {
    token.kind = TOKEN_KEYWORD;
    if (use_lowercase_keywords) {
      token.sVal = g_hash_table_lookup(lower_to_upper_keywords, token.sVal);
    }
  }
}

void scan_number(void) {
  const char *start = stream;
  token.kind = TOKEN_INT;
  int base = 10;
  bool need_h_or_x = false;
  while ((*stream >= '0' && *stream <= '9') ||
      (*stream >= 'A' && *stream <= 'F') ||
      (*stream >= 'a' && *stream <= 'f')) {
    if ((*stream >= 'A' && *stream <= 'F') ||
      (*stream >= 'a' && *stream <= 'f')) {
      need_h_or_x = true;
    }
    stream++;
  }
  // Got letters and hex digits. Could be hex, char, or floating point
  if (*stream == 'X' || *stream == 'x') {
    token.kind = TOKEN_STRING;
    base = 16;
    need_h_or_x = false;
    stream++;
  } else if (*stream == 'H' || *stream == 'h') {
    base = 16;
    need_h_or_x = false;
    stream++;
  } else if (*stream == '.' && stream[1] != '.') {
    // Special case - 10..20 is 10 TOKEN_DOTDOT 20
    stream++;
    while (*stream >= '0' && *stream <= '9') {
      stream++;
    }
    if (*stream == 'e' || *stream == 'E') {
      stream++;
    }
    if (*stream == '-') {
      stream++;
    }
    while (*stream >= '0' && *stream <= '9') {
      stream++;
    }
    token.kind = TOKEN_REAL;
    token.rVal = strtod(start, NULL);
    return;
  } else if (need_h_or_x) {
    error("Hex digit must be followed by H or X");
  }
  token.iVal = 0;
  while (start != stream) {
    if (*start >= '0' && *start <= '9') {
      token.iVal = token.iVal * base + (*start - '0');
    } else if (*start >= 'A' && *start <= 'F') {
      token.iVal = token.iVal * base + (*start - 'A' + 10);
    } else if (*start >= 'a' && *start <= 'f') {
      token.iVal = token.iVal * base + (*start - 'a' + 10);
    } else if (*start == 'H' || *start <= 'h' ||
        *start == 'X' || *start == 'x') {
    } else {
      assert(0);
    }
    start++;
  }
  if (token.kind == TOKEN_STRING) {
    if (token.iVal > 255) {
      error("Character constant > 255");
    } else {
      char sVal[] = {token.iVal, 0};
      token.sVal = string_intern(sVal);
    }
  }
}

void scan_string(void) {
  assert(*stream == '"');
  stream++;
  int startLine = token.line;
  const char *start = stream;
  while (*stream && *stream != '"') {
    if (*stream == '\n') {
      token.line++;
    }
    stream++;
  }
  if (*stream != '"') {
    token.line = startLine;
    error("Unterminated \"");
  } else {
    token.kind = TOKEN_STRING;
    token.sVal = string_intern_range(start, stream);
    stream++;
  }
}

void scan_comment(void) {
  assert(stream[0] == '(' && stream[1] == '*');
  stream += 2;
  int startLine = token.line;
  while (*stream && stream[1] && (stream[0] != '*') && (stream[1] != ')')) {
    if (*stream == '\n') {
      token.line++;
    }
    stream++;
    if (stream[0] == '(' && stream[1] == '*') {
      scan_comment();
    }
  }
  if (stream[0] != '*' && stream[1] != ')') {
    token.line = startLine;
    error("Unterminated comment");
  }
  stream += 2;
}

void next_token(void) {
  token.kind = TOKEN_UNKNOWN;
  while (token.kind == TOKEN_UNKNOWN) {
    switch (*stream) {
    case '\0':
      token.kind = TOKEN_EOF;
      break;
    case ' ': case '\n': case '\r': case '\t': case '\v':
      while (isspace(*stream)) {
        if (*stream++ == '\n') {
          token.line++;
        }
      }
      break;
    case '_': case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
    case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm':
    case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't':
    case 'u': case 'v': case 'w': case 'x': case 'y': case 'z': case 'A':
    case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H':
    case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O':
    case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V':
    case 'W': case 'X': case 'Y': case 'Z':
      scan_identifier();
      break;
    case '0': case '1': case '2': case '3': case '4': case '5': case '6':
    case '7': case '8': case '9':
      scan_number();
      break;
    case '"':
      scan_string();
      break;
    case '+':
      token.kind = TOKEN_PLUS; stream++; break;
    case '-':
      token.kind = TOKEN_MINUS; stream++; break;
    case '*':
      token.kind = TOKEN_STAR; stream++; break;
    case '/':
      token.kind = TOKEN_SLASH; stream++; break;
    case '~':
      token.kind = TOKEN_TILDE; stream++; break;
    case '&':
      token.kind = TOKEN_AMP; stream++; break;
    case '.':
      token.kind = TOKEN_DOT; stream++;
      if (*stream == '.') { token.kind = TOKEN_DOTDOT; stream++; }
      break;
    case ',':
      token.kind = TOKEN_COMMA; stream++; break;
    case ';':
      token.kind = TOKEN_SEMI; stream++; break;
    case '|':
      token.kind = TOKEN_VBAR; stream++; break;
    case '(':
      if (stream[1] == '*') {
        scan_comment();
      } else {
        token.kind = TOKEN_LPAREN; stream++;
      }
      break;
    case ')':
      token.kind = TOKEN_RPAREN; stream++; break;
    case '[':
      token.kind = TOKEN_LBRACK; stream++; break;
    case ']':
      token.kind = TOKEN_RBRACK; stream++; break;
    case '{':
      token.kind = TOKEN_LBRACE; stream++; break;
    case '}':
      token.kind = TOKEN_RBRACE; stream++; break;
    case ':':
      token.kind = TOKEN_COLON; stream++;
      if (*stream == '=') { token.kind = TOKEN_ASSIGN; stream++; }
      break;
    case '^':
      token.kind = TOKEN_CARET; stream++; break;
    case '=':
      token.kind = TOKEN_EQ; stream++; break;
    case '#':
      token.kind = TOKEN_POUND; stream++; break;
    case '<':
      token.kind = TOKEN_LT; stream++;
      if (*stream == '=') { token.kind = TOKEN_LTEQ; stream++; }
      break;
    case '>':
      token.kind = TOKEN_GT; stream++;
      if (*stream == '=') { token.kind = TOKEN_GTEQ; stream++; }
      break;
    default:
      error("Unknown token");
      token.kind = TOKEN_EOF;
      break;
    }
  }
}

void assert_token_real(float expected) {
  next_token();
  assert(token.kind == TOKEN_REAL);
  printf("Checking real token %f against %f\n", token.rVal, expected);
  assert(token.rVal == expected);
}

void assert_token_int(int expected) {
  next_token();
  assert(token.kind == TOKEN_INT);
  printf("Checking int token %d against %d\n", token.iVal, expected);
  assert(token.iVal == expected);
}

void assert_token_string(const char *expected) {
  next_token();
  assert(token.kind == TOKEN_STRING);
  printf("Checking string token %s against %s\n", token.sVal, expected);
  assert(strcmp(token.sVal, expected) == 0);
}

void assert_token_ident(const char *expected) {
  next_token();
  assert(token.kind == TOKEN_IDENT);
  printf("Checking identifier token %s against %s\n", token.sVal, expected);
  assert(strcmp(token.sVal, expected) == 0);
}


void assert_token_keyword(const char *expected) {
  next_token();
  assert(token.kind == TOKEN_KEYWORD);
  printf("Checking keyword token %s against %s\n", token.sVal, expected);
  assert(strcmp(token.sVal, expected) == 0);
}


void lex_test_dump_file(const char *fileName) {
  printf("Parsing %s\n", fileName);
  char *contents = read_file(fileName);
  if (contents) {
    init_stream(contents);
    while (token.kind != TOKEN_EOF) {
      next_token();
      printf("%d\n", token.kind);
    }
    free(contents);
  }
  printf("Done.\n");
}

void lex_test(void) {
  pool_test();
  init_stream("");
  next_token();
  assert(token.kind == TOKEN_EOF);
  next_token();
  assert(token.kind == TOKEN_EOF);
  init_stream("alpha          beta gamma");
  assert_token_ident("alpha");
  assert_token_ident("beta");
  assert_token_ident("gamma");
  next_token();
  assert(token.kind == TOKEN_EOF);
  init_stream("alpha   q912     beta gamma");
  assert_token_ident("alpha");
  init_stream("0 1 2 123 1234 0C000H 0C000h 0c000H 41X4");
  assert_token_int(0);
  assert_token_int(1);
  assert_token_int(2);
  assert_token_int(123);
  assert_token_int(1234);
  assert_token_int(49152);
  assert_token_int(49152);
  assert_token_int(0xc000);
  assert_token_string("A");
  assert_token_int(4);
  init_stream("45x 46x 47x 48x");
  assert_token_string("E");
  assert_token_string("F");
  assert_token_string("G");
  assert_token_string("H");
  init_stream("3.14 3.14E2 314.E-2");
  assert_token_real(3.14);
  assert_token_real(314);
  assert_token_real(3.14);
  init_stream("FOR REPEAT PROCEDURE");
  assert_token_keyword(for_keyword);
  assert(token.sVal == for_keyword);
  assert_token_keyword(repeat_keyword);
  assert_token_keyword(procedure_keyword);
  use_lowercase_keywords = true;
  init_stream("for repeat\n procedure");
  assert_token_keyword(for_keyword);
  assert(token.sVal == for_keyword);
  assert_token_keyword(repeat_keyword);
  assert_token_keyword(procedure_keyword);
  use_lowercase_keywords = false;
  init_stream("for repeat procedure");
  assert_token_ident("for");
  assert_token_ident("repeat");
  assert_token_ident("procedure");
  init_stream("a\"hello\n world\"b c");
  assert_token_ident("a");
  assert_token_string("hello\n world");
  assert_token_ident("b");
  assert(token.line == 2);
  init_stream("\"hello\"\"world\"");
  assert_token_string("hello");
  assert_token_string("world");
  next_token();
  assert(token.kind == TOKEN_EOF);
  init_stream("alpha(*q912\n(* cool (**) *)\n   *)beta gamma");
  assert_token_ident("alpha");
  assert_token_ident("beta");
  assert(token.line == 3);
  init_stream("+ - * / ~ & . , ; | ( ) [ ] { } := ^ = # < > <= >= .. 10..20");
  for (TokenKind k = TOKEN_PLUS; k <= TOKEN_DOTDOT; k++) {
    next_token();
    assert(token.kind == k);
  }
  assert_token_int(10);
  next_token();
  assert(token.kind == TOKEN_DOTDOT);
  assert_token_int(20);
}
