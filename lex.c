typedef enum TokenKind {
  TOKEN_UNKNOWN,
  TOKEN_EOF,
  TOKEN_IDENT,
  TOKEN_KEYWORD,
  TOKEN_INT,
  TOKEN_STRING,
  TOKEN_FLOAT,
  TOKEN_CHAR,
} TokenKind;

const char *stream;

typedef struct Token {
  TokenKind kind;
  int line;
  const char *sVal;
  char cVal;
  int iVal;
  float fVal;
} Token;

Token token;

void init_stream(const char *buf) {
  stream = buf;
  token.kind = TOKEN_INT;
  token.line = 1;
}

void error(const char *str) {
  fprintf(stderr, "Error: %s at line %d, stream char '%c'.\n", str, token.line, *stream);
}

void scan_identifier(void) {
  token.sVal = stream;
  // Already did first letter, so letter or digit
  while (*stream && (isalnum(*stream) || *stream == '_')) {
    stream++;
  }
  printf("Found ident [%.*s]\n", stream - token.sVal, token.sVal);
  token.kind = TOKEN_IDENT;
}

void scan_number(void) {
  token.sVal = stream;
  token.kind = TOKEN_INT;
  int base = 10;
  bool need_h_or_x = false;
  while ((*stream >= '0' && *stream <= '9') ||
      (*stream >= 'A' && *stream <= 'F') ||
      (*stream >= 'a' && *stream <= 'f')) {
    if ((*stream >= 'A' && *stream <= 'F') ||
      (*stream >= 'a' && *stream <= 'f')) {
      base = 16;
      need_h_or_x = true;
    }
    stream++;
  }
  // Got letters and hex digits. Could be hex, char, or floating point
  if (*stream == 'X' || *stream == 'x') {
    token.kind = TOKEN_CHAR;
    base = 16;
    need_h_or_x = false;
    stream++;
  } else if (*stream == 'H' || *stream == 'h') {
    base = 16;
    need_h_or_x = false;
    stream++;
  } else if (*stream == '.') {
    // float
    assert(0);
  } else if (base == 16 && need_h_or_x) {
    error("Hex digit must be followed by H or X");
  }
  token.iVal = 0;
  while (token.sVal != stream) {
    if (*token.sVal >= '0' && *token.sVal <= '9') {
      token.iVal = token.iVal * base + (*token.sVal - '0');
    } else if (*token.sVal >= 'A' && *token.sVal <= 'F') {
      token.iVal = token.iVal * base + (*token.sVal - 'A' + 10);
    } else if (*token.sVal >= 'a' && *token.sVal <= 'f') {
      token.iVal = token.iVal * base + (*token.sVal - 'a' + 10);
    } else if (*token.sVal == 'H' || *token.sVal <= 'h' ||
        *token.sVal == 'X' || *token.sVal == 'x') {
    } else {
      assert(0);
    }
    token.sVal++;
  }
  if (token.kind == TOKEN_CHAR) {
    if (token.iVal > 255) {
      error("Character constant > 255");
    } else {
      token.cVal = token.iVal;
    }
  }
}


void next_token(void) {
  const char *start = stream;

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
    default:
      error("Unknown token");
      token.kind = TOKEN_EOF;
      break;
    }
  }
}

void assert_token_int(int expected) {
  next_token();
  assert(token.kind == TOKEN_INT);
  assert(token.iVal == expected);
}

void assert_token_char(char expected) {
  next_token();
  assert(token.kind == TOKEN_CHAR);
  assert(token.iVal == expected);
}

void lex_test(void) {
  init_stream("");
  next_token();
  assert(token.kind == TOKEN_EOF);
  next_token();
  assert(token.kind == TOKEN_EOF);
  init_stream("alpha          beta gamma");
  for (int i=0; i < 3; i++) {
    next_token();
    assert(token.kind == TOKEN_IDENT);
  }
  next_token();
  assert(token.kind == TOKEN_EOF);
  init_stream("alpha   q912     beta gamma");
  next_token();
  next_token();
  init_stream("0 1 2 123 1234 0C000H 0C000h 0c000H 41X4");
  assert_token_int(0);
  assert_token_int(1);
  assert_token_int(2);
  assert_token_int(123);
  assert_token_int(1234);
  assert_token_int(49152);
  assert_token_int(49152);
  assert_token_int(0xc000);
  assert_token_char('A');
  assert_token_int(4);
}
