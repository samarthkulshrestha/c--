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
      fprintf(stderr, "syntax error on line: %d, token: %d\n", Line, Token.token);
      exit(1);
  }
}

// operator precedence for each token
static int OpPrec[] = { 0, 10, 10, 20, 20, 0 };

// check that we have a binary operator and return its precedence.
static int op_precedence(int tokentype) {
  int prec = OpPrec[tokentype];
  if (prec == 0) {
    fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
    exit(1);
  }
  return (prec);
}

// return an AST tree whose root is a binary operator
struct ASTnode *binexpr(int ptp) {
    struct ASTnode *left, *right;
  int tokentype;

  left = primary();
  tokentype = Token.token;

  if (tokentype == T_EOF)
    return (left);

  while (op_precedence(tokentype) > ptp) {
    scan(&Token);
    right = binexpr(OpPrec[tokentype]);
    left = mkastnode(arithop(tokentype), left, right, 0);
    tokentype = Token.token;
    if (tokentype == T_EOF)
      return (left);
  }

  return (left);
}
