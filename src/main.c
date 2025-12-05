#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main() {
    Curso *raizCursos;
    ListaNota listaNotas;
    int opc;
    
    listaNotas.inicio = NULL;
    listaNotas.fim = NULL;
    system("clear || cls");

    printf("%s->%s lendo o %sarquivo 1%s e inserindo na %sBST%s...         ", COLOR_YELLOW, COLOR_WHITE, COLOR_GREEN, COLOR_WHITE, COLOR_GREEN, COLOR_WHITE);
    fflush(stdout);
    raizCursos = lerArq1("data/arq1.txt");
    printf("[%sOK%s]\n", COLOR_GREEN, COLOR_WHITE);


    printf("%s->%s lendo o %sarquivo 3%s e inserindo na %sLINKED LIST%s... ", COLOR_YELLOW, COLOR_WHITE, COLOR_GREEN, COLOR_WHITE, COLOR_GREEN, COLOR_WHITE);
    fflush(stdout);
    lerArq3(&listaNotas,"data/arq3.txt");
    printf("[%sOK%s]", COLOR_GREEN, COLOR_WHITE);

    for(;;) {
        int cod, ies, uf, grupo, n, t;
        Curso *c;

        printf("\n\n%sMenu%s:\n", COLOR_GREEN, COLOR_RESET);
        printf("\t[%s1%s] Buscar curso por codigo\n", COLOR_YELLOW, COLOR_RESET);
        printf("\t[%s2%s] Listar cursos por IES\n",   COLOR_YELLOW, COLOR_RESET);
        printf("\t[%s3%s] Listar cursos por UF\n",    COLOR_YELLOW, COLOR_RESET);
        printf("\t[%s4%s] Listar cursos por grupo\n", COLOR_YELLOW, COLOR_RESET);
        printf("\t[%s5%s] Top N maiores notas\n",     COLOR_YELLOW, COLOR_RESET);
        printf("\t[%s6%s] Media de um curso\n",       COLOR_YELLOW, COLOR_RESET);
        printf("\t[%s0%s] Sair\n",                    COLOR_RED,    COLOR_RESET);
        printf("\nEscolha opcao: ");
        if (scanf("%d",&opc)!=1) break;
        if (opc==0) break;

        if (opc==1) {
            printf("\n%s->%s Digite codigo do curso: ", COLOR_YELLOW, COLOR_WHITE);
            if (scanf("%d",&cod)!=1) break;
            c = buscarCursoArv(raizCursos,cod);
        
            if (c) {
                printf("Curso %d | IES %d | Grupo %d | UF %d | Ano %d\n", c->co_curso,c->co_ies,c->co_grupo,c->co_uf,c->ano);
                mostrarNotasCurso(&listaNotas,c->co_curso);
            } else printf("\n%sCurso nao encontrado%s\n", COLOR_RED, COLOR_WHITE);

        } else if (opc==2) {
            printf("Digite codigo da IES: "); if (scanf("%d",&ies)!=1) break;
            listarCursosArv(raizCursos,"ies",ies);
        } else if (opc==3) {
            printf("Digite codigo da UF: "); if (scanf("%d",&uf)!=1) break;
            listarCursosArv(raizCursos,"uf",uf);
        } else if (opc==4) {
            printf("Digite codigo do grupo: "); if (scanf("%d",&grupo)!=1) break;
            listarCursosArv(raizCursos,"grupo",grupo);
        } else if (opc==5) {
            printf("Quantas maiores notas mostrar? "); if (scanf("%d",&n)!=1) break;
            printf("Tipo de nota (1-geral,2-específica): "); if (scanf("%d",&t)!=1) break;
            mostrarTopNotas(&listaNotas,raizCursos,n,t);
        } else if (opc==6) {
            printf("Digite codigo do curso para media: "); if (scanf("%d",&cod)!=1) break;
            mostrarMediaNotasCurso(&listaNotas,cod);
        } else printf("Opcao invalida\n");
    }

    return 0;
}