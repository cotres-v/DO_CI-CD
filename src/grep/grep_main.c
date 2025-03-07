#include "grep_main.h"

int main(int argc, char *argv[]) {
  Flags flags = GrepReadFlags(argc, argv);
  if (flags.e_pattern) {
    GrepFlags(argc, argv, flags);
  } else {
    Grep(argc, argv, flags);
  }
  return 0;
}