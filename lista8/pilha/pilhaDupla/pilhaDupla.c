#include <stdlib.h>
#include "pilhaDupla.h"

struct pilhadupla {
    int qtd1;
    int qtd2;
    int capacidade;
    struct aluno *dados;
    int primeira;
    int segunda;
};


PilhaDupla* cria_PilhaDupla(int capacidade){
	PilhaDupla *pi;
	if(capacidade <= 0)
		return NULL;
	pi = (PilhaDupla*) malloc(sizeof(struct pilhadupla));
	if(pi == NULL)
		return NULL;
	pi->dados = (struct aluno*) malloc(capacidade * sizeof(struct aluno));
	if(pi->dados == NULL){
		free(pi);
		return NULL;
	}
	pi->capacidade = capacidade;
	pi->primeira = 0;
	pi->segunda = capacidade-1;
	pi->qtd1 = 0;
	pi->qtd2 = 0;

	return pi;
}
void libera_PilhaDupla(PilhaDupla* pd){
	if(pd == NULL)
		return;
	free(pd->dados);
	free(pd);

}
int tamanho_PilhaDupla(PilhaDupla* pd, int p){
	if(pd == NULL)
		return -1;
	if(p==1)
		return pd->qtd1;
	else if(p==2)
		return pd->qtd2;
	else
		return -1;
}
int PilhaDupla_cheia(PilhaDupla* pd){
	if(pd == NULL)
		return -1;
	return (pd->qtd1 + pd->qtd2 == pd->capacidade);
}
int insere_PilhaDupla(PilhaDupla* pd, int p, struct aluno al){
	if(pd == NULL)
		return 0;
	if(PilhaDupla_cheia(pd))
		return 0;
	if(p==1){
		pd->dados[pd->primeira] = al;
		pd->primeira++;
    	pd->qtd1++;
	} else if (p==2){
		pd->dados[pd->segunda] = al;
		pd->segunda--;
		pd->qtd2++;
	}
	return 1;
}
int remove_PilhaDupla(PilhaDupla* pd, int p){
	if(pd == NULL)
		return 0;
	if(p==1){
		if(pd->qtd1==0)
			return 0;
		pd->primeira--;
    	pd->qtd1--;
	} else if (p==2){
		if(pd->qtd2==0)
			return 0;
		pd->segunda++;
		pd->qtd2--;
	}
	return 1;
}
int consulta_topo_PilhaDupla(PilhaDupla* pd, int p, struct aluno *al){
	if(pd == NULL)
		return 0;
	if(p==1){
		if(pd->qtd1==0)
			return 0;
		*al = pd->dados[pd->primeira-1];
	} else if (p==2){
		if(pd->qtd2==0)
			return 0;
		*al = pd->dados[pd->segunda+1];
	}
	return 1;
}
