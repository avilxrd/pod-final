#include "utils.h"

void throwMsgError(void) {
    printf("\n%snão encontrado!%s\n", COLOR_RED, COLOR_RESET);
    return;
}

Curso* lerArq1(const char *nome) {
    FILE *f;
    char linha[2048];
    Curso c;
    char *token;
    Curso *raiz = NULL;

    f = fopen(nome, "r");
    if (!f) { printf("Erro ao abrir %s\n", nome); exit(1); }

    fgets(linha, sizeof(linha), f);      /* pula cabeçalho */
    while (fgets(linha, sizeof(linha), f)) {
        token = strtok(linha, ";"); c.ano      = atoi(token);
        token = strtok(NULL, ";");  c.co_curso = atoi(token);
        token = strtok(NULL, ";");  c.co_ies   = atoi(token);
        token = strtok(NULL, ";");             /* ignorado */
        token = strtok(NULL, ";");             /* ignorado */
        token = strtok(NULL, ";");  c.co_grupo = atoi(token);
        token = strtok(NULL, ";");             /* ignorado */
        token = strtok(NULL, ";");             /* ignorado */
        token = strtok(NULL, ";");  c.co_uf    = atoi(token);

        raiz = inserirCursoArv(raiz, c);
    }
    fclose(f);
    return raiz;
}

void lerArq3(VetorNotas *v, const char *nome) {
    FILE *f;
    char linha[4096];
    Nota n;
    char *token;
    int i;

    f = fopen(nome, "r");
    if (!f) { printf("Erro ao abrir %s\n", nome); exit(1); }

    fgets(linha, sizeof(linha), f); /* pula cabeçalho */ 
    while (fgets(linha, sizeof(linha), f)) {
        token = strtok(linha, ";"); /* ano */
        token = strtok(NULL, ";");  n.co_curso = atoi(token);
        for (i=0;i<21;i++) token=strtok(NULL,";");
        token = strtok(NULL,";"); n.nt_ger = token ? atof(token) : -1.0f;
        for (i=0;i<7;i++) token=strtok(NULL,";");
        token = strtok(NULL,";"); n.nt_es = token ? atof(token) : -1.0f;

        inserirNota(v, n);
    }
    fclose(f);
    ordenarNotas(v);
}