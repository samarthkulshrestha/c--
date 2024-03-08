#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>

static void init() {
  Line = 1;
  Putback = '\n';
}

static void usage(char *prog) {
  fprintf(stderr, "usage: %s <input_file>\n", prog);
  exit(1);
}

char *tokstr[] = {"+", "-", "*", "/", "intlit"};

static void scanfile() {
  struct token T;

  while (scan(&T)) {
    printf("token: %s", tokstr[T.token]);
    if (T.token == T_INTLIT) {
      printf(", value: %d", T.intvalue);
    }
    printf("\n");
  }
}

void main(int argc, char *argv[]) {
  if (argc != 2) {
    usage(argv[0]);
  }

  init();

  if ((Infile = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "unable to open %s: %s\n", argv[1], strerror(errno));
  }

  scanfile();
  exit(0);
}
