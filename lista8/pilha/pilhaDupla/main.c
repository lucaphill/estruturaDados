#include <stdio.h>
#include "pilhaDupla.h"

static void mostra_estado(PilhaDupla* pd){
	struct aluno t;
	printf("   qtd1=%d qtd2=%d | topo1=", tamanho_PilhaDupla(pd, 1), tamanho_PilhaDupla(pd, 2));
	if(consulta_topo_PilhaDupla(pd, 1, &t)) printf("%d", t.matricula);
	else printf("-");
	printf(" topo2=");
	if(consulta_topo_PilhaDupla(pd, 2, &t)) printf("%d", t.matricula);
	else printf("-");
	printf("\n");
}

static void insere(PilhaDupla* pd, int p, int mat){
	struct aluno al;
	al.matricula = mat;
	int r = insere_PilhaDupla(pd, p, al);
	printf("insere %d na pilha %d -> retorno %d\n", mat, p, r);
	mostra_estado(pd);
}

int main() {
	PilhaDupla* pd = cria_PilhaDupla(5);
	if(pd == NULL)
		return 1;

	insere(pd, 1, 10);
	insere(pd, 2, 90);
	insere(pd, 1, 20);
	insere(pd, 2, 80);
	insere(pd, 1, 30);
	insere(pd, 2, 70);   /* cheia: deve retornar 0 */

	int r = remove_PilhaDupla(pd, 2);
	printf("remove da pilha 2 -> retorno %d\n", r);
	mostra_estado(pd);

	insere(pd, 1, 40);

	libera_PilhaDupla(pd);
	return 0;
}
/* c)
 * Quando vc precisar inserir mais de 4 elementos em uma das pilhas e a outra ainda tiver
 * espaço a pilha separada vai perder para a unificada. Não existe a situação inversa pq
 * teoricamente fazer a pilha assim é a mesma coisa de fazer duas pilhas singulares.
 *
 * d)
 * São todas O(1) não precisa percorrer a pilha em nenhum momento, isso pode ser vantajoso
 * por ex quando fazendo um sistema para juntar a heap e a pilha, ou quando tem um limite claro
 * de coisas que precisam ser classificadas de duas formas diferentes mas estão aleatóriamente
 * distribuidas.
 */
