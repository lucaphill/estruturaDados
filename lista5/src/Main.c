#include "ListaDinamica.h"
#include <stdio.h>
#include <string.h>

void mostra(ListaTarefas* li, const char* nome){
	struct tarefa t;
	printf("%s:", nome);
	if(li == NULL){
		printf(" NULL\n");
		return;
	}
	for(int i = 1; busca_tarefa_pos(li, i, &t); i++)
		printf(" [cod %d, prio %d, %s]", t.codigo, t.prioridade, t.descricao);
	printf("\n");
}

struct tarefa nova(int cod, const char* desc, int prio){
	struct tarefa t;
	t.codigo = cod;
	strcpy(t.descricao, desc);
	t.prioridade = prio;
	return t;
}

void menu(){
	printf("--- MENU ---\n");
	printf("0  - Sair\n");
	printf("1  - Contar por prioridade\n");
	printf("2  - Tarefa mais urgente\n");
	printf("3  - Buscar por descricao\n");
	printf("4  - Inserir apos a ultima de mesma prioridade\n");
	printf("5  - Remover todas de uma prioridade\n");
	printf("6  - Inverter lista\n");
	printf("7  - Remover por posicao\n");
	printf("8  - Mesclar listas\n");
	printf("9  - Inserir tarefa no final da lista 1\n");
	printf("10 - Mostrar listas\n");
	printf("Escolha: ");
}

void escolha(ListaTarefas* list, ListaTarefas* list2, int num){
	if(num==1){
		int p;
		printf("Qual prioridade? ");
		scanf("%d", &p);
		printf("Quantidade: %d\n", conta_tarefas_prioridade(list, p));
	} else if(num==2){
		struct tarefa t;
		if(tarefa_mais_urgente(list, &t))
			printf("Mais urgente: cod %d, prio %d\n", t.codigo, t.prioridade);
		else printf("Lista vazia, nada encontrado\n");
	} else if(num==3){
		char texto[40];
		struct tarefa t;
		printf("Qual texto esta procurando? ");
		scanf(" %39[^\n]", texto);
		if(busca_tarefa_desc(list, texto, &t))
			printf("Encontrada: cod %d, %s\n", t.codigo, t.descricao);
		else printf("Nao encontrada\n");
	} else if(num==4){
		int cod, prio;
		printf("Codigo e prioridade da nova tarefa: ");
		scanf("%d %d", &cod, &prio);
		if(insere_tarefa_final_prioridade(list, nova(cod, "nova", prio)))
			printf("Inserida\n");
		else printf("Falha ao inserir\n");
	} else if(num==5){
		int p;
		printf("Remover qual prioridade? ");
		scanf("%d", &p);
		printf("Removidas: %d\n", remove_tarefas_prioridade(list, p));
	} else if(num==6){
		if(inverte_lista(list))
			printf("Lista invertida\n");
		else printf("Falha ao inverter\n");
	} else if(num==7){
		int pos;
		printf("Qual posicao (a partir de 1)? ");
		scanf("%d", &pos);
		if(remove_tarefa_pos(list, pos))
			printf("Removida\n");
		else printf("Posicao invalida, nada removido\n");
	} else if(num==8){
		printf("Transferidas: %d\n", mescla_tarefas(list, list2));
	} else if(num==9){
		int cod, prio;
		printf("Codigo e prioridade: ");
		scanf("%d %d", &cod, &prio);
		insere_tarefa_final(list, nova(cod, "tarefa", prio));
	} else if(num==10){
		mostra(list, "Lista 1");
		mostra(list2, "Lista 2");
	} else {
		printf("Opcao invalida\n");
	}
}

int main(void) {
	ListaTarefas* list = cria_lista();
	ListaTarefas* list2 = cria_lista();

	insere_tarefa_final(list, nova(1, "Estudar ED1", 2));
	insere_tarefa_final(list, nova(2, "Entregar lista", 1));
	insere_tarefa_final(list, nova(3, "Estudar calculo numerico", 2));
	insere_tarefa_final(list2, nova(10, "Revisar codigo", 3));
	insere_tarefa_final(list2, nova(11, "jogar minecraft", 1));

	while(1){
		int num;
		menu();
		scanf("%d", &num);
		if(num==0)
			break;
		escolha(list, list2, num);
	}
	libera_lista(list);
	libera_lista(list2);
	return 0;
}
