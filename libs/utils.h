#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "curso.h"
#include "nota.h"

/* códigos ANSI de algumas cores para
   melhorar a visualização dos dados */
#define COLOR_RESET   "\033[0m"
#define COLOR_BLACK   "\033[30m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

/* apenas um print default de erro */
void throwMsgError(void);

/* lê o arquivo 1 com os microdados do ENADE e insere 
   em uma AVL tree                                 */
Curso* lerArq1(const char *nome);

/* lê o arquivo 1 com os microdados do ENADE, insere 
   em um vetor dinâmico e o ordena                 */
void lerArq3(VetorNotas *v, const char *nome);

#endif /* UTILS_H */