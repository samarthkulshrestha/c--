#define NOBUILD_IMPLEMENTATION
#include "./nob.h"

#define CFLAGS "-Wall", "-Wextra", "-std=c11", "-ggdb", "-pedantic"
// #define LD "-lm", "-lz"

void build(const char *m) {
  Cstr m_path = PATH("src", m);
  // CMD("cc", CFLAGS, "-o", CONCAT("./target/", NOEXT(m)), m_path);
  CMD("cc", "-o", CONCAT("./target/", NOEXT(m)), m_path, "src/scan.c");
}

int main(int argc, char **argv) {
  GO_REBUILD_URSELF(argc, argv);

  build("main.c");

  return 0;
}
