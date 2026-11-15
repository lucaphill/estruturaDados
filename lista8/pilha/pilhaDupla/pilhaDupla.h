struct aluno {
    int   matricula;
    char  nome[30];
    float n1, n2, n3;
};
typedef struct pilhadupla PilhaDupla;

PilhaDupla* cria_PilhaDupla(int capacidade);
void libera_PilhaDupla(PilhaDupla* pd);
int tamanho_PilhaDupla(PilhaDupla* pd, int p);
int PilhaDupla_cheia(PilhaDupla* pd);
int insere_PilhaDupla(PilhaDupla* pd, int p, struct aluno al);
int remove_PilhaDupla(PilhaDupla* pd, int p);
int consulta_topo_PilhaDupla(PilhaDupla* pd, int p, struct aluno *al);
