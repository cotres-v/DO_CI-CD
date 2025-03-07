#include "grep_main.h"

Flags GrepReadFlags(int argc, char *argv[]) {
  Flags flags = {false, false, false, false, false, false,
                 false, false, false, false, 1};
  for (int currentFlag = getopt(argc, argv, "eivclnhsfo"); currentFlag != -1;
       currentFlag = getopt(argc, argv, "eivclnhsfo")) {
    switch (currentFlag) {
      case 'e':
        flags.e_pattern = true;
        break;
      case 'i':
        flags.i_noRegistr = true;  // передача  в regexec
        flags.pattern_flags |= REG_ICASE;
        break;
      case 'v':
        flags.v_invert = true;
        break;
      case 'c':
        flags.c_count = true;
        break;
      case 'l':
        flags.l_filesMatch = true;
        break;
      case 'n':
        flags.n_numberLine = true;
        break;
      case 'h':
        flags.h_noFilename = true;
        break;
      case 's':
        flags.s_noWarning = true;
        break;
      case 'f':
        flags.f_file = true;
        break;
      case 'o':
        flags.o_onlyMatches = true;
        break;
    }
  }
  return flags;
}

void GrepFlag_c(FILE *file, char *filename, int count_f, Flags flags,
                regex_t *preg) {
  char *line = NULL;
  size_t length = 0;
  int count = 0;
  while (getline(&line, &length, file) != -1) {
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
    if (!flags.v_invert) {
      if (!regexec(preg, line, 0, NULL, 0)) count++;
    } else {
      if (regexec(preg, line, 0, NULL, 0)) count++;
    }
  }
  free(line);
  if (count_f > 1)
    printf("%s:%d\n", filename, count);
  else
    printf("%d\n", count);
}

void GrepFlag_l(FILE *file, Flags flags, char *filename, regex_t *preg) {
  char *line = NULL;
  size_t length = 0;
  int count = 0;  // счетчик файлов
  regmatch_t match;
  while (getline(&line, &length, file) > 0) {
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
    if (flags.v_invert) {
      if (regexec(preg, line, 1, &match, 0)) {
        if (count < 1) {  // печатаем 1 раз
          printf("%s\n", filename);
          count++;
        }
      }
    } else {
      if (!regexec(preg, line, 1, &match, 0)) {
        if (count < 1) {
          printf("%s\n", filename);
          count++;
        }
      }
    }
  }
  free(line);
}

void GrepFlag_n(FILE *file, char *filename, Flags flags, regex_t *preg,
                int count_f) {
  char *line = NULL;
  size_t length = 0;
  int countLine = 0;  // номера строк
  regmatch_t match;
  while (getline(&line, &length, file) > 0) {
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
    countLine++;
    if (flags.v_invert) {
      if (regexec(preg, line, 1, &match, 0)) {
        if (count_f == 1)
          printf("%d:%s\n", countLine, line);
        else
          printf("%s:%d:%s\n", filename, countLine, line);
      }
    } else {
      if (!regexec(preg, line, 1, &match, 0)) {
        if (count_f == 1)
          printf("%d:%s\n", countLine, line);
        else
          printf("%s:%d:%s\n", filename, countLine, line);
      }
    }
  }
  free(line);
}

void GrepFlag_h(FILE *file, Flags flags, regex_t *preg) {
  char *line = NULL;
  size_t length = 0;
  regmatch_t match;
  while (getline(&line, &length, file) > 0) {
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
    if (flags.v_invert) {
      if (regexec(preg, line, 1, &match, 0)) printf("%s\n", line);
    } else {
      if (!regexec(preg, line, 1, &match, 0)) printf("%s\n", line);
    }
  }
  free(line);
}

void GrepFlag_o(FILE *file, char *filename, Flags flags, regex_t *preg,
                int count_f) {
  char *line = NULL;
  size_t length = 0;
  regmatch_t match;
  while (getline(&line, &length, file) > 0) {
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
    char *ptr = line;
    while (!flags.v_invert && !regexec(preg, ptr, 1, &match, 0)) {
      int start = match.rm_so;
      int end = match.rm_eo;
      if (count_f == 1) {
        printf("%.*s\n", end - start, ptr + start);
      } else {
        printf("%s:%.*s\n", filename, end - start, ptr + start);
      }
      ptr += end;
    }
    if (flags.v_invert && regexec(preg, line, 0, NULL, 0)) {
      if (count_f == 1) {
        printf("%s\n", line);
      } else {
        printf("%s:%s\n", filename, line);
      }
    }
  }
  free(line);
}

void GrepFile(FILE *file, char *filename, Flags flags, regex_t *preg,
              int files_count) {
  char *line = NULL;  // введение строки
  size_t length = 0;
  regmatch_t match;  // начало и конец строки совпадения строки с совпадением
  while (getline(&line, &length, file) > 0) {
    if (line[strlen(line) - 1] ==
        '\n')  // позиция символа будет на длине строки - 1,
      line[strlen(line) - 1] = '\0';
    if (flags.v_invert) {  // вывод с флагом -v (все кроме совпадений)
      if (files_count == 1) {
        if (regexec(preg, line, 1, &match,
                    0))  // проверка соотвествия строки и рег выражения
          printf("%s\n", line);
      } else {
        if (regexec(preg, line, 1, &match, 0))
          printf("%s:%s\n", filename, line);
      }
    } else {  // обычный вывод совпадений и тд
      if (files_count == 1) {
        if (!regexec(preg, line, 1, &match, 0)) printf("%s\n", line);
      } else {
        if (!regexec(preg, line, 1, &match, 0))
          printf("%s:%s\n", filename, line);
      }
    }
  }
  free(line);
}

void GrepFlag_fFile(int argc, FILE *f, char *filename, char *argv[],
                    Flags flags, int count_f) {
  char filenameF[100] = {""};
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0) strcpy(filenameF, argv[i + 1]);
  }
  FILE *filePattern;
  filePattern = fopen(filenameF, "r");
  if (filePattern != NULL) {
    char *patternFromFile = NULL;  // чтение строк из файла
    size_t length = 0, lengthf = 0;
    char patternsF[1024][1024];  // массив для хранения всех шаблонов
    int countPattern = 0;  // счетчик подсчета шаблонов
    while (getline(&patternFromFile, &lengthf, filePattern) > 0) {
      if (patternFromFile[strlen(patternFromFile) - 1] == '\n') {
        patternFromFile[strlen(patternFromFile) - 1] = '\0';
      }
      strcpy(patternsF[countPattern], patternFromFile);
      countPattern++;
    }
    free(patternFromFile);
    fclose(filePattern);
    char *line = NULL;
    while (getline(&line, &length, f) > 0) {
      bool check = false;  // без нее будет дублирование вывода
      if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
      for (int i = 0; i < countPattern && check == false; i++) {
        regex_t regex;
        regcomp(
            &regex, patternsF[i],
            flags.pattern_flags);  // условие ? значение_true : значение_false
        if (flags.v_invert ? regexec(&regex, line, 0, NULL, 0)
                           : !regexec(&regex, line, 0, NULL, 0)) {
          check = true;
          count_f == 1 ? printf("%s\n", line)
                       : printf("%s:%s\n", filename, line);
        }
        regfree(&regex);
      }
    }
    free(line);
  } else {
    if (!flags.s_noWarning)
      printf("grep: %s: No such file or directory\n", filenameF);
  }
}

void Grep(int argc, char *argv[], Flags flags) {
  char **pattern = &argv[1];
  char **end = &argv[argc];
  regex_t preg;
  int count_f = 0;
  for (; pattern != end && pattern[0][0] == '-';
       ++pattern)  // пропуск аргументов с -
    ;
  if (pattern == end) {
    if (!flags.s_noWarning)
      printf(
          "usage: grep [OPTION]... PATTERN [FILE]...\n");  // доработать ошибку
  } else {
    if (regcomp(&preg, *pattern,
                flags.pattern_flags)) {  // сохранение шаблона в preg
      if (!flags.s_noWarning)
        printf("failed to cimpile regex\n");  // доработать ошибку
    } else {
      for (char **filename = pattern + 1; filename != end; ++filename) {
        count_f++;  // подсчёт кол-ва файлов
      }
      for (char **filename = pattern + 1; filename != end; ++filename) {
        if (**filename != '-' && !flags.e_pattern) {
          FILE *file = fopen(*filename, "r");
          if (file == NULL) {
            if (!flags.s_noWarning) {
              printf("grep: %s: No such file or directory\n", *filename);
            }
          } else {
            if (flags.c_count)
              GrepFlag_c(file, *filename, count_f, flags, &preg);
            else if (flags.l_filesMatch)
              GrepFlag_l(file, flags, *filename, &preg);
            else if (flags.n_numberLine)
              GrepFlag_n(file, *filename, flags, &preg, count_f);
            else if (flags.h_noFilename)
              GrepFlag_h(file, flags, &preg);
            else if (flags.o_onlyMatches)
              GrepFlag_o(file, *filename, flags, &preg, count_f);
            else if (flags.f_file)
              GrepFlag_fFile(argc, file, *filename, argv, flags, count_f);
            else
              GrepFile(file, *filename, flags, &preg, count_f);
            fclose(file);
          }
        }
      }
    }
    regfree(&preg);
  }
}

void GrepFlags(int argc, char *argv[], Flags flags) {
  char filename[256][256],
      patternsE[256][256];  // массивы для хранения имен файлов и паттернов с
                            // флагом -е
  int count_P = 0, count_f = 0;  // кол-во паттернов и файлов
  for (int i = 0; i < argc; i++) {  // заполнение массив паттернов -е
    if (strcmp(argv[i], "-e") == 0) {
      strcpy(patternsE[count_P], argv[i] + 3);
      count_P++;
    }
  }
  for (int i = 1; i < argc; i++) {  // заполнение массива аргументами
    if (strcmp(argv[i], "-e") != 0 && strcmp(argv[i], "-v") != 0 &&
        strcmp(argv[i], "-ev") != 0 &&
        strcmp(argv[i], "-ve") != 0) {  // все кроме -e -v
      int check = 0;
      for (int j = 0; j < count_P; j++) {
        if (strcmp(argv[i], patternsE[j]) == 0) check = 1;
      }
      if (check == 0) {
        strcpy(filename[count_f], argv[i]);
        count_f++;
      }
    }
  }
  for (int j = 0; j < count_f; j++) {
    for (int h = 0; h < count_P; h++) {
      FILE *file;
      file = fopen(filename[j], "r");
      if (file != NULL) {
        regex_t preg;
        regcomp(&preg, patternsE[h], flags.pattern_flags);
        GrepFile(file, filename[j], flags, &preg, count_f);
        regfree(&preg);
        fclose(file);
      } else {
        if (!flags.s_noWarning)
          printf("grep: %s: No such file or directory\n", *filename);
      }
    }
  }
}