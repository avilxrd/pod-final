#include "nota.h"
#include "utils.h"

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
    int qtdGer = 0, qtdEs = 0;

    printf("\nNotas do curso %d:\n", co_curso);
    printf("%sObs: NT_GER = 0.00 e NT_ES = -1.00 quer dizer que o aluno não fez a prova!\nNão são contabilizadas na média!%s\n\n", COLOR_RED, COLOR_RESET);
    p = lista->inicio;
    while (p) {
        if (p->co_curso == co_curso) {
            printf("%sNT_GER%s: %.2f \t %sNT_ES%s: %.2f\n", 
                COLOR_YELLOW, COLOR_RESET, p->nt_ger, 
                COLOR_YELLOW, COLOR_RESET, p->nt_es
            );
            
            if (p->nt_ger > 0.0f) {
                somaGer += p->nt_ger;
                qtdGer++;
            }

            if (p->nt_es >= 0.0f) {
                somaEs += p->nt_es;
                qtdEs++;
            }
        }
        p = p->next;
    }
    if (qtdGer > 0) printf("\n%sNT_GER Média:%s %.2f\n", COLOR_GREEN, COLOR_RESET, somaGer / qtdGer);
    else            printf("%sNenhuma NT_GER valida encontrada para o curso %d%s\n", COLOR_RED, co_curso, COLOR_RESET);
    if (qtdEs > 0)  printf("%sNT_ES  Média:%s %.2f\n", COLOR_GREEN, COLOR_RESET, somaEs / qtdEs);
    else            printf("%sNenhuma NT_ES valida encontrada para o curso %d%s\n", COLOR_RED, co_curso, COLOR_RESET);
}

void mostrarMediaNotasCurso(ListaNota *lista, int co_curso) {
    Nota *p;
    float somaGer = 0.0f, somaEs = 0.0f;
    int qtdGer = 0, qtdEs = 0;

    p = lista->inicio;

    while (p != NULL) {
        if (p->co_curso == co_curso) {

            if (p->nt_ger > 0.0f) {
                somaGer += p->nt_ger;
                qtdGer++;
            }

            if (p->nt_es >= 0.0f) {
                somaEs += p->nt_es;
                qtdEs++;
            }
        }

        p = p->next;
    }

    if (qtdGer > 0) printf("\n%sNT_GER Média:%s %.2f\n", COLOR_GREEN, COLOR_RESET, somaGer / qtdGer);
    else            printf("%sNenhuma NT_GER valida encontrada para o curso %d%s\n", COLOR_RED, co_curso, COLOR_RESET);
    if (qtdEs > 0)  printf("%sNT_ES  Média:%s %.2f\n", COLOR_GREEN, COLOR_RESET, somaEs / qtdEs);
    else            printf("%sNenhuma NT_ES valida encontrada para o curso %d%s\n", COLOR_RED, co_curso, COLOR_RESET);
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

    printf("\nTop %d maiores notas (%s):\n\n", n, (tipo==1)?"geral":"específica");
    for (i=0;i<n;i++) {
        if (top[i].nota<0) continue;
        printf("%sNota%s: %.2f\t %sIES%s: %d\t %sCurso%s: %d\n", 
            COLOR_YELLOW, COLOR_RESET, top[i].nota,
            COLOR_YELLOW, COLOR_RESET, top[i].co_ies, 
            COLOR_YELLOW, COLOR_RESET, top[i].co_curso
        );
    }
}