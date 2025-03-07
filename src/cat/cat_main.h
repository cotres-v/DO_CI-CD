#ifndef CAT_MAIN_H
#define CAT_MAIN_H

#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  bool numberNonBlank;
  bool end;
  bool number;
  bool squeeze;
  bool tab;
  bool nonPrinting;
} Flags;

Flags CatReadFlags(int argc, char *argv[]);
void CatSetTable(char *table[static 256]);
void CatSetEnd(char *table[static 256]);
void CatSetTab(char *table[static 256]);
void CatSetNonPritable(char *table[static 256]);
void CatFile(FILE *file, Flags flags, char *table[256], int *count);
void Cat(int argc, char *argv[], Flags flags, char *table[256], int *count);

#endif