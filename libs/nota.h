#ifndef NOTA_H
#define NOTA_H

#include <stdio.h> 
#include <stdlib.h>
#include <strings.h>
#include "curso.h"

#define MAX_TOP 1000  /* máximo de notas a mostrar */

typedef struct Nota {
    int co_curso; 
    float nt_ger;
    float nt_es;
    struct Nota *next;
} Nota;

typedef struct {
    Nota *inicio;
    Nota *fim;
} ListaNota;

typedef struct {
    int co_curso;
    int co_ies;
    float nota;
} TopNota;


/* insere uma nota na linked list */
void inserirNota(ListaNota *lista, Nota n);

/* mostra as notas que pertencem a um curso */
void mostrarNotasCurso(ListaNota *lista, int co_curso);

/* mostra a média de notas de um curso */
void mostrarMediaNotasCurso(ListaNota *lista, int co_curso);

/* carrega as top notas */
void insereTopNota(TopNota top[], int n, TopNota nova);

/* mostra as top notas */
void mostrarTopNotas(ListaNota *lista, Curso *raiz, int n, int tipo);

#endif /* NOTA_H */