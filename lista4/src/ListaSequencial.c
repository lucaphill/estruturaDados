#include <stdio.h>
#include <stdlib.h>
#include "ListaSequencial.h"

struct lista {
    int qtd;
    struct produto dados[MAX];
};

Lista* cria_lista() {
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if (li != NULL)
        li->qtd = 0;
    return li;
};

void libera_lista(Lista* li) {
	free(li);
};

// ------ INSERSÃO DE DADOS ------
int insere_lista_final(Lista* li, struct produto p) {
	if (li == NULL)
		return 0;
	if (li->qtd == MAX) // lista cheia
		return 0;
	li->dados[li->qtd] = p;
	li->qtd++;
	return 1;
};

int insere_lista_inicio(Lista* li, struct produto p) {
	if (li == NULL)
		return 0;
	if (li->qtd == MAX) // lista cheia
		return 0;
	int i;
	for (i = li->qtd-1; i >= 0; i--)
		li->dados[i+1] = li->dados[i];
	li->dados[0] = p;
	li->qtd++;
	return 1;
};

int insere_lista_ordenada(Lista* li, struct produto p) {
	if (li == NULL)
		return 0;
	if (li->qtd == MAX) // lista cheia
		return 0;
	int k, i = 0;
	while (i < li->qtd && li->dados[i].codigo < p.codigo)
		i++;
	for (k = li->qtd-1; k >= i; k--)
		li->dados[k+1] = li->dados[k];
	li->dados[i] = p;
	li->qtd++;
	return 1;
};
// ------ REMOÇÃO DE DADOS ------
int remove_lista(Lista* li, int cod) {
	if (li == NULL)
		return 0;
	if (li->qtd == 0) // lista vazia
		return 0;
	int k, i = 0;
	while (i < li->qtd && li->dados[i].codigo != cod)
		i++;
	if (i == li->qtd) // não encontrado
		return 0;
	for (k = i; k < li->qtd-1; k++)
		li->dados[k] = li->dados[k+1];
	li->qtd--;
	return 1;
};

int remove_lista_inicio(Lista* li) {
	if (li == NULL)
		return 0;
	if (li->qtd == 0) // lista vazia
		return 0;
	int k = 0;
	for (k = 0; k < li->qtd-1; k++)
		li->dados[k] = li->dados[k+1];
	li->qtd--;
	return 1;
}

int remove_lista_final(Lista* li) {
	if (li == NULL)
		return 0;
	if (li->qtd == 0) // lista vazia
		return 0;
	li->qtd--;
	return 1;
}
// ------ BUSCAS ------
int busca_lista_pos(Lista* li, int pos, struct produto *p) {
	if (li == NULL || pos <= 0 || pos > li->qtd)
		return 0;
	*p = li->dados[pos-1];
	return 1;
}

int busca_lista_mat(Lista* li, int cod, struct produto *p) {
	if (li == NULL)
		return 0;
	int i = 0;
	while (i < li->qtd && li->dados[i].codigo != cod)
		i++;
	if (i == li->qtd) // não encontrado
		return 0;
	*p = li->dados[i];
	return 1;
}

// ------ VERIFICAÇÕES ------
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
// ------ A PARTIR DAQUI COMEÇA AS QUESTÕES DA ATIVIDADE 4 ------
// para tal, mudaremos a variável 'aluno' para 'produto' com sua própria definição bonitinha no .h

int lista_tem_espaco(Lista* li, int n);
float soma_precos(Lista* li);
int busca_por_nome(Lista* li, char *nome, struct produto *p);
int insere_lista_decrescente(Lista* li, struct produto p);
int remove_mais_caro(Lista* li, struct produto *removido);
int conta_faixa_preco(Lista* li, float min, float max);
int remove_abaixo_de(Lista* li, float precoMinimo);
int mescla_listas(Lista* destino, Lista* origem);
