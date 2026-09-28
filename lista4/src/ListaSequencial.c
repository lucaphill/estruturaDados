#include <stdio.h>
#include <stdlib.h>
#include "ListaSequencial.h"

struct lista {
    int qtd;
    struct aluno dados[MAX];
};

Lista* cria_lista() {
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if (li != NULL)
        li->qtd = 0;
    return li;
};

int tamanho_lista(Lista* li) {
    if (li == NULL)
        return -1;
    return li->qtd;
};

int lista_cheia(Lista* li) {
    if (li == NULL)
        return -1;
    return (li->qtd == MAX);
};

int lista_vazia(Lista* li) {
    if (li == NULL)
        return -1;
    return (li->qtd == 0);
};
