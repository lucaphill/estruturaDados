#include <stdlib.h>
#include <string.h>
#include "fila.h"
struct elemento {
	struct elem dados;
    struct elemento *final;
    struct elemento *prox;
    int qtd;
};
typedef struct elemento Elem;


Fila* cria_Fila(void){
	Fila* fi = (Fila*) malloc(sizeof(Fila));
	if(fi != NULL){
		 *fi          = NULL;
		(*fi)->final  = NULL;
		(*fi)->qtd    =    0;
	}
	return fi;
}
void libera_Fila(Fila* fi){
	if(fi == NULL) return;
	Elem* no;
	while((*fi) != NULL)
		remove_Fila(fi);
	free(fi);
}
int tamanho_Fila(Fila* fi){
	if(  fi  == NULL) return -1;
	if((*fi) == NULL) return  0;
	return           (*fi)->qtd;
}
int Fila_vazia(Fila* fi){
	if(  fi  == NULL) return -1;
	if((*fi) == NULL) return  1;
	return      ((*fi)->qtd)==0;
}
int Fila_cheia(Fila* fi){
	if(fi == NULL)    return -1;
	return 0;
}
int insere_Fila(Fila* fi, struct elem t){
	if(fi == NULL) return 0;
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) return 0;
	no->dados          =  t;
	no->prox         = NULL;
	(*fi)->final->prox = no;
	(*fi)->final       = no;
	return 1;
}
int remove_Fila(Fila* fi){
	if(fi == NULL||(*fi) == NULL) return 0;
	Elem* aux = (*fi);
	(*fi) = (*fi)->prox;
	free(aux);
	return 1;
}
int consulta_Fila(Fila* fi, struct elem *t){
	if(fi == NULL||(*fi) == NULL) return 0;
	return(*fi)->dados.codigo == t->codigo;
}
