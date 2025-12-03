#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOP 100  /* máximo de notas a mostrar */

typedef struct Curso {
    int ano;
    int co_curso;
    int co_ies;
    int co_grupo;
    int co_uf;
    struct Curso *esq;
    struct Curso *dir;
} Curso;

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

/* -------------------- Inserção na BST -------------------- */
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
    if (c.co_curso < raiz->co_curso) {
        raiz->esq = inserirCursoArv(raiz->esq, c);
    } else if (c.co_curso > raiz->co_curso) {
        raiz->dir = inserirCursoArv(raiz->dir, c);
    }
    return raiz;
}

Curso* buscarCursoArv(Curso *raiz, int cod) {
    if (!raiz) return NULL;
    if (cod == raiz->co_curso) return raiz;
    if (cod < raiz->co_curso) return buscarCursoArv(raiz->esq, cod);
    return buscarCursoArv(raiz->dir, cod);
}

void listarCursosArv(Curso *raiz, const char *tipo, int codigo) {
    if (!raiz) return;
    listarCursosArv(raiz->esq, tipo, codigo);
    if ((strcmp(tipo,"ies")==0 && raiz->co_ies==codigo) ||
        (strcmp(tipo,"uf")==0 && raiz->co_uf==codigo) ||
        (strcmp(tipo,"grupo")==0 && raiz->co_grupo==codigo)) {
        printf("Curso %d | IES %d | Grupo %d | UF %d | Ano %d\n",
               raiz->co_curso, raiz->co_ies, raiz->co_grupo, raiz->co_uf, raiz->ano);
    }
    listarCursosArv(raiz->dir, tipo, codigo);
}

/* -------------------- Lista de Notas -------------------- */
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

Curso* lerArq1(const char *nome) {
    FILE *f;
    char linha[2048];
    Curso c;
    char *token;
    Curso *raiz = NULL;

    f = fopen(nome, "r");
    if (!f) { printf("Erro ao abrir %s\n", nome); exit(1); }

    fgets(linha, sizeof(linha), f); /* pula cabeçalho */
    while (fgets(linha, sizeof(linha), f)) {
        token = strtok(linha, ";"); c.ano = atoi(token);
        token = strtok(NULL, ";");  c.co_curso = atoi(token);
        token = strtok(NULL, ";");  c.co_ies = atoi(token);
        token = strtok(NULL, ";");  /* ignorado */
        token = strtok(NULL, ";");  /* ignorado */
        token = strtok(NULL, ";");  c.co_grupo = atoi(token);
        token = strtok(NULL, ";");  /* ignorado */
        token = strtok(NULL, ";");  /* ignorado */
        token = strtok(NULL, ";");  c.co_uf = atoi(token);

        raiz = inserirCursoArv(raiz, c);
    }
    fclose(f);
    return raiz;
}

void lerArq3(ListaNota *lista, const char *nome) {
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

        inserirNota(lista, n);
    }
    fclose(f);
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
    if (qtd>0)
        printf("Media: NT_GER=%.2f | NT_ES=%.2f\n", somaGer/qtd, somaEs/qtd);
    else
        printf("Nenhuma nota encontrada.\n");
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

    if (qtd>0)
        printf("Media curso %d: NT_GER=%.2f | NT_ES=%.2f\n", co_curso, somaGer/qtd, somaEs/qtd);
    else
        printf("Nenhuma nota encontrada para o curso %d\n", co_curso);
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

int main() {
    Curso *raizCursos;
    ListaNota listaNotas;
    int opc;

    listaNotas.inicio = NULL;
    listaNotas.fim = NULL;

    raizCursos = lerArq1("data/arq1.txt");
    lerArq3(&listaNotas,"data/arq3.txt");

    for(;;) {
        int cod, ies, uf, grupo, n, t;
        Curso *c;

        printf("\nMenu:\n");
        printf("1 - Buscar curso por codigo\n");
        printf("2 - Listar cursos por IES\n");
        printf("3 - Listar cursos por UF\n");
        printf("4 - Listar cursos por grupo\n");
        printf("5 - Top N maiores notas\n");
        printf("6 - Media de um curso\n");
        printf("0 - Sair\n");
        printf("Escolha opcao: ");
        if (scanf("%d",&opc)!=1) break;
        if (opc==0) break;

        if (opc==1) {
            printf("Digite codigo do curso: ");
            if (scanf("%d",&cod)!=1) break;
            c = buscarCursoArv(raizCursos,cod);
            if (c) {
                printf("Curso %d | IES %d | Grupo %d | UF %d | Ano %d\n",
                       c->co_curso,c->co_ies,c->co_grupo,c->co_uf,c->ano);
                mostrarNotasCurso(&listaNotas,c->co_curso);
            } else printf("Curso nao encontrado\n");
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
