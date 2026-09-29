#define MAX 100
struct produto {
    int codigo;
    char nome[30];
    float preco;
};
typedef struct lista Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int busca_lista_pos(Lista* li, int pos, struct produto *p);
int busca_lista_mat(Lista* li, int cod, struct produto *p);
int insere_lista_final(Lista* li, struct produto p);
int insere_lista_inicio(Lista* li, struct produto p);
int insere_lista_ordenada(Lista* li, struct produto p);
int remove_lista(Lista* li, int cod);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_cheia(Lista* li);
int lista_vazia(Lista* li);
