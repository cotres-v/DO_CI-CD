#include "cat_main.h"

int main(int argc, char *argv[]) {
  Flags flags = CatReadFlags(argc, argv);
  char *table[256];
  int count_str = 1;
  CatSetTable(table);
  if (flags.end) CatSetEnd(table);
  if (flags.tab) CatSetTab(table);
  if (flags.nonPrinting) CatSetNonPritable(table);
  Cat(argc, argv, flags, table, &count_str);
  return 0;
}