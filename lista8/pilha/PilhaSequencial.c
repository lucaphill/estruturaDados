/* ============================================================
   PilhaSequencial.c
   Estrutura de Dados I - UFPB - Aula 11
   Implementacao da pilha sequencial estatica com capacidade
   definida na criacao.

   Tudo o que deve ficar oculto do usuario da biblioteca esta
   aqui: a definicao de struct pilha e o corpo das funcoes.
   ============================================================ */

#include <stdlib.h>
#include "PilhaSequencial.h"

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
    struct aluno *dados;
};

/* ------------------------------------------------------------
   Criacao e destruicao
   ------------------------------------------------------------ */

Pilha* cria_Pilha(int capacidade) {
    Pilha *pi;
    if (capacidade <= 0)
        return NULL;
    pi = (Pilha*) malloc(sizeof(struct pilha));          /* 1a alocacao */
    if (pi == NULL)
        return NULL;
    pi->dados = (struct aluno*) malloc(capacidade * sizeof(struct aluno));
    if (pi->dados == NULL) {                             /* 2a alocacao falhou */
        free(pi);       /* sem este free, a struct ficaria perdida */
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

int insere_Pilha(Pilha* pi, struct aluno al) {
    if (pi == NULL)
        return 0;
    if (Pilha_cheia(pi))                  /* teste de estouro */
        return 0;
    pi->dados[pi->qtd] = al;              /* qtd e a primeira posicao livre */
    pi->qtd++;                            /* o novo elemento passa a ser o topo */
    return 1;
}

int remove_Pilha(Pilha* pi) {
    if (pi == NULL || Pilha_vazia(pi))
        return 0;
    pi->qtd--;          /* o topo desce uma posicao; nada e apagado */
    return 1;
}

int consulta_topo_Pilha(Pilha* pi, struct aluno *al) {
    if (pi == NULL || al == NULL || Pilha_vazia(pi))
        return 0;
    *al = pi->dados[pi->qtd - 1];         /* topo: ultima posicao ocupada */
    return 1;
}
/*  ---------------- ATIVIDADE -----------------
 * QUESTÃO 4 ------------------
 * a)
 * ordem:
 * i:1 = [1]
 * i:2 = [2, 1]
 * r   = [1]
 * i:3 = [3, 1]
 * i:4 = [4,3,1]
 * r   = [3,1]
 * r   = [1]
 * r   = []
 *
 * b)
 * Não, para conseguir inserir o 3 precisaria inserir 1,2 antes.
 * Considerando isso não teria como a próxima saída ser 1 já que o
 * 2 tem príoridade como entrou mais tarde
 *
 * c)
 */
int sequencia_valida(const char *s){
	int i=0, qtd=0;
	while(s[i] != '\0'){
		if(qtd < 0) break;
		if(s[i] == 'I')
			qtd++;
		else if(s[i] == 'R')
			qtd--;
		i++;
	}
	if(qtd == 0)
		return 1;
	else
		return 0;
}
/*
 * Tecnicamente não, mas basicamente, eu usei um contador que funciona
 * de forma parecido com uma pilha, para cada 'I' ele empilha, e para
 * cada 'R' ele desempilha... No final é só conferir se a "pilha" está
 * vázia, se estiver, então a sequência era válida, além disso se em algum
 * momento ficar negativo ela quebra;
 *
 * QUESTÃO 5 -------------------
 * Ta em pilha char
 *
 * QUESTÃO 6 -------------------
 *
 */
