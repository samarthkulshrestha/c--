#include "defs.h"
#include "data.h"
#include "decl.h"

// convert a token into an AST operation
int arithop(int tok) {
  switch (tok) {
    case T_PLUS:
      return (A_ADD);
    case T_MINUS:
      return (A_SUBTRACT);
    case T_ASTERISK:
      return (A_MULTIPLY);
    case T_SLASH:
      return (A_DIVIDE);
    default:
      fprintf(stderr, "unknown token in arithop() on line %d\n", Line);
      exit(1);
  }
}

// parse a primary factor and return an AST node
static struct ASTnode *primary(void) {
  struct ASTnode *n;

  switch (Token.token) {
    case T_INTLIT:
      n = mkastleaf(A_INTLIT, Token.intvalue);
      scan(&Token);
      return (n);
    default:
      fprintf(stderr, "syntax error on line: %d\n", Line);
      exit(1);
  }
}

// Return an AST tree whose root is a binary operator
struct ASTnode *binexpr(void) {
  struct ASTnode *n, *left, *right;
  int nodetype;
  left = primary();

  if (Token.token == T_EOF)
    return (left);

  nodetype = arithop(Token.token);
  scan(&Token);
  right = binexpr();
  n = mkastnode(nodetype, left, right, 0);
  return (n);
}
