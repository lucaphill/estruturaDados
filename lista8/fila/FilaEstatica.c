/* ============================================================
   FilaEstatica.c
   Estrutura de Dados I - UFPB - Aula 09
   Implementacao da fila sequencial estatica com capacidade
   definida na criacao.

   Tudo o que deve ficar oculto do usuario da biblioteca esta
   aqui: a definicao de struct fila e o corpo das funcoes.
   ============================================================ */

//#include <stdio.h>
#include <stdlib.h>
#include "FilaEstatica.h"

/* inicio:     posicao do vetor que guarda o primeiro da fila.
   final:      posicao livre onde entra o proximo elemento.
   qtd:        quantos elementos estao na fila.
   capacidade: tamanho do vetor dados, escolhido em cria_Fila.
   dados:      vetor alocado com malloc em cria_Fila.

   O vetor e tratado como circular: ao passar da ultima posicao
   (capacidade - 1), inicio e final voltam para a posicao 0. Por
   isso inicio == final ocorre tanto na fila vazia quanto na fila
   cheia, e quem distingue os dois casos e o campo qtd. */
struct fila {
    int inicio, final, qtd;
    int capacidade;
    struct aluno *dados;
};

/* ------------------------------------------------------------
   Criacao e destruicao
   ------------------------------------------------------------ */

Fila* cria_Fila(int capacidade) {
    Fila *fi;
    if (capacidade <= 0)
        return NULL;
    fi = (Fila*) malloc(sizeof(struct fila));            /* 1a alocacao */
    if (fi == NULL)
        return NULL;
    fi->dados = (struct aluno*) malloc(capacidade * sizeof(struct aluno));
    if (fi->dados == NULL) {                             /* 2a alocacao falhou */
        free(fi);       /* sem este free, a struct ficaria perdida */
        return NULL;
    }
    fi->capacidade = capacidade;
    fi->inicio = 0;
    fi->final = 0;
    fi->qtd = 0;
    return fi;
}

void libera_Fila(Fila* fi) {
    if (fi == NULL)
        return;
    free(fi->dados);    /* primeiro o vetor: fi ainda e valido aqui */
    free(fi);           /* depois a estrutura que guardava o vetor */
}

/* ------------------------------------------------------------
   Informacoes de estado
   ------------------------------------------------------------ */

int tamanho_Fila(Fila* fi) {
    if (fi == NULL)
        return -1;
    return fi->qtd;
}

int Fila_cheia(Fila* fi) {
    if (fi == NULL)
        return -1;
    return (fi->qtd == fi->capacidade);  /* no livro: qtd == MAX */
}

int Fila_vazia(Fila* fi) {
    if (fi == NULL)
        return -1;
    return (fi->qtd == 0);
}

/* ------------------------------------------------------------
   Operacoes da fila
   ------------------------------------------------------------ */

int insere_Fila(Fila* fi, struct aluno al) {
    if (fi == NULL)
        return 0;
    if (Fila_cheia(fi))                   /* teste de estouro */
        return 0;
    fi->dados[fi->final] = al;            /* final e a posicao livre */
    fi->final = (fi->final + 1) % fi->capacidade;   /* volta para 0 no fim */
    fi->qtd++;
    return 1;
}

int remove_Fila(Fila* fi) {
    if (fi == NULL || Fila_vazia(fi))
        return 0;
    /* nenhum elemento e deslocado: o inicio apenas avanca */
    fi->inicio = (fi->inicio + 1) % fi->capacidade;
    fi->qtd--;
    return 1;
}

int consulta_Fila(Fila* fi, struct aluno *al) {
    if (fi == NULL || al == NULL || Fila_vazia(fi))
        return 0;
    *al = fi->dados[fi->inicio];
    return 1;
}
/*  ---------------- ATIVIDADE -----------------
 * > QUESTÃO 1 --------------------
 * a)
 *  1. retorna  1; inicio = 0, final = 0, qtd = 0, [-,-,-,-], para '-' sendo lixo
 *  2. retorna  1; inicio = 0, final = 1, qtd = 1, [a5,-,-,-], para '-' sendo lixo
 *  3. retorna  1; inicio = 0, final = 2, qtd = 2, [a5,a8,-,-], para '-' sendo lixo
 *  4. retorna  1; inicio = 0, final = 3, qtd = 3, [a5,a8,a3,-], para '-' sendo lixo
 *  5. retorna  1; inicio = 1, final = 3, qtd = 2, [\a5\,a8,a3,-], para '-' sendo lixo e '\x\' um elemento excluido
 *  6. retorna  1; inicio = 1, final = 0, qtd = 3, [\a5\,a8,a3,a9], para '-' sendo lixo e '\x\' um elemento excluido
 *  7. retorna  1; inicio = 1, final = 1, qtd = 4, [a7,a8,a3,a9], para '-' sendo lixo e '\x\' um elemento excluido
 *  8. retorna  0; inicio = 1, final = 1, qtd = 4, [a7,a8,a3,a9], para '-' sendo lixo e '\x\' um elemento excluido
 *  9. retorna  1; inicio = 2, final = 1, qtd = 3, [a7,\a8\,a3,a9], para '-' sendo lixo e '\x\' um elemento excluido
 * 10. retorna  1; inicio = 2, final = 2, qtd = 4, [a7,a6,a3,a9], para '-' sendo lixo e '\x\' um elemento excluido
 * 11. retorna a3; inicio = 2, final = 2, qtd = 4, [a7,a6,a3,a9], para '-' sendo lixo e '\x\' um elemento excluido
 *
 * b)
 * a6, a7, a9, a3 ... retorno foi a3
 *
 * c)
 * As posições {0,1} forãm escritas mais de uma vez, isso não perde nenhum elemento pois os elementos delas já tinham
 * cido descartados, como a fila é ciclica, podemos descartar elementos e sobrescrever eles sem perder nada
 */
// QUESTÃO 2 --------------------
// a)
/* fila vazia -> insere normalmente
 * inicio = 0 -> insere no final do vetor
 * fila cheia -> retorna erro
 *
 * b)
 * por algum motivo, mesmo a matemática já tendo uma solução ideal para mod de numeros negativos, em
 * programação é diferente, então vai dar erro, pra números negativos fica meio complexo e pelo que eu entendi
 * pode váriar de maquina para maquina.
 * Por isso uma forma de contornar é, como a lista não pode estar cheia, se inicio está em 0, final não pode estar
 * no último elemento, então podemos tratar esse caso especial colocando em capacidade-1
 *
 * c)
 * Não, agora dá pra considerar como uma fila de príoridade acho, já que a politica fifo foi quebrada
 */
int fura_Fila(Fila* fi, struct aluno al){
	if(fi==NULL || fi->qtd == fi->capacidade)
		return 0;
	if(fi->qtd == 0){
		insere_Fila(fi, al);
		return 1;
	}
	if(fi->inicio == 0){
		fi->inicio = fi->capacidade-1;
		fi->dados[fi->inicio] = al;
		fi->qtd++;
		return 1;
	}
	fi->dados[(fi->inicio-1) % fi->capacidade] = al;
	fi->inicio = (fi->inicio-1) % fi->capacidade;
	fi->qtd++;
	return 1;
}
// QUESTÃO 3 --------------------
/*
 * IMPLEMENTADA NA MAIN
 * b)
 * ela só precisa de n espaços, como a gente vai girando os elementos não precisa
 * de mais doq isso
 *
 * c)
 * ela é O(n*k), na implementação que eu fiz ficou O(n*(k-1)mod n) mas enfim se
 * fosse com lista sequêncial estática séria O(n^2*k) já que remover no inicio é O(n)
 */

vamos fazer um arquivo de teste apenas para treinar exatamente o que eu deveria estar fazendo no modo vim
