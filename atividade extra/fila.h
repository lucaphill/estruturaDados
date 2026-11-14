#include "ListaDinEncad.h"
struct elem {
    int codigo;
    char descricao[40];
    int prioridade;
};
typedef struct elemento* Fila;

Fila* cria_Fila(void);
void libera_Fila(Fila* fi);
int tamanho_Fila(Fila* fi);
int Fila_vazia(Fila* fi);
int Fila_cheia(Fila* fi);
int insere_Fila(Fila* fi, struct elem t);
int remove_Fila(Fila* fi);
int consulta_Fila(Fila* fi, struct elem *t);
