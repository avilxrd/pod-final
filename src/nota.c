#include "nota.h"
#include "utils.h"

void inserirNota(VetorNotas *v, Nota n) {
    if (v->capacidade == 0) {
        v->capacidade = 1000;
        v->vetor = malloc(sizeof(Nota) * v->capacidade);
    }
    if (v->tamanho >= v->capacidade) {
        v->capacidade *= 2;
        v->vetor = realloc(v->vetor, sizeof(Nota) * v->capacidade);
    }
    v->vetor[v->tamanho++] = n;
}

static int cmpNotas(const void *a, const void *b) {
    Nota *x = (Nota*)a;
    Nota *y = (Nota*)b;
    return (x->co_curso - y->co_curso);
}

static int cmpNotasGerDesc(const void *a, const void *b) {
    float x = ((Nota*)a)->nt_ger;
    float y = ((Nota*)b)->nt_ger;

    if (x < y) return 1;
    if (x > y) return -1;
    return 0;
}

static int cmpNotasEsDesc(const void *a, const void *b) {
    float x = ((Nota*)a)->nt_es;
    float y = ((Nota*)b)->nt_es;

    if (x < y) return 1;
    if (x > y) return -1;
    return 0;
}

void ordenarNotas(VetorNotas *v) {
    qsort(v->vetor, v->tamanho, sizeof(Nota), cmpNotas);
}

static int cmpBusca(const void *chave, const void *elem) {
    int c = *(int*)chave;
    Nota *n = (Nota*)elem;
    return c - n->co_curso;
}

Nota *buscarNotaCurso(VetorNotas *v, int co_curso) {
    return bsearch(&co_curso, v->vetor, v->tamanho, sizeof(Nota), cmpBusca);
}

void mostrarNotasCurso(VetorNotas *v, int co_curso) {
    
    float somaGer = 0, somaEs = 0;
    int qtdGer = 0, qtdEs = 0;
    
    int encontrado = 0;
    int i;

    printf("\nNotas do curso %d:\n", co_curso);
    printf("%sObs: NT_GER = 0.00 e NT_ES = -1.00 quer dizer que o aluno não fez a prova!\nNão são contabilizadas na média!%s\n\n", COLOR_RED, COLOR_RESET);

    for (i = 0; i < v->tamanho; i++) {
        Nota *p = &v->vetor[i];
        if (p->co_curso == co_curso) {
            encontrado = 1;

            printf("%sNT_GER%s: %.2f \t %sNT_ES%s: %.2f\n", 
                COLOR_YELLOW, COLOR_RESET, p->nt_ger, 
                COLOR_YELLOW, COLOR_RESET, p->nt_es
            );

            if (p->nt_ger > 0) { somaGer += p->nt_ger; qtdGer++; }
            if (p->nt_es >= 0) { somaEs += p->nt_es; qtdEs++; }
        }
    }

    if (!encontrado) {
        printf("%sNenhuma nota encontrada para o curso %d%s\n", COLOR_RED, co_curso, COLOR_RESET);
        return;
    }

    if (qtdGer > 0) printf("\n%sNT_GER Média:%s %.2f\n", COLOR_GREEN, COLOR_RESET, somaGer / qtdGer);
    else            printf("%sNenhuma NT_GER válida encontrada%s\n", COLOR_RED, COLOR_RESET);

    if (qtdEs > 0)  printf("%sNT_ES  Média:%s %.2f\n", COLOR_GREEN, COLOR_RESET, somaEs / qtdEs);
    else            printf("%sNenhuma NT_ES válida encontrada%s\n", COLOR_RED, COLOR_RESET);
}

void mostrarMediaNotasCurso(VetorNotas *v, int co_curso) {
    float somaGer = 0, somaEs = 0;
    int qtdGer = 0, qtdEs = 0;
    int i;

    for (i = 0; i < v->tamanho; i++) {
        Nota *p = &v->vetor[i];
        if (p->co_curso == co_curso) {
            if (p->nt_ger > 0) { somaGer += p->nt_ger; qtdGer++; }
            if (p->nt_es >= 0) { somaEs += p->nt_es; qtdEs++; }
        }
    }

    if (qtdGer > 0) printf("\n%sNT_GER Média:%s %.2f\n", COLOR_GREEN, COLOR_RESET, somaGer / qtdGer);
    else            printf("%sNenhuma NT_GER válida%s\n", COLOR_RED, COLOR_RESET);

    if (qtdEs > 0)  printf("%sNT_ES  Média:%s %.2f\n", COLOR_GREEN, COLOR_RESET, somaEs / qtdEs);
    else            printf("%sNenhuma NT_ES válida%s\n", COLOR_RED, COLOR_RESET);
}

void insereTopNota(TopNota top[], int n, TopNota nova) {
    int i,j;
    for (i=0;i<n;i++) if (top[i].nota<nova.nota) break;
    if (i==n) return;
    for (j=n-1;j>i;j--) top[j]=top[j-1];
    top[i]=nova;
}

void mostrarTopNotas(VetorNotas *v, Curso *raiz, int n, int tipo) {
    int i;
    if (n > v->tamanho) n = v->tamanho;

    if (tipo == 1) qsort(v->vetor, v->tamanho, sizeof(Nota), cmpNotasGerDesc);
    else qsort(v->vetor, v->tamanho, sizeof(Nota), cmpNotasEsDesc);

    printf("\nTop %d maiores notas (%s):\n\n", n, (tipo == 1) ? "geral" : "específica");

    for (i = 0; i < n; i++) {
        Nota *p = &v->vetor[i];
        Curso *c = buscarCursoArv(raiz, p->co_curso);
        printf("%sNota%s: %.2f\t %sIES%s: %d\t %sCurso%s: %d\n", 
            COLOR_YELLOW, COLOR_RESET, (tipo == 1 ? p->nt_ger : p->nt_es), 
            COLOR_YELLOW, COLOR_RESET, c ? c->co_ies : 0, 
            COLOR_YELLOW, COLOR_RESET, p->co_curso
        );
    }
}

