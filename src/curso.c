#include "curso.h"
#include "utils.h"

Curso* inserirCursoArv(Curso *raiz, Curso c) {
    if (raiz == NULL) {
        Curso *novo = (Curso*) malloc(sizeof(Curso));

        if (!novo) {
            printf("Erro de memoria\n");
            exit(1);
        }
        
        *novo = c;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (c.co_curso < raiz->co_curso)      { raiz->esq = inserirCursoArv(raiz->esq, c); } 
    else if (c.co_curso > raiz->co_curso) { raiz->dir = inserirCursoArv(raiz->dir, c); }
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
    if ((strcmp(tipo,"ies")==0 && raiz->co_ies==codigo) ||
        (strcmp(tipo,"uf")==0 && raiz->co_uf==codigo)   ||
        (strcmp(tipo,"grupo")==0 && raiz->co_grupo==codigo)) { 
            printf("\n%sCurso%s: %d %sIES%s: %d %sGrupo%s: %d %sUF%s: %d %sAno%s: %d", 
                COLOR_YELLOW, COLOR_RESET, raiz->co_curso, 
                COLOR_YELLOW, COLOR_RESET, raiz->co_ies, 
                COLOR_YELLOW, COLOR_RESET, raiz->co_grupo, 
                COLOR_YELLOW, COLOR_RESET, raiz->co_uf, 
                COLOR_YELLOW, COLOR_RESET, raiz->ano); 
        }

    listarCursosArv(raiz->dir, tipo, codigo);
}