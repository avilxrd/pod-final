#ifndef NOTA_H
#define NOTA_H

#include <stdio.h> 
#include <stdlib.h>
#include <strings.h>
#include "curso.h"

#define MAX_TOP 500000  /* máximo de notas a mostrar */

typedef struct {
    int co_curso; 
    float nt_ger;
    float nt_es;
} Nota;

typedef struct {
    Nota *vetor;
    int tamanho;
    int capacidade;
} VetorNotas;

typedef struct {
    int co_curso;
    int co_ies;
    float nota;
} TopNota;

/* funções do vetor dinâmico */
void inserirNota(VetorNotas *v, Nota n);
void ordenarNotas(VetorNotas *v);  
Nota *buscarNotaCurso(VetorNotas *v, int co_curso); 

/* funções que usam o acesso sequencial (nos dados ordenados) 
   apenas funções que tem que mostrar todos os dados       */
void mostrarNotasCurso(VetorNotas *v, int co_curso);
void mostrarMediaNotasCurso(VetorNotas *v, int co_curso);

/* funções do top n notas */
void insereTopNota(TopNota top[], int n, TopNota nova);
void mostrarTopNotas(VetorNotas *v, Curso *raiz, int n, int tipo);

#endif
