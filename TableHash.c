#include "ArvoreAvl.c"
#include "TableHash.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM 131 /* Definindo o tamanho da tabela Hash, o critério utilizado foi 
que no Brasil existem 66 DDD's, 66*2 = 132, e 131 é o número primo mais 
próximo de 132 */

/*Declaração do TAD no da tabela Hash, cada posição da tabela Hash terá um desses
onde terá um campo que aponta para arvore avl e um campo que aponta para a
proxima posicao da tabela */
typedef struct noHash{
    NoAVL *elementos;
    struct noHash *proximo;
}NoHash;

// Função para inicializar a lista encadeada que estará dentro de cada posição da tabela hash
void inicializarLista(Lista *list){
    list->inicio = NULL; // Como está inicializando, o campo inicio será Nulo...
    list->tamanho = 0; // ... e o tamanho 0
}

// Função para inicializar a tabela hash, apenas rodando a inicializarLista em todas as posições da tabela
void inicializarTabela(Lista t[]){
    for(int i = 0; i < TAM; i++){
        inicializarLista(&t[i]);
    }
}

// Função para inserir na lista encadeada que estará dentro de cada posição da tabela hash
void inserirLista(Lista *list, NoAVL* raiz){
    NoHash *novo = malloc(sizeof(NoHash)); // Cria um Nó de tabela hash alocando memória para ele
    
    if(novo != NULL){ // Caso a memória seja alocada com sucesso, passa o nó raiz da arvore a ser inserida na tabela hash (Na verdade na lista dentro da tabela hash para que seja realizado o encadeamento separado)
        novo->elementos = raiz; // Adiciona o nó de árvore avl na lista
        novo->proximo = list->inicio; // Passa o nó inicial da lista encadeada para ser o proximo do novo nó inserido
        list->inicio = novo; // Passa o novo nó da lista para o inicio da lista
        list->tamanho++; // Atualiza a quantidade de elementos da lista encadeada dentro da posição da tabela hash

    } else {
        return;
    }
}

// Função para inserir um elemento na tabela hash
void inserirHash(Lista t[], NoAVL *raiz){
    int id = calcularFuncaoHash(raiz->user->ddd);
    inserirLista(&t[id], raiz);
}

// Função para buscar um elemento na lista encadeada com base no DDD
int buscarLista(Lista *list, int ddd){
    NoHash *aux = list->inicio;
    while(aux != NULL && aux->elementos->user->ddd != ddd) // Vai iterando o NoHash auxiliar até que o valor do ddd do aux seja igual ao do ddd
        aux = aux->proximo;
    if(aux != NULL){
        return aux->elementos->user->ddd;
    }
    return 0;
}

// Função para imprimir os elementos da lista encadeada
void imprimirLista(Lista *list){
    NoHash *aux = list->inicio;
    printf("Tamanho da lista: %d\n",list->tamanho);
    while(aux != NULL){ // Utiliza o noHash auxiliar de forma iterativa e vai printando os dados do usuario
        imprimirDDDUsuario(aux->elementos);
        aux = aux->proximo;
    }
}

// Função que imprime todas as listas em todas posições da tabela hash (apenas os DDD's presentes)
void imprimirHash(Lista t[]){
    for(int i = 0; i < TAM; i++){
        printf("%3d = ", i);
        imprimirLista(&t[i]);
        printf("\n");
    }
}


// Função Hash que utilizamos, consiste em [ddd MOD tamanho da tabela]
int calcularFuncaoHash(int chave) {
    return chave % TAM; // 85 % 10 = 5
}


// Função para buscar um elemento na tabela hash com base no DDD (função auxiliar fundamental para outras funções)
int buscaTabela(Lista t[], int ddd){
    int id = calcularFuncaoHash(ddd);
    return buscarLista(&t[id], ddd);
}



// A função é usada para verificar se um DDD existe na tabela hash
int checandoDDDExiste(Lista t[], int ddd){
    int id = calcularFuncaoHash(ddd);

    if(t[id].tamanho != 0){
        return 1;
    } else {
        return 0;
    }
}



