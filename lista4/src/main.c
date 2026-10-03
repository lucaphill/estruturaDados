#include "ListaSequencial.h"
#include <stdio.h>
#include <string.h>

void menu(){
	printf("--- MENU ---\n");
	printf("0 - Sair\n");
	printf("1 - Tem espaco pra n produtos?\n");
	printf("2 - Somar precos\n");
	printf("3 - Buscar por nome\n");
	printf("4 - Inserir decrescente\n");
	printf("5 - Remover o mais caro\n");
	printf("6 - Contar na faixa de preco\n");
	printf("7 - Remove abaixo de n\n");
	printf("8 - Mescla listas\n");
	printf("Escolha: ");
}

void escolha(Lista* list, Lista* list2, int num, struct produto* ptemp){
	if(num==1){
		printf("Quantos produtos quer colocar?\n");
		int t;
		scanf("%d", &t);
		if(lista_tem_espaco(list, t))
			printf("Sim, tem espaço\n");
		else printf("Não tem espaço\n");
	} else if(num==2){
		printf("A soma eh %.2f\n", soma_precos(list));
	} else if(num==3){
		char nome[30];
		printf("Qual nome esta procurando? ");
		scanf(" %29[^\n]", nome);
		if(busca_por_nome(list, nome, ptemp))
			printf("Produto encontrado e retornado no ponteiro\n");
		else printf("Não encontrado\n");
	} else if(num==4){
		insere_lista_decrescente(list, *ptemp);
	} else if(num==5){
		struct produto t;
		if(remove_mais_caro(list, &t))
			printf("O produto de cod %d foi removido\n", t.codigo);
		else printf("Lista vazia, nada removido\n");
	} else if(num==6){
		float min, max;
		printf("Preco minimo: ");
		scanf("%f", &min);
		printf("Preco maximo: ");
		scanf("%f", &max);
		printf("Quantidade na faixa: %d\n", conta_faixa_preco(list, min, max));
	} else if(num==7){
		float precoMinimo;
		printf("Remover tudo abaixo de qual preco? ");
		scanf("%f", &precoMinimo);
		printf("Produtos removidos: %d\n", remove_abaixo_de(list, precoMinimo));
	} else if(num==8){
		if(mescla_listas(list, list2))
			printf("Listas mescladas com sucesso\n");
		else printf("Falha ao mesclar\n");
	} else {
		printf("Opcao invalida\n");
	}
}

int main(void) {
	Lista* list = cria_lista();
	struct produto p1;
	p1.codigo = 1;
	strcpy(p1.nome, "Chocolate");
	p1.preco = 20.5;
	struct produto p2;
	p2.codigo = 2;
	strcpy(p2.nome, "Ouro");
	p2.preco = 1000;
	struct produto ptemp;
	ptemp.codigo = 100;
	strcpy(ptemp.nome, "Temporario");
	ptemp.preco = 10;

	insere_lista_final(list,p1);
	insere_lista_ordenada(list,p2);

	// lista separada pra testar o mescla_listas (opcao 8)
	Lista* list2 = cria_lista();
	struct produto p3;
	p3.codigo = 3;
	strcpy(p3.nome, "pastel");
	p3.preco = 5000000;
	insere_lista_final(list2, p3);

	// testando as funções
	while(1){
		int num;
		menu();
		scanf("%d", &num);
		if(num==0)
			break;
		escolha(list, list2, num, &ptemp);
	}
	libera_lista(list);
	libera_lista(list2);
	return 0;
}
