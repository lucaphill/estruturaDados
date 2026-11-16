/* ============================================================
   PilhaSequencial.c
   Estrutura de Dados I - UFPB - Aula 11
   Implementacao da pilha sequencial estatica com capacidade
   definida na criacao.

   Tudo o que deve ficar oculto do usuario da biblioteca esta
   aqui: a definicao de struct pilha e o corpo das funcoes.
   ============================================================ */

#include <stdlib.h>
#include "PilhaChar.h"

/* qtd:        quantos elementos estao na pilha.
   capacidade: tamanho do vetor dados, escolhido em cria_Pilha.
   dados:      vetor alocado com malloc em cria_Pilha.

   A base da pilha e dados[0] e o topo e dados[qtd - 1]. A proxima
   insercao grava em dados[qtd], que e a primeira posicao livre.
   Assim, empilhar e desempilhar nunca deslocam elementos: e a
   insercao e a remocao no final da lista sequencial estatica. */
struct pilha {
    int qtd;
    int capacidade;
    char* dados;
};

/* ------------------------------------------------------------
   Criacao e destruicao
   ------------------------------------------------------------ */

Pilha* cria_Pilha(int capacidade) {
    Pilha *pi;
    if (capacidade <= 0)
        return NULL;
    pi = (Pilha*) malloc(sizeof(struct pilha)); /* 1a alocacao */
    if (pi == NULL)
        return NULL;
    pi->dados = (char*) malloc(capacidade * sizeof(char));
    if(pi->dados == NULL){
    	free(pi);
     	return NULL;
    }
    pi->capacidade = capacidade;
    pi->qtd = 0;
    return pi;
}

void libera_Pilha(Pilha* pi) {
    if (pi == NULL)
        return;
    free(pi->dados);    /* primeiro o vetor: pi ainda e valido aqui */
    free(pi);           /* depois a estrutura que guardava o vetor */
}

/* ------------------------------------------------------------
   Informacoes de estado
   ------------------------------------------------------------ */

int tamanho_Pilha(Pilha* pi) {
    if (pi == NULL)
        return -1;
    return pi->qtd;
}

int Pilha_cheia(Pilha* pi) {
    if (pi == NULL)
        return -1;
    return (pi->qtd == pi->capacidade);  /* no livro: qtd == MAX */
}

int Pilha_vazia(Pilha* pi) {
    if (pi == NULL)
        return -1;
    return (pi->qtd == 0);
}

/* ------------------------------------------------------------
   Operacoes da pilha (sempre no topo)
   ------------------------------------------------------------ */

int insere_Pilha(Pilha* pi, char c) {
    if (pi == NULL)
        return 0;
    if (Pilha_cheia(pi))                 /* teste de estouro */
        return 0;
    pi->dados[pi->qtd] = c;              /* qtd e a primeira posicao livre */
    pi->qtd++;                           /* o novo elemento passa a ser o topo */
    return 1;
}

int remove_Pilha(Pilha* pi) {
    if (pi == NULL || Pilha_vazia(pi))
        return 0;
    pi->qtd--;          /* o topo desce uma posicao; nada e apagado */
    return 1;
}

int consulta_topo_Pilha(Pilha* pi, char* c) {
    if (pi == NULL || c == NULL || Pilha_vazia(pi))
        return 0;
    *c = pi->dados[pi->qtd - 1];         /* topo: ultima posicao ocupada */
    return 1;
}
/*  ---------------- ATIVIDADE -----------------
 * QUESTÃO 5 -------------------
 * Em pilhaChar.h eu tirei a definição de struct e mudei os tipos de aluno para char
 * Nesse arquivo as funções de insersão e consulta mudaram, além disso claro, tive que
 * mudar a definição da lista, colocando um ponteiro para char, e na criação, alocamos
 * o tamanho equivalente a um array de char e colocamos esse ponteiro para apontar para
 * ele.
 *
 * b)
 */
