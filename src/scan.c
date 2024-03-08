#include "data.h"
#include "defs.h"
#include "decl.h"

// get next char from input file
static int next(void) {
  int c;

  if (Putback) {
    c = Putback;
    Putback = 0;
    return c;
  }

  c = fgetc(Infile);
  if ('\n' == c) {
    Line++;
  }
  return c;
}

// put back unwanted char
static void putback(int c) { Putback = c; }

// skip whitespace, newlines, etc
static int skip(void) {
  int c;

  c = next();
  while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
    c = next();
  }
  return c;
}

// return position of char in str
static int chrpos(char *s, int c) {
  char *p;

  p = strchr(s, c);
  return (p ? p - s : -1);
}

// scan integer literals
static int scanint(int c) {
  int k, val = 0;

  while ((k = chrpos("0123456789", c)) >= 0) {
    val = val * 10 + k;
    c = next();
  }

  putback(c);
  return val;
}

// rudimentary lexical scanner
// returns 1 if token is valid; 0 if no tokens left
int scan(struct token *t) {
  int c;

  // skip whitespace
  c = skip();

  // determine token
  switch (c) {
  case EOF:
    return (0);
  case '+':
    t->token = T_PLUS;
    break;
  case '-':
    t->token = T_MINUS;
    break;
  case '*':
    t->token = T_ASTERISK;
    break;
  case '/':
    t->token = T_SLASH;
    break;
  default:
    if (isdigit(c)) {
      t->intvalue = scanint(c);
      t->token = T_INTLIT;
      break;
    }

    printf("unrecognised character '%c' on line: %d\n", c, Line);
    exit(1);
  }

  return (1);
}
