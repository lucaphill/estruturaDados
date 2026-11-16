/* Programa de teste da biblioteca: reproduz o trace geral da Aula 11
   (pilha com capacidade 4, incluindo pilha cheia e pilha vazia). */
#include <stdio.h>
#include "PilhaChar.h"

int verifica_delimitadores(const char *exrp){
	int tamanho=0;
	while(exrp[tamanho] != '\0')
		tamanho++;
	if(tamanho == 0)
		return 1;
	Pilha* pi = cria_Pilha(tamanho);
	if(pi == NULL)
		return 0;

	int i=0, errado=0;
	char aux=' ';

	while(exrp[i] != '\0'){
		if(exrp[i] == '(')
			insere_Pilha(pi, '(');
		else if(exrp[i] == ')'){
			if(tamanho_Pilha(pi) < 1){
				errado=1;
				break;
			}
			consulta_topo_Pilha(pi, &aux);
			if(aux != '('){
				errado=1;
				break;
			}
			remove_Pilha(pi);
		}

		else if(exrp[i] == '[')
			insere_Pilha(pi, '[');
		else if(exrp[i] == ']'){
			if(tamanho_Pilha(pi) < 1){
				errado=1;
				break;
			}
			consulta_topo_Pilha(pi, &aux);
			if(aux != '['){
				errado=1;
				break;
			}
			remove_Pilha(pi);
		}

		else if(exrp[i] == '{')
			insere_Pilha(pi, '{');
		else if(exrp[i] == '}'){
			if(tamanho_Pilha(pi) < 1){
				errado=1;
				break;
			}
			consulta_topo_Pilha(pi, &aux);
			if(aux != '{'){
				errado=1;
				break;
			}
			remove_Pilha(pi);
		}
		i++;
	}
	if(errado==1){
		libera_Pilha(pi);
		return 0;
	}else if(tamanho_Pilha(pi) == 0){
		libera_Pilha(pi);
		return 1;
	}else {
		libera_Pilha(pi);
		return 0;
	}
}
/*
 * Ela precisaria ter o tamanho da string de capacidade para não falhar
 * d)
 * Não, com mais coisas não podemos só guardar a quantidade já que a ordem
 * deles também importa...
 */

int main() {
	char certo[]   = "()(){}{[]}";
	char errado[]  = "([)]";
	char errado2[] = "())({}";
	printf("()(){}{[]} %d\n", verifica_delimitadores(certo));
	printf("([)]       %d\n", verifica_delimitadores(errado));
	printf("())({}     %d\n", verifica_delimitadores(errado2));

	return 0;
}
