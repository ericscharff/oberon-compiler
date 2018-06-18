#include <gmodule.h>

// Avoid dumb problems with const
#define G_HASH_INSERT(t, k, v) g_hash_table_insert(t, (void *)k, (void *)v)

typedef enum {
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
  TOKEN_IN,
  TOKEN_IS,
  TOKEN_OR,
  TOKEN_DIV,
  TOKEN_MOD,
  TOKEN_XOR,
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
  TOKEN_AS_SET_ELT,
  TOKEN_CASE_DOTDOT,
} TokenKind;

const char *token_kind_names[] = {
    [TOKEN_UNKNOWN] = "<unknown>",
    [TOKEN_EOF] = "<eof>",
    [TOKEN_IDENT] = "<ident>",
    [TOKEN_KEYWORD] = "<keyword>",
    [TOKEN_STRING] = "<string>",
    [TOKEN_INT] = "<integer number>",
    [TOKEN_REAL] = "<real number>",
    [TOKEN_PLUS] = "+",
    [TOKEN_MINUS] = "-",
    [TOKEN_STAR] = "*",
    [TOKEN_SLASH] = "/",
    [TOKEN_TILDE] = "~",
    [TOKEN_IN] = "IN",
    [TOKEN_IS] = "IN",
    [TOKEN_OR] = "OR",
    [TOKEN_DIV] = "DIV",
    [TOKEN_MOD] = "MOD",
    [TOKEN_XOR] = "XOR",
    [TOKEN_AMP] = "&",
    [TOKEN_DOT] = ".",
    [TOKEN_COMMA] = ",",
    [TOKEN_SEMI] = ";",
    [TOKEN_VBAR] = "|",
    [TOKEN_LPAREN] = "(",
    [TOKEN_RPAREN] = ")",
    [TOKEN_LBRACK] = "[",
    [TOKEN_RBRACK] = "]",
    [TOKEN_LBRACE] = "{",
    [TOKEN_RBRACE] = "}",
    [TOKEN_ASSIGN] = ":=",
    [TOKEN_CARET] = "^",
    [TOKEN_EQ] = "=",
    [TOKEN_POUND] = "#",
    [TOKEN_LT] = "<",
    [TOKEN_GT] = ">",
    [TOKEN_LTEQ] = "<=",
    [TOKEN_GTEQ] = ">=",
    [TOKEN_DOTDOT] = "..",
    [TOKEN_COLON] = ":",
    [TOKEN_AS_SET_ELT] = "AS_SET_ELEMENT",
    [TOKEN_CASE_DOTDOT] = "CASE_DOTDOT",
};

typedef struct Loc {
  const char *file_name;
  int line;
} Loc;

typedef struct Token {
  TokenKind kind;
  Loc pos;
  const char *sVal;
  int iVal;
  float rVal;
} Token;

#define STRING_POOL_SIZE 256 * 1024
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
const char *keyword_array;
const char *keyword_begin;
const char *keyword_by;
const char *keyword_case;
const char *keyword_const;
const char *keyword_div;
const char *keyword_do;
const char *keyword_else;
const char *keyword_elsif;
const char *keyword_end;
const char *keyword_false;
const char *keyword_for;
const char *keyword_if;
const char *keyword_import;
const char *keyword_in;
const char *keyword_is;
const char *keyword_mod;
const char *keyword_module;
const char *keyword_native;
const char *keyword_nil;
const char *keyword_of;
const char *keyword_or;
const char *keyword_pointer;
const char *keyword_procedure;
const char *keyword_record;
const char *keyword_repeat;
const char *keyword_return;
const char *keyword_then;
const char *keyword_to;
const char *keyword_true;
const char *keyword_type;
const char *keyword_until;
const char *keyword_var;
const char *keyword_while;
const char *keyword_xor;

// optional keywords in lower case
const char *lc_keyword_array;
const char *lc_keyword_begin;
const char *lc_keyword_by;
const char *lc_keyword_case;
const char *lc_keyword_const;
const char *lc_keyword_div;
const char *lc_keyword_do;
const char *lc_keyword_else;
const char *lc_keyword_elsif;
const char *lc_keyword_end;
const char *lc_keyword_false;
const char *lc_keyword_for;
const char *lc_keyword_if;
const char *lc_keyword_import;
const char *lc_keyword_in;
const char *lc_keyword_is;
const char *lc_keyword_mod;
const char *lc_keyword_module;
const char *lc_keyword_native;
const char *lc_keyword_nil;
const char *lc_keyword_of;
const char *lc_keyword_or;
const char *lc_keyword_pointer;
const char *lc_keyword_procedure;
const char *lc_keyword_record;
const char *lc_keyword_repeat;
const char *lc_keyword_return;
const char *lc_keyword_then;
const char *lc_keyword_to;
const char *lc_keyword_true;
const char *lc_keyword_type;
const char *lc_keyword_until;
const char *lc_keyword_var;
const char *lc_keyword_while;
const char *lc_keyword_xor;

// Builtin procedures
const char *builtin_abs;
const char *builtin_chr;
const char *builtin_dec;
const char *builtin_inc;
const char *builtin_new;
const char *builtin_ord;
const char *builtin_val;

const char *op_name(TokenKind kind) { return token_kind_names[kind]; }

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
  g_hash_table_add(string_map, (void *)target);
  return target;
}

const char *string_intern(const char *str) {
  return string_intern_range(str, str + strlen(str));
}

void init_keywords(void) {
  lower_to_upper_keywords = g_hash_table_new(g_str_hash, g_str_equal);

  keyword_array = string_intern("ARRAY");
  keyword_begin = string_intern("BEGIN");
  keyword_by = string_intern("BY");
  keyword_case = string_intern("CASE");
  keyword_const = string_intern("CONST");
  keyword_div = string_intern("DIV");
  keyword_do = string_intern("DO");
  keyword_else = string_intern("ELSE");
  keyword_elsif = string_intern("ELSIF");
  keyword_end = string_intern("END");
  keyword_false = string_intern("FALSE");
  keyword_for = string_intern("FOR");
  keyword_if = string_intern("IF");
  keyword_import = string_intern("IMPORT");
  keyword_in = string_intern("IN");
  keyword_is = string_intern("IS");
  keyword_mod = string_intern("MOD");
  keyword_module = string_intern("MODULE");
  keyword_native = string_intern("NATIVE");
  keyword_nil = string_intern("NIL");
  keyword_of = string_intern("OF");
  keyword_or = string_intern("OR");
  keyword_pointer = string_intern("POINTER");
  keyword_procedure = string_intern("PROCEDURE");
  keyword_record = string_intern("RECORD");
  keyword_repeat = string_intern("REPEAT");
  keyword_return = string_intern("RETURN");
  keyword_then = string_intern("THEN");
  keyword_to = string_intern("TO");
  keyword_true = string_intern("TRUE");
  keyword_type = string_intern("TYPE");
  keyword_until = string_intern("UNTIL");
  keyword_var = string_intern("VAR");
  keyword_while = string_intern("WHILE");
  keyword_xor = string_intern("XOR");

  // optional lower case keywords
  lc_keyword_array = string_intern("array");
  lc_keyword_begin = string_intern("begin");
  lc_keyword_by = string_intern("by");
  lc_keyword_case = string_intern("case");
  lc_keyword_const = string_intern("const");
  lc_keyword_div = string_intern("div");
  lc_keyword_do = string_intern("do");
  lc_keyword_else = string_intern("else");
  lc_keyword_elsif = string_intern("elsif");
  lc_keyword_end = string_intern("end");
  lc_keyword_false = string_intern("false");
  lc_keyword_for = string_intern("for");
  lc_keyword_if = string_intern("if");
  lc_keyword_import = string_intern("import");
  lc_keyword_in = string_intern("in");
  lc_keyword_is = string_intern("is");
  lc_keyword_mod = string_intern("mod");
  lc_keyword_module = string_intern("module");
  lc_keyword_native = string_intern("native");
  lc_keyword_nil = string_intern("nil");
  lc_keyword_of = string_intern("of");
  lc_keyword_or = string_intern("or");
  lc_keyword_pointer = string_intern("pointer");
  lc_keyword_procedure = string_intern("procedure");
  lc_keyword_record = string_intern("record");
  lc_keyword_repeat = string_intern("repeat");
  lc_keyword_return = string_intern("return");
  lc_keyword_then = string_intern("then");
  lc_keyword_to = string_intern("to");
  lc_keyword_true = string_intern("true");
  lc_keyword_type = string_intern("type");
  lc_keyword_until = string_intern("until");
  lc_keyword_var = string_intern("var");
  lc_keyword_while = string_intern("while");
  lc_keyword_xor = string_intern("xor");

  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_array, lc_keyword_array);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_begin, keyword_begin);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_by, keyword_by);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_case, keyword_case);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_const, keyword_const);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_div, keyword_div);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_do, keyword_do);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_else, keyword_else);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_elsif, keyword_elsif);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_end, keyword_end);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_false, keyword_false);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_for, keyword_for);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_if, keyword_if);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_import, keyword_import);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_in, keyword_in);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_is, keyword_is);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_mod, keyword_mod);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_module, keyword_module);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_native, keyword_native);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_nil, keyword_nil);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_of, keyword_of);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_or, keyword_or);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_pointer, keyword_pointer);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_procedure,
                keyword_procedure);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_record, keyword_record);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_repeat, keyword_repeat);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_return, keyword_return);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_then, keyword_then);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_to, keyword_to);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_true, keyword_true);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_type, keyword_type);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_until, keyword_until);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_var, keyword_var);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_while, keyword_while);
  G_HASH_INSERT(lower_to_upper_keywords, lc_keyword_xor, keyword_xor);

  builtin_abs = string_intern("ABS");
  builtin_chr = string_intern("CHR");
  builtin_dec = string_intern("DEC");
  builtin_inc = string_intern("INC");
  builtin_new = string_intern("NEW");
  builtin_ord = string_intern("ORD");
  builtin_val = string_intern("VAL");
}

void init_string_pool(void) {
  pool_current = string_pool;
  pool_end = pool_current + STRING_POOL_SIZE;
  string_map = g_hash_table_new(g_str_hash, g_str_equal);
  init_keywords();
}

void pool_test(void) {
  const char *s = "helloworldabcd";
  string_pool_insert(s, s + 5);
  string_pool_finish(s, s + 5);
  string_pool_insert(s + 5, s + 10);
  string_pool_finish(s + 5, s + 10);
  string_pool_insert(s + 10, s + 11);
  string_pool_finish(s + 10, s + 11);
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
  const char *one = string_intern_range(s, s + 3);
  assert(s != one);
}

void init_stream(const char *fileName, const char *buf) {
  stream = buf;
  token.kind = TOKEN_UNKNOWN;
  if (fileName) {
    token.pos.file_name = string_intern(fileName);
  } else {
    token.pos.file_name = NULL;
  }
  token.pos.line = 1;
}

FILE *find_file(const char *fileName) {
  char *oberonPath = getenv("OBERONPATH");
  if (!oberonPath) {
    fprintf(stderr, "OBERONPATH must be set!\n");
    exit(1);
  }
  char path[1024];
  strncpy(path, oberonPath, 1024);
  char buf[1024];
  char *elt = strtok(path, ":");
  while (elt) {
    snprintf(buf, sizeof(buf), "%s/%s", elt, fileName);
    FILE *f = fopen(buf, "rb");
    if (f) {
      return f;
    }
    elt = strtok(NULL, ":");
  }
  return NULL;
}

char *read_file(const char *path) {
  FILE *file = find_file(path);
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

void write_file(const char *path, const char *contents) {
  FILE *file = fopen(path, "wb");
  if (!file) {
    return;
  }
  if (fwrite(contents, strlen(contents), 1, file) != 1) {
    assert(0);
  }
  fclose(file);
}

void error(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  printf("%s:%d: error: ", token.pos.file_name, token.pos.line);
  vprintf(fmt, args);
  printf("\n");
  va_end(args);
  exit(1);
}

void errorloc(Loc loc, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  printf("%s:%d: error: ", loc.file_name, loc.line);
  vprintf(fmt, args);
  printf("\n");
  va_end(args);
  exit(1);
}

bool string_is_keyword(const char *s) {
  return (s >= keyword_array && s <= keyword_xor) ||
         (use_lowercase_keywords && s >= lc_keyword_array &&
          s <= lc_keyword_xor);
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
    // A few special case keywords that really are tokens
    if (token.sVal == keyword_in) {
      token.kind = TOKEN_IN;
    }
    if (token.sVal == keyword_is) {
      token.kind = TOKEN_IS;
    }
    if (token.sVal == keyword_or) {
      token.kind = TOKEN_OR;
    }
    if (token.sVal == keyword_div) {
      token.kind = TOKEN_DIV;
    }
    if (token.sVal == keyword_mod) {
      token.kind = TOKEN_MOD;
    }
    if (token.sVal == keyword_xor) {
      token.kind = TOKEN_XOR;
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
    } else if (*start == 'H' || *start <= 'h' || *start == 'X' ||
               *start == 'x') {
    } else {
      assert(0);
    }
    start++;
  }
  if (token.kind == TOKEN_STRING) {
    if (token.iVal > 255) {
      error("Character constant %d > 255", token.iVal);
    } else {
      char sVal[] = {token.iVal, 0};
      token.sVal = string_intern(sVal);
    }
  }
}

void scan_string(void) {
  assert(*stream == '"');
  stream++;
  int startLine = token.pos.line;
  const char *start = stream;
  while (*stream && *stream != '"') {
    if (*stream == '\n') {
      token.pos.line++;
    }
    stream++;
  }
  if (*stream != '"') {
    token.pos.line = startLine;
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
  int startLine = token.pos.line;
  bool found_end_token = false;
  while (*stream && stream[1] && !found_end_token) {
    found_end_token = stream[0] == '*' && stream[1] == ')';
    if (*stream == '\n') {
      token.pos.line++;
    }
    if (!found_end_token) {
      stream++;
    }
    if (stream[0] == '(' && stream[1] == '*') {
      scan_comment();
    }
  }
  if (found_end_token) {
    stream += 2;
  } else {
    token.pos.line = startLine;
    error("Unterminated comment");
  }
}

void next_token(void) {
  token.kind = TOKEN_UNKNOWN;
  while (token.kind == TOKEN_UNKNOWN) {
    switch (*stream) {
      case '\0':
        token.kind = TOKEN_EOF;
        break;
      case ' ':
      case '\n':
      case '\r':
      case '\t':
      case '\v':
        while (isspace(*stream)) {
          if (*stream++ == '\n') {
            token.pos.line++;
          }
        }
        break;
      case '_':
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
      case 'G':
      case 'H':
      case 'I':
      case 'J':
      case 'K':
      case 'L':
      case 'M':
      case 'N':
      case 'O':
      case 'P':
      case 'Q':
      case 'R':
      case 'S':
      case 'T':
      case 'U':
      case 'V':
      case 'W':
      case 'X':
      case 'Y':
      case 'Z':
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
      case 'g':
      case 'h':
      case 'i':
      case 'j':
      case 'k':
      case 'l':
      case 'm':
      case 'n':
      case 'o':
      case 'p':
      case 'q':
      case 'r':
      case 's':
      case 't':
      case 'u':
      case 'v':
      case 'w':
      case 'x':
      case 'y':
      case 'z':
        scan_identifier();
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        scan_number();
        break;
      case '"':
        scan_string();
        break;
      case '+':
        token.kind = TOKEN_PLUS;
        stream++;
        break;
      case '-':
        token.kind = TOKEN_MINUS;
        stream++;
        break;
      case '*':
        token.kind = TOKEN_STAR;
        stream++;
        break;
      case '/':
        token.kind = TOKEN_SLASH;
        stream++;
        break;
      case '~':
        token.kind = TOKEN_TILDE;
        stream++;
        break;
      case '&':
        token.kind = TOKEN_AMP;
        stream++;
        break;
      case '.':
        token.kind = TOKEN_DOT;
        stream++;
        if (*stream == '.') {
          token.kind = TOKEN_DOTDOT;
          stream++;
        }
        break;
      case ',':
        token.kind = TOKEN_COMMA;
        stream++;
        break;
      case ';':
        token.kind = TOKEN_SEMI;
        stream++;
        break;
      case '|':
        token.kind = TOKEN_VBAR;
        stream++;
        break;
      case '(':
        if (stream[1] == '*') {
          scan_comment();
        } else {
          token.kind = TOKEN_LPAREN;
          stream++;
        }
        break;
      case ')':
        token.kind = TOKEN_RPAREN;
        stream++;
        break;
      case '[':
        token.kind = TOKEN_LBRACK;
        stream++;
        break;
      case ']':
        token.kind = TOKEN_RBRACK;
        stream++;
        break;
      case '{':
        token.kind = TOKEN_LBRACE;
        stream++;
        break;
      case '}':
        token.kind = TOKEN_RBRACE;
        stream++;
        break;
      case ':':
        token.kind = TOKEN_COLON;
        stream++;
        if (*stream == '=') {
          token.kind = TOKEN_ASSIGN;
          stream++;
        }
        break;
      case '^':
        token.kind = TOKEN_CARET;
        stream++;
        break;
      case '=':
        token.kind = TOKEN_EQ;
        stream++;
        break;
      case '#':
        token.kind = TOKEN_POUND;
        stream++;
        break;
      case '<':
        token.kind = TOKEN_LT;
        stream++;
        if (*stream == '=') {
          token.kind = TOKEN_LTEQ;
          stream++;
        }
        break;
      case '>':
        token.kind = TOKEN_GT;
        stream++;
        if (*stream == '=') {
          token.kind = TOKEN_GTEQ;
          stream++;
        }
        break;
      default:
        error("Unexpected character $d", *stream);
        token.kind = TOKEN_EOF;
        break;
    }
  }
}

bool is_token(TokenKind kind) { return token.kind == kind; }

bool is_keyword(const char *name) {
  return token.kind == TOKEN_KEYWORD && token.sVal == name;
}

void expect_keyword(const char *name) {
  if (is_keyword(name)) {
    next_token();
  } else {
    error("Expected %s", name);
  }
}

void expect_token(TokenKind kind) {
  if (is_token(kind)) {
    next_token();
  } else {
    error("Expected %s, got %s", op_name(kind), op_name(token.kind));
  }
}

const char *expect_identifier(void) {
  const char *id = token.sVal;
  expect_token(TOKEN_IDENT);
  return id;
}

bool match_keyword(const char *name) {
  if (is_keyword(name)) {
    next_token();
    return true;
  } else {
    return false;
  }
}

bool match_token(TokenKind kind) {
  if (is_token(kind)) {
    next_token();
    return true;
  } else {
    return false;
  }
}

void assert_token_real(float expected) {
  next_token();
  assert(token.kind == TOKEN_REAL);
  assert(token.rVal == expected);
}

void assert_token_int(int expected) {
  next_token();
  assert(token.kind == TOKEN_INT);
  assert(token.iVal == expected);
}

void assert_token_string(const char *expected) {
  next_token();
  assert(token.kind == TOKEN_STRING);
  assert(strcmp(token.sVal, expected) == 0);
}

void assert_token_ident(const char *expected) {
  next_token();
  assert(token.kind == TOKEN_IDENT);
  assert(strcmp(token.sVal, expected) == 0);
}

void assert_token_keyword(const char *expected) {
  next_token();
  assert(token.kind == TOKEN_KEYWORD);
  assert(strcmp(token.sVal, expected) == 0);
}

void lex_test(void) {
  pool_test();
  init_stream("", "");
  next_token();
  assert(token.kind == TOKEN_EOF);
  next_token();
  assert(token.kind == TOKEN_EOF);
  init_stream("", "alpha          beta gamma");
  assert_token_ident("alpha");
  assert_token_ident("beta");
  assert_token_ident("gamma");
  next_token();
  assert(token.kind == TOKEN_EOF);
  init_stream("", "alpha   q912     beta gamma");
  assert_token_ident("alpha");
  init_stream("", "0 1 2 123 1234 0C000H 0C000h 0c000H 41X4");
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
  init_stream("", "45x 46x 47x 48x");
  assert_token_string("E");
  assert_token_string("F");
  assert_token_string("G");
  assert_token_string("H");
  init_stream("", "3.14 3.14E2 314.E-2");
  assert_token_real(3.14);
  assert_token_real(314);
  assert_token_real(3.14);
  init_stream("", "FOR REPEAT PROCEDURE");
  assert_token_keyword(keyword_for);
  assert(token.sVal == keyword_for);
  assert_token_keyword(keyword_repeat);
  assert_token_keyword(keyword_procedure);
  use_lowercase_keywords = true;
  init_stream("", "for repeat\n procedure");
  assert_token_keyword(keyword_for);
  assert(token.sVal == keyword_for);
  assert_token_keyword(keyword_repeat);
  assert_token_keyword(keyword_procedure);
  use_lowercase_keywords = false;
  init_stream("", "for repeat procedure");
  assert_token_ident("for");
  assert_token_ident("repeat");
  assert_token_ident("procedure");
  init_stream("", "a\"hello\n world\"b c");
  assert_token_ident("a");
  assert_token_string("hello\n world");
  assert_token_ident("b");
  assert(token.pos.line == 2);
  init_stream("", "\"hello\"\"world\"");
  assert_token_string("hello");
  assert_token_string("world");
  next_token();
  assert(token.kind == TOKEN_EOF);
  init_stream("", "alpha(*q912\n(* cool (**) *)\n   *)beta gamma");
  assert_token_ident("alpha");
  assert_token_ident("beta");
  assert(token.pos.line == 3);
  init_stream(
      "",
      "+ - * / ~ IN IS OR DIV MOD XOR & . , ; | ( ) [ ] { } := ^ = # < > "
      "<= >= .. 10..20");
  for (TokenKind k = TOKEN_PLUS; k <= TOKEN_DOTDOT; k++) {
    next_token();
    assert(token.kind == k);
  }
  assert_token_int(10);
  next_token();
  assert(token.kind == TOKEN_DOTDOT);
  assert_token_int(20);
  printf("PASS: lex_test\n");
}
