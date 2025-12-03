#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Curso {
    int ano;
    int co_curso;
    int co_ies;
    int co_grupo;
    int co_uf;
    struct Curso *next;
} Curso;

typedef struct Nota {
    int co_curso;
    float nt_ger;
    float nt_es;
    struct Nota *next;
} Nota;

typedef struct {
    Curso *inicio;
    Curso *fim;
} ListaCurso;

typedef struct {
    Nota *inicio;
    Nota *fim;
} ListaNota;

/* insere um novo curso na lista encadeada */
void inserirCurso(ListaCurso *lista, Curso c) {
    Curso *novo = (Curso*) malloc(sizeof(Curso));
    
    if (!novo) {
        printf("Erro de memoria\n");
        exit(1);
    }

    *novo = c;
    novo->next = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        lista->fim->next = novo;
        lista->fim = novo;
    }
}

/* insere uma nova nota na lista encadeada */
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

/* lê o arquivo 1 e insere os dados numa lista */
void lerArq1(ListaCurso *lista, const char *nome) {
    FILE *f = fopen(nome, "r");
    char linha[2048];
    Curso c;
    char *token;
    
    if (!f) {
        printf("Erro ao abrir %s\n", nome);
        exit(1);
    }

    fgets(linha, sizeof(linha), f); /* pula cabeçalho */

    while (fgets(linha, sizeof(linha), f)) {
        token = strtok(linha, ";"); c.ano = atoi(token);
        token = strtok(NULL, ";");  c.co_curso = atoi(token);
        token = strtok(NULL, ";");  c.co_ies = atoi(token);
        token = strtok(NULL, ";");  /* (ignorado) */
        token = strtok(NULL, ";");  /* (ignorado) */
        token = strtok(NULL, ";");  c.co_grupo = atoi(token);
        token = strtok(NULL, ";");  /* (ignorado) */
        token = strtok(NULL, ";");  /* (ignorado) */
        token = strtok(NULL, ";");  c.co_uf = atoi(token);

        inserirCurso(lista, c);
    }

    fclose(f);
}

/* lê o arquivo 3 e insere os dados numa lista */
void lerArq3(ListaNota *lista, const char *nome) {
    FILE *f = fopen(nome, "r");
    char linha[4096];
    Nota n;
    char *token;
    int i;
    
    if (!f) {
        printf("Erro ao abrir %s\n", nome);
        exit(1);
    }

    fgets(linha, sizeof(linha), f); /* pula cabeçalho */

    while (fgets(linha, sizeof(linha), f)) {
        token = strtok(linha, ";"); /* ano */
        token = strtok(NULL, ";");  n.co_curso = atoi(token);

        for (i = 0; i < 21; i++) token = strtok(NULL, ";"); /* pula alguns campos até o NT_GER */

        
        token = strtok(NULL, ";"); /* NT_GER */
        n.nt_ger = token ? atof(token) : -1.0f;

        for (i = 0; i < 7; i++) token = strtok(NULL, ";");

        token = strtok(NULL, ";"); /* NT_ES */
        n.nt_es = token ? atof(token) : -1.0f;

        inserirNota(lista, n);
    }

    fclose(f);
}

/* mostra todos os cursos da lista */
void mostrarCursos(Curso *l) {
    while (l) {
        printf("Curso %d | IES %d | Grupo %d | UF %d\n", l->co_curso, l->co_ies, l->co_grupo, l->co_uf);
        l = l->next;
    }
}

/* mostra todas as notas da lista */
void mostrarNotas(Nota *l) {
    while (l) {
        printf("Curso %d | NT_GER %.2f | NT_ES %.2f\n", l->co_curso, l->nt_ger, l->nt_es);
        l = l->next;
    }
}

int main() {

    ListaCurso listaCursos;
    ListaNota listaNotas;
    
    listaCursos.inicio = NULL;
    listaCursos.fim = NULL;
    
    listaNotas.inicio = NULL;
    listaNotas.fim = NULL;

    lerArq1(&listaCursos, "data/arq1.txt");
    lerArq3(&listaNotas, "data/arq3.txt");

    printf("Cursos (arquivo 1): \n");
    mostrarCursos(listaCursos.inicio);

    printf("\nNotas (arquivo 3): \n");
    mostrarNotas(listaNotas.inicio);

    return 0;
}
