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

void scan_identifier(void) {
  token.sVal = stream;
  // Already did first letter, so letter or digit
  while (*stream && (isalnum(*stream) || *stream == '_')) {
    stream++;
  }
  printf("Found ident [%.*s]\n", stream - token.sVal, token.sVal);
  token.kind = TOKEN_IDENT;
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
    }
  }
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
}
