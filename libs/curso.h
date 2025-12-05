#ifndef CURSO_H
#define CURSO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Curso {
    int ano;
    int co_curso;
    int co_ies;
    int co_grupo;
    int co_uf;
    struct Curso *esq;
    struct Curso *dir;
} Curso;


/* aloca um novo nó para um curso lido no arquivo
   e insere na BST                             */
Curso* inserirCursoArv(Curso *raiz, Curso c);

/* busca um curso na árvore */
Curso* buscarCursoArv(Curso *raiz, int cod);

/* lista os cursos da árvore */
void listarCursosArv(Curso *raiz, const char *tipo, int codigo);

#endif /* CURSO_H */