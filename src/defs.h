#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tokens
enum {
  T_PLUS,
  T_MINUS,
  T_ASTERISK,
  T_SLASH,
  T_INTLIT,
};

// token structure
struct token {
  int token;
  int intvalue;
};
