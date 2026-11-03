/* ============================================================
   ListaDinEncadDupla.c
   Estrutura de Dados I - UFPB - Aula 08
   Lista dinamica duplamente encadeada

   Implementacao identica a apresentada nos slides da Aula 08.
   A definicao de struct elemento esta aqui, e nao no .h: e isso
   que torna Lista um tipo opaco. Quem usa a biblioteca enxerga
   apenas Lista* e os prototipos declarados no cabecalho.

   Qualquer funcao nova que precise percorrer a lista no a no
   tem de ser escrita NESTE arquivo, porque e aqui que os campos
   ant, dados e prox sao visiveis.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"

/* Definicao do tipo lista: oculta de quem usa a biblioteca.
   Com struct aluno de 48 bytes, sizeof(Elem) = 64 bytes em uma
   plataforma de 64 bits, contra 56 na lista encadeada simples. */
struct elemento {
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

/* --- criacao e destruicao ---------------------------------- */

Lista* cria_lista(void) {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li) {
    if (li != NULL) {
        Elem* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;   /* avanca antes de liberar */
            free(no);
        }
        free(li);                /* libera o bloco do inicio */
    }
}

/* --- informacoes de estado --------------------------------- */

int tamanho_lista(Lista* li) {
    if (li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL) {
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li) {
    (void) li;               /* parametro mantido por simetria com as demais */
    return 0;
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return 1;            /* lista invalida */
    if (*li == NULL)
        return 1;            /* nenhum elemento alocado */
    return 0;
}

/* --- insercao ---------------------------------------------- */

int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;    /* sem memoria: a lista esta cheia */
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if (*li != NULL)             /* lista nao vazia */
        (*li)->ant = no;         /* o antigo primeiro ganha antecessor */
    *li = no;
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    no->prox = NULL;
    if ((*li) == NULL) {         /* lista vazia: insere inicio */
        no->ant = NULL;
        *li = no;
    } else {
        Elem* aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    if ((*li) == NULL) {         /* lista vazia: insere inicio */
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    }
    else {
        /* O livro declara ante sem valor inicial. A inicializacao com
           NULL nao altera o comportamento e elimina o aviso
           "may be used uninitialized" do gcc com -O2. */
        Elem *ante = NULL, *atual = *li;
        while (atual != NULL &&
               atual->dados.matricula < al.matricula) {
            ante = atual;
            atual = atual->prox;
        }
        if (atual == *li) {      /* insere inicio */
            no->ant = NULL;
            (*li)->ant = no;
            no->prox = (*li);
            *li = no;
        } else {                 /* insere no meio ou no final */
            no->prox = ante->prox;
            no->ant = ante;
            ante->prox = no;
            if (atual != NULL)   /* nao e o ultimo */
                atual->ant = no;
        }
        return 1;
    }
}

/* --- remocao ----------------------------------------------- */

int remove_lista_inicio(Lista* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    *li = no->prox;
    if (no->prox != NULL)          /* existe um seguinte */
        no->prox->ant = NULL;      /* ele passa a ser o primeiro */
    free(no);
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    while (no->prox != NULL)
        no = no->prox;
    if (no->ant == NULL)           /* primeiro e unico */
        *li = no->prox;
    else
        no->ant->prox = NULL;      /* penultimo obtido pelo proprio no */
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL)                /* chave ausente */
        return 0;
    if (no->ant == NULL)           /* remove o primeiro */
        *li = no->prox;
    else
        no->ant->prox = no->prox;
    if (no->prox != NULL)          /* nao e o ultimo */
        no->prox->ant = no->ant;
    free(no);
    return 1;
}

/* --- busca ------------------------------------------------- */

int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while (no != NULL && i < pos) {
        no = no->prox;
        i++;
    }
    if (no == NULL)
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) {
    if (li == NULL)
        return 0;
    Elem *no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL)
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}

/*___________________ATIVIDADE_________________________*/
/*QUESTÃO 1*/
/*
 * Custo: O(n). Vai até o último por prox (n-1 passos) e volta por ant (n-1 passos),
 * ou seja, 2n - 2 passos no total, que continua sendo linear.
 */
void imprime_lista_inversa(Lista* li){
	if(li == NULL || (*li) == NULL){
		printf("(lista vazia)\n");
		return;
	}
	Elem *no = *li;
	while(no->prox != NULL)
		no = no->prox;
	while(no != NULL){
		printf("%d ", no->dados.matricula);
		no = no->ant;
	}
	printf("\n");
}
/*QUESTÃO 2*/
int lista_consistente(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)
        return 1;
    Elem *no = *li;
    if(no->ant != NULL)
        return 0;
    while(no->prox != NULL) {
        if(no->prox->ant != no)
            return 0;
        no = no->prox;
    }
    return 1;
}
/*QUESTÃO 3*/
/* a) ele vai começar, vai ver que a lista é valida e testar o 33
 * como é diferente ele já vai para o while, mas depois ele tenta mudar
 * o que o ant ta apontando (que é NULL) e ele não mexe no ant do próximo
 * basicamente, ele acessa dados indevidos e ainda deixa um ponteiro para
 * um lugar que não deveria
 *
 * b) remove_lista(li, 23) em 33 23 16, lista após a chamada:
 *    [33] ant = NULL, prox = [16]
 *    [16] ant = (endereço do 23, JÁ LIBERADO), prox = NULL
 */
int remove_lista1(Lista* li, int mat){
    if(li == NULL || (*li) == NULL)
        return 0;
    Elem *no = *li;
    if(no->dados.matricula == mat){
        (*li) = no->prox;
        no->prox->ant = NULL;
        free(no);
        return 1;
    }
    while(no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if(no == NULL) return 0;
    no->ant->prox = no->prox;
    no->prox->ant = no->ant;
    free(no);
    return 1;
}
/*QUESTÃO 4*/
// Custo: O(pos), que no pior caso (última posição) é O(n). Remover a posição 1 é O(1).
int remove_lista_pos(Lista* li, int pos){
    if(li == NULL || (*li) == NULL || pos < 1)
        return 0;
    Elem *no = (*li);
    while(no != NULL && --pos)
        no = no->prox;
    if(no == NULL)
        return 0;
    if(no->ant == NULL)
        *li = no->prox;
    else
        no->ant->prox = no->prox;
    if(no->prox != NULL)
        no->prox->ant = no->ant;
    free(no);
    return 1;
}

/*QUESTÃO 5*/
/*
 * Elemento no meio: são escritos 5 campos de nós (no->ant->prox, no->prox->ant,
 * no->ant, no->prox e (*li)->ant), e mais o próprio *li, totalizando 6 ponteiros.
 * Elemento último: o if(no->prox != NULL) pula a escrita de no->prox->ant, então
 * são 4 campos de nós (no->ant->prox, no->ant, no->prox e (*li)->ant), 5 com *li.
 */
int move_para_inicio(Lista* li, int mat){
	if(li == NULL || (*li) == NULL)
		return 0;
	Elem *no = *li;
	while(no != NULL && no->dados.matricula != mat)
		no = no->prox;
	if(no == NULL)
		return 0;
	if(no == *li) // já é o primeiro
		return 1;
	no->ant->prox = no->prox;
	if(no->prox != NULL)
		no->prox->ant = no->ant;
	no->ant = NULL;
	no->prox = *li;
	(*li)->ant = no;
	*li = no;
	return 1;
}
/*QUESTÃO 6*/
int remove_todos(Lista* li, int mat){
	if(li == NULL || (*li) == NULL)
		return 0;
	int cont = 0;
	Elem *no = *li, *prox;
	while(no != NULL){
		prox = no->prox; // guarda o próximo antes do free
		if(no->dados.matricula == mat){
			if(no->ant == NULL)
				*li = no->prox;
			else
				no->ant->prox = no->prox;
			if(no->prox != NULL)
				no->prox->ant = no->ant;
			free(no);
			cont++;
		}
		no = prox;
	}
	return cont;
}
/*QUESTÃO 7*/
/*
 * Por que trocar ant e prox basta: cada nó inverte seu sucessor e antesessor
 * e a propriedade no->prox->ant == no é simétrica, então
 * continua valendo depois da troca. O antigo primeiro (ant NULL) vira o último
 * (prox NULL) e o antigo último vira o primeiro, por isso só falta atualizar *li
 * para o antigo último.
 * Custo: O(n) no tempo (uma única passada) e O(1) de memória extra.
 */
void inverte_lista(Lista* li){
	if(li == NULL || (*li) == NULL)
		return;
	Elem *no = *li, *aux, *ult = *li;
	while(no != NULL){
		aux = no->prox;
		no->prox = no->ant;
		no->ant = aux;
		ult = no;
		no = aux;
	}
	*li = ult;
}
/*QUESTÃO 8*/
/*
 * Condição de parada: ini == fim (tamanho ímpar, os dois se encontram no meio) ou
 * ini->ant == fim (tamanho par, os dois se cruzaram). Qualquer uma das duas
 * significa que todos os pares já foram comparados.
 * Custo: O(n), com n-1 passos para achar o último e cerca de n/2 comparações.
 * Na lista simples não dá para usar a mesma estratégia diretamente porque não existe
 * ant, então o ponteiro do fim não consegue ir pra tras. Para cada recuo seria preciso
 * percorrer de novo desde o início (O(n^2) no total)
 */
int eh_palindromo(Lista* li){
	if(li == NULL)
		return 0;
	if((*li) == NULL)
		return 1;
	Elem *ini = *li, *fim = *li;
	while(fim->prox != NULL)
		fim = fim->prox;
	while(ini != fim && ini->ant != fim){
		if(ini->dados.matricula != fim->dados.matricula)
			return 0;
		ini = ini->prox;
		fim = fim->ant;
	}
	return 1;
}
