#include "curso.h"
#include "utils.h"

int altura(Curso *n) { return n ? n->altura : 0; }

int max(int a, int b) { return (a > b) ? a : b; }

Curso* rotacaoDireita(Curso *y) {
    Curso *x = y->esq;
    Curso *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

Curso* rotacaoEsquerda(Curso *x) {
    Curso *y = x->dir;
    Curso *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

int fatorBalanceamento(Curso *n) { return n ? altura(n->esq) - altura(n->dir) : 0; }

Curso* inserirCursoArv(Curso *raiz, Curso c) {
    int fb;

    if (raiz == NULL) {
        Curso *novo = (Curso*) malloc(sizeof(Curso));
        *novo = c;
        novo->esq = novo->dir = NULL;
        novo->altura = 1;
        return novo;
    }

    if      (c.co_curso < raiz->co_curso) raiz->esq = inserirCursoArv(raiz->esq, c);
    else if (c.co_curso > raiz->co_curso) raiz->dir = inserirCursoArv(raiz->dir, c);
    else return raiz;

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    fb = fatorBalanceamento(raiz);

    if (fb >  1 && c.co_curso < raiz->esq->co_curso) return rotacaoDireita(raiz);
    if (fb < -1 && c.co_curso > raiz->dir->co_curso) return rotacaoEsquerda(raiz);

    if (fb > 1 && c.co_curso > raiz->esq->co_curso) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
    if (fb < -1 && c.co_curso < raiz->dir->co_curso) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}


Curso* buscarCursoArv(Curso *raiz, int cod) {
    if (!raiz) return NULL;
    if (cod == raiz->co_curso) return raiz;
    if (cod <  raiz->co_curso) return buscarCursoArv(raiz->esq, cod);
    return buscarCursoArv(raiz->dir, cod);
}

void listarCursosArv(Curso *raiz, const char *tipo, int codigo) {
    if (!raiz) return;
    listarCursosArv(raiz->esq, tipo, codigo);
    
    if (strcmp(tipo,"ies")==0 && raiz->co_ies==codigo) {
        printf("\n%sAno%s: %d %sIES%s: %d %sUF%s: %d %sGrupo%s: %d %sCurso%s: %d ", 
                COLOR_YELLOW, COLOR_RESET, raiz->ano,
                COLOR_YELLOW, COLOR_RESET, raiz->co_ies, 
                COLOR_YELLOW, COLOR_RESET, raiz->co_uf,
                COLOR_YELLOW, COLOR_RESET, raiz->co_grupo, 
                COLOR_YELLOW, COLOR_RESET, raiz->co_curso 
            ); 
    } else if (strcmp(tipo,"uf")==0 && raiz->co_uf==codigo) {
        printf("\n%sAno%s: %d %sUF%s: %d %sIES%s: %d %sGrupo%s: %d %sCurso%s: %d ", 
                COLOR_YELLOW, COLOR_RESET, raiz->ano,
                COLOR_YELLOW, COLOR_RESET, raiz->co_uf,
                COLOR_YELLOW, COLOR_RESET, raiz->co_ies, 
                COLOR_YELLOW, COLOR_RESET, raiz->co_grupo, 
                COLOR_YELLOW, COLOR_RESET, raiz->co_curso 
            ); 
    } else if (strcmp(tipo,"grupo")==0 && raiz->co_grupo==codigo) {
        printf("\n%sAno%s: %d %sGrupo%s: %d %sUF%s: %d %sIES%s: %d %sCurso%s: %d ", 
                COLOR_YELLOW, COLOR_RESET, raiz->ano,
                COLOR_YELLOW, COLOR_RESET, raiz->co_grupo, 
                COLOR_YELLOW, COLOR_RESET, raiz->co_uf,
                COLOR_YELLOW, COLOR_RESET, raiz->co_ies, 
                COLOR_YELLOW, COLOR_RESET, raiz->co_curso 
            ); 
    }

    listarCursosArv(raiz->dir, tipo, codigo);
}