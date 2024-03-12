#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tokens
enum {
  T_EOF,
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

// AST node types
enum {
  A_ADD,
  A_SUBTRACT,
  A_MULTIPLY,
  A_DIVIDE,
  A_INTLIT,
};

// AST structure
struct ASTnode {
  int op;
  struct ASTnode *left;
  struct ASTnode *right;
  int intvalue;
};
