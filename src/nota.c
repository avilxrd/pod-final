#include "nota.h"

void inserirNota(ListaNota *lista, Nota n) {
    Nota *novo = (Nota*) malloc(sizeof(Nota));
    if (!novo) {
        printf("Erro de memoria!\n");
        exit(1);
    }
    *novo = n;
    novo->next = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        lista->fim->next = novo;
        lista->fim = novo;
    }
}

void mostrarNotasCurso(ListaNota *lista, int co_curso) {
    Nota *p;
    float somaGer=0, somaEs=0;
    int qtd=0;
    printf("Notas do curso %d (NT_GER | NT_ES):\n", co_curso);
    p = lista->inicio;
    while (p) {
        if (p->co_curso == co_curso) {
            printf("%.2f | %.2f\n", p->nt_ger, p->nt_es);
            somaGer += p->nt_ger;
            somaEs += p->nt_es;
            qtd++;
        }
        p = p->next;
    }
    if (qtd>0) printf("Media: NT_GER=%.2f | NT_ES=%.2f\n", somaGer/qtd, somaEs/qtd);
    else printf("Nenhuma nota encontrada.\n");
}

void mostrarMediaNotasCurso(ListaNota *lista, int co_curso) {
    Nota *p;
    float somaGer=0, somaEs=0;
    int qtd=0;

    p = lista->inicio;
    while (p) {
        if (p->co_curso == co_curso) {
            somaGer += p->nt_ger;
            somaEs += p->nt_es;
            qtd++;
        }
        p = p->next;
    }

    if (qtd>0) printf("Media curso %d: NT_GER=%.2f | NT_ES=%.2f\n", co_curso, somaGer/qtd, somaEs/qtd);
    else printf("Nenhuma nota encontrada para o curso %d\n", co_curso);
}

void insereTopNota(TopNota top[], int n, TopNota nova) {
    int i,j;
    for (i=0;i<n;i++) if (top[i].nota<nova.nota) break;
    if (i==n) return;
    for (j=n-1;j>i;j--) top[j]=top[j-1];
    top[i]=nova;
}

void mostrarTopNotas(ListaNota *lista, Curso *raiz, int n, int tipo) {
    TopNota top[MAX_TOP];
    int i;
    Nota *p;
    Curso *c;

    if (n>MAX_TOP) n=MAX_TOP;

    for (i=0;i<n;i++) top[i].nota=-1.0f;

    p = lista->inicio;
    while (p) {
        TopNota t;
        t.co_curso = p->co_curso;
        t.nota = (tipo==1) ? p->nt_ger : p->nt_es;
        t.co_ies = 0;
        insereTopNota(top,n,t);
        p = p->next;
    }

    for (i=0;i<n;i++) {
        if (top[i].nota<0) continue;
        c = buscarCursoArv(raiz, top[i].co_curso);
        if (c) top[i].co_ies = c->co_ies;
    }

    printf("Top %d maiores notas (%s):\n", n, (tipo==1)?"geral":"específica");
    for (i=0;i<n;i++) {
        if (top[i].nota<0) continue;
        printf("Curso %d | IES %d | Nota %.2f\n", top[i].co_curso, top[i].co_ies, top[i].nota);
    }
}