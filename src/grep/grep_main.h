#define _GNU_SOURCE  // для getline
#include <errno.h>
#include <getopt.h>
#include <regex.h>  //регулярные выражения
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool e_pattern;    //-e шаблон
  bool i_noRegistr;  // i - игнорирует регистр шаблона
  bool v_invert;  // -v показывает строки без совпадения с шаблоном
  bool c_count;  // -c выводит количество совпадающих строк. Если файлов > 1 -
                 // выводит имена файлов
  bool l_filesMatch;  // -l выводит имена файлов где обнаружены совпадения
  bool n_numberLine;  // -n выводит номера строк c совпадениями
  bool h_noFilename;  // -h вывод строк без имени файла
  bool s_noWarning;  // -s не пишет ошибки если нет файла
  bool f_file;  // -f file Ищет выражения из файла 1 в файле 2
  bool o_onlyMatches;  // -o печатает только совпадения
  int pattern_flags;  // поле для хранение флагов паттерна
} Flags;

Flags GrepReadFlags(int argc, char *argv[]);
void GrepFlag_c(FILE *file, char *filename, int count_f, Flags flags,
                regex_t *preg);
void GrepFlag_l(FILE *file, Flags flags, char *filename, regex_t *preg);
void GrepFlag_n(FILE *file, char *filename, Flags flags, regex_t *preg,
                int count_f);
void GrepFlag_h(FILE *file, Flags flags, regex_t *preg);
void GrepFlag_o(FILE *file, char *filename, Flags flags, regex_t *preg,
                int count_f);
void GrepFile(FILE *file, char *filename, Flags flags, regex_t *preg,
              int files_count);
void GrepFlag_fFile(int argc, FILE *f, char *filename, char *argv[],
                    Flags flags, int count_f);
void Grep(int argc, char *argv[], Flags flags);
void GrepFlags(int argc, char *argv[], Flags flags);
