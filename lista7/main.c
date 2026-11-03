#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"

/* cria uma lista com os valores do vetor (so a matricula importa) */
Lista* cria_com(int v[], int n){
	Lista* li = cria_lista();
	for(int i = 0; i < n; i++){
		struct aluno al = {0};
		al.matricula = v[i];
		insere_lista_final(li, al);
	}
	return li;
}

/* imprime as matriculas do inicio ao fim */
void imprime(Lista* li){
	struct aluno al;
	for(int i = 1; i <= tamanho_lista(li); i++){
		busca_lista_pos(li, i, &al);
		printf("%d ", al.matricula);
	}
	printf("\n");
}

int main(){
	Lista *li, *vazia = cria_lista();

	printf("===== QUESTAO 1 =====\n");
	int v1[] = {33, 23, 16};
	li = cria_com(v1, 3);
	printf("Lista: ");
	imprime(li);
	printf("Inversa: ");
	imprime_lista_inversa(li);
	printf("Lista vazia: ");
	imprime_lista_inversa(vazia);
	printf("Lista invalida: ");
	imprime_lista_inversa(NULL);
	libera_lista(li);

	printf("\n===== QUESTAO 2 =====\n");
	li = cria_com(v1, 3);
	printf("Lista normal: %d (esperado 1)\n", lista_consistente(li));
	printf("Lista vazia: %d (esperado 1)\n", lista_consistente(vazia));
	printf("Lista invalida: %d (esperado 0)\n", lista_consistente(NULL));
	libera_lista(li);

	printf("\n===== QUESTAO 4 =====\n");
	int v4[] = {10, 20, 30, 40};
	li = cria_com(v4, 4);
	printf("Lista: ");
	imprime(li);
	printf("Remove pos 2 (meio): retorno %d -> ", remove_lista_pos(li, 2));
	imprime(li);
	printf("Remove pos 1 (primeiro): retorno %d -> ", remove_lista_pos(li, 1));
	imprime(li);
	printf("Remove pos 2 (ultimo): retorno %d -> ", remove_lista_pos(li, 2));
	imprime(li);
	printf("Remove pos 5 (inexistente): retorno %d\n", remove_lista_pos(li, 5));
	printf("Remove pos 0 (invalida): retorno %d\n", remove_lista_pos(li, 0));
	printf("Remove ultimo elemento: retorno %d -> ", remove_lista_pos(li, 1));
	imprime(li);
	printf("Remove em lista vazia: retorno %d\n", remove_lista_pos(li, 1));
	printf("Remove em lista invalida: retorno %d\n", remove_lista_pos(NULL, 1));
	printf("Consistente: %d\n", lista_consistente(li));
	libera_lista(li);

	printf("\n===== QUESTAO 5 =====\n");
	li = cria_com(v4, 4);
	printf("Lista: ");
	imprime(li);
	printf("Move 30 (meio): retorno %d -> ", move_para_inicio(li, 30));
	imprime(li);
	printf("Move 40 (ultimo): retorno %d -> ", move_para_inicio(li, 40));
	imprime(li);
	printf("Move 40 (ja e o primeiro): retorno %d -> ", move_para_inicio(li, 40));
	imprime(li);
	printf("Move 99 (inexistente): retorno %d\n", move_para_inicio(li, 99));
	printf("Consistente: %d\n", lista_consistente(li));
	libera_lista(li);

	printf("\n===== QUESTAO 6 =====\n");
	int v6[] = {7, 3, 7, 7, 5, 7};
	li = cria_com(v6, 6);
	printf("Lista: ");
	imprime(li);
	printf("Remove todos os 7: removidos %d -> ", remove_todos(li, 7));
	imprime(li);
	printf("Consistente: %d\n", lista_consistente(li));
	libera_lista(li);

	int v6b[] = {7, 7, 7};
	li = cria_com(v6b, 3);
	int removidos = remove_todos(li, 7);
	printf("Lista so com 7: removidos %d, lista_vazia = %d\n", removidos, lista_vazia(li));
	libera_lista(li);

	printf("\n===== QUESTAO 7 =====\n");
	int v7[] = {1, 2, 3, 4, 5};
	li = cria_com(v7, 5);
	printf("Antes: ");
	imprime(li);
	inverte_lista(li);
	printf("Depois: ");
	imprime(li);
	printf("Consistente: %d\n", lista_consistente(li));
	libera_lista(li);

	int v7b[] = {1, 2};
	li = cria_com(v7b, 2);
	inverte_lista(li);
	printf("Dois elementos invertidos: ");
	imprime(li);
	libera_lista(li);

	printf("\n===== QUESTAO 8 =====\n");
	int p1[] = {1, 2, 3, 2, 1}, p2[] = {4, 8, 8, 4}, p3[] = {1, 2, 2, 3}, p4[] = {9};
	li = cria_com(p1, 5);
	printf("1 2 3 2 1: %d (esperado 1)\n", eh_palindromo(li));
	libera_lista(li);
	li = cria_com(p2, 4);
	printf("4 8 8 4: %d (esperado 1)\n", eh_palindromo(li));
	libera_lista(li);
	li = cria_com(p3, 4);
	printf("1 2 2 3: %d (esperado 0)\n", eh_palindromo(li));
	libera_lista(li);
	li = cria_com(p4, 1);
	printf("um elemento: %d (esperado 1)\n", eh_palindromo(li));
	libera_lista(li);
	printf("lista vazia: %d (esperado 1)\n", eh_palindromo(vazia));
	printf("lista invalida: %d (esperado 0)\n", eh_palindromo(NULL));

	libera_lista(vazia);
	return 0;
}
