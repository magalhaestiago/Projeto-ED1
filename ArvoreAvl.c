#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAvl.h"
#include <time.h>

// Declaração do TAD nó da árvore AVL, contém altura, um nó aponta a direita e um nó aponta a esquerda, e um atributo reservado para as informações do usuário
typedef struct noavl{
    Usuario *user;
    struct no *esquerdo, *direito;
    int altura;
}NoAVL;

// Função para criar um nó com um usuário sendo passado como parâmetro, retorna este usuário com os atributos do usuário alocados.
NoAVL* novoNo(Usuario *x){
    NoAVL *novo = malloc(sizeof(NoAVL)); // Aloca espaço de memória para um novo nó

    if(novo){ // Testa se a alocação de memória foi possível
        novo->user = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    }
    else // Caso não tenha sido possível alocar memória, retorna NULL
        return NULL;
    return novo;
}

/* Funções auxiliares */
// Função auxiliar para descobrir o maior valor entre dois números, útil para calcular altura da árvore e subárvores
int maior(int a, int b){
    return (a > b)? a: b; // Operador ternário (caso a seja maior que b retorne a, senão retorne b)
}


// Função que retorna a altura de um nó
int alturaDoNo(NoAVL *no){
    if(no == NULL) // Caso o nó seja nulo retorna -1
        return -1;
    else
        return no->altura; // Se não retorna o campo altura
}

// Calcula e retorna o fator de balanceamento de um nó
int fatorDeBalanceamento(NoAVL *no){
    if(no)
        return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
    else
        return 0;
}

/* Funções de rotação */
// Função de rotação para a esquerda

NoAVL* rotacaoEsquerda(NoAVL *raiz){
    NoAVL *proximaRaiz, *filho; // Cria dois nós auxiliares
    // proximaRaiz será a nova raiz e o filho será seu filho a esquerda (caso tenha algum valor será necessário salvá-lo, mas tem possibilidade de ser NULL)

    proximaRaiz = raiz->direito; // Colocando a variavel "proximaRaiz" como o filho da raiz a direita
    filho = proximaRaiz->esquerdo; // Colocando a variavel "filho" como o filho da proximaRaiz a esquerda

    proximaRaiz->esquerdo = raiz; // Colocando a atual raíz para ser filho a esquerda da próxima raiz 
    raiz->direito = filho; // Colocando o filho a direita da "atual" raíz para ser o filho a esquerda da variavel "proximaRaiz" 
    // Recalculando a altura da antiga raiz e da nova raiz
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->esquerdo)) + 1; 
    proximaRaiz->altura = maior(alturaDoNo(proximaRaiz->esquerdo), alturaDoNo(proximaRaiz->direito)) + 1;
    // Retorna a nova raiz
    return proximaRaiz;
}

// Função de rotação para a direita
NoAVL* rotacaoDireita(NoAVL *raiz){
    NoAVL *proximaRaiz, *filho; // Cria dois nós auxiliares

    proximaRaiz = raiz->esquerdo; // Colocando a variavel "proximaRaiz" como o filho da raiz a esquerda
    filho = proximaRaiz->direito; // Colocando a variavel "filho" como o filho da proximaRaiz a esquerda

    proximaRaiz->direito = raiz; // Colocando a atual raíz para ser filho a direita da próxima raiz
    raiz->esquerdo = filho; // Colocando o filho a esquerda da "atual" raíz para ser o filho a direita da variavel "proximaRaiz"
    // Recalculando a altura da antiga raiz e da nova raiz
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->esquerdo)) + 1;
    proximaRaiz->altura = maior(alturaDoNo(proximaRaiz->esquerdo), alturaDoNo(proximaRaiz->direito)) + 1;
    // Retorna a nova raiz
    return proximaRaiz;
}

// Função de rotação dupla à esquerda
NoAVL* rotacaoEsquerdaDireita(NoAVL *raiz){
    raiz->esquerdo = rotacaoEsquerda(raiz->esquerdo); 
    return rotacaoDireita(raiz);
}

// Função de rotação dupla à direita
NoAVL* rotacaoDireitaEsquerda(NoAVL *raiz){
    raiz->direito = rotacaoDireita(raiz->direito);
    return rotacaoEsquerda(raiz);
}


// Função para balancear a árvore após uma inserção ou remoção
NoAVL* balancear(NoAVL *raiz){
    int fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação à direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação dupla à esquerda
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação dupla à direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

// Função de inserção
NoAVL* inserir(NoAVL *raiz, Usuario *x){
    
    if(raiz == NULL) // Se raiz for nulo, apenas cria um novo nó onde será a árvore avl
        return novoNo(x);
    else{ // Testando se o telefone do Usuário passado é maior ou menor do que o usuário do nó raíz da árvore...
        if(x->telefone < raiz->user->telefone) // ... se for menor, adiciona de forma recursiva no filho a esquerda
            raiz->esquerdo = inserir(raiz->esquerdo, x);
        else if(x->telefone > raiz->user->telefone) // ... se for maior, adiciona de forma recursiva no filho a direita
            raiz->direito = inserir(raiz->direito, x);
        else
            printf("\nInsercao nao realizada!\nO elemento %ld ja existe!\n", x->telefone);
    }

    // Altera a altura do Nó raíz
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    // Verifica a necessidade de rebalancear a árvore após a inserção
    raiz = balancear(raiz);

    return raiz; // Retorna a raíz da arvore agora com um um outro no inserido
}






// Função de remoção
NoAVL* remover(NoAVL *raiz, long int telefone) {
    
    if(raiz == NULL){ // Se raiz é nulo, nenhum telefone foi cadastrado, portanto não será encontrado, apenas retorna NULL
        printf("Valor nao encontrado!\n");
        return NULL; 
    } else { 
        if(raiz->user->telefone == telefone)  {
            // Remover nós folhas
            if(raiz->esquerdo == NULL && raiz->direito == NULL) { // Checando se o nó não tem filhos, (condições necessárias para ser nó folha)
                free(raiz); // Libera raíz
                printf("Elemento folha removido: %ld !\n", telefone);
                return NULL; // Retorna Nulo
            }
            else{
                // Remover nós que possuem 2 filhos
                if(raiz->esquerdo != NULL && raiz->direito != NULL){ // Checando se o nó possui os 2 filhos
                    NoAVL *aux = raiz->esquerdo;
                    while(aux->direito != NULL)
                        aux = aux->direito;
                    Usuario *usuarioAux;
                    aux->user = raiz->user;

                    raiz->user = aux->user;
                    aux->user = usuarioAux;
                    printf("Elemento trocado: %ld !\n", telefone);
                    raiz->esquerdo = remover(raiz->esquerdo, telefone);
                    return raiz;
                }
                else{
                    // Remover nó que possui apenas 1 filho
                    NoAVL *aux;
                    if(raiz->esquerdo != NULL)
                        aux = raiz->esquerdo; // Checando se o nó possui apenas 1 filho...
                    else
                        aux = raiz->direito; // Checando se o nó possui apenas 1 filho...
                    free(raiz); // Libera raíz
                    printf("Elemento com 1 filho removido: %ld !\n", telefone);
                    return aux;
                }
            }
        } else { 
            if(telefone < raiz->user->telefone)
                raiz->esquerdo = remover(raiz->esquerdo, telefone);
            else
                raiz->direito = remover(raiz->direito, telefone);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

        // verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
    }
}

void imprimirDadosUsuario(Usuario *user){ // Função auxiliar utilizada para imprimir os dados de um certo usuário
    printf("%s [%d] %ld %s\n", user->nome,user->ddd, user->telefone, user->endereco);
}


// Imprimir pré-ordem, sequência: dados da raiz, dados do filho a esquerda, dados do filho a direita
void imprimirPreOrdem(NoAVL *raiz){
    if(raiz != NULL){
        imprimirDadosUsuario(raiz->user);
        imprimirPreOrdem(raiz->esquerdo);
        imprimirPreOrdem(raiz->direito);
    }
}

// Imprimir pré-ordem, sequência: dados da esquerda, dados da raiz, dados do filho a direita
void imprimirEmOrdem(NoAVL *raiz){
    if(raiz != NULL){
        imprimirEmOrdem(raiz->esquerdo);
        imprimirDadosUsuario(raiz->user);
        imprimirEmOrdem(raiz->direito);
    }
}

// Imprimir pré-ordem, sequência: dados da esquerda, dados do filho a direita, dados da raiz
void imprimirPosOrdem(NoAVL *raiz){
    if(raiz != NULL){
        imprimirPosOrdem(raiz->esquerdo);
        imprimirPosOrdem(raiz->direito);
        imprimirDadosUsuario(raiz->user);
    }
}


void imprimirDDDUsuario(NoAVL *raiz){
    printf("\t%d\n", raiz->user->ddd);
}

void printarBusca(NoAVL* raiz, long int telefoneBuscado){
    if(raiz == NULL){
        return 0;
    } else
    if (telefoneBuscado == raiz->user->telefone){
        imprimirDadosUsuario(raiz->user);
    } else if(telefoneBuscado < raiz->user->telefone){
        printarBusca(raiz->esquerdo, telefoneBuscado);
    } else {
        printarBusca(raiz->direito, telefoneBuscado);
        
    }
}

int busca(NoAVL *raiz, long int telefoneBuscado){
    if(raiz == NULL){
        return 0;
    } else 
    if(telefoneBuscado == raiz->user->telefone){
        return 1;
    } else if(telefoneBuscado < raiz->user->telefone){
        return busca(raiz->esquerdo, telefoneBuscado);
    } else {
        return busca(raiz->direito, telefoneBuscado);
    }
}

void printTelefonesEmOrdem(NoAVL *raiz){
    if(raiz != NULL){
        printTelefonesEmOrdem(raiz->esquerdo);
        printf("\t%d\n", raiz->user->telefone);
        printTelefonesEmOrdem(raiz->direito);
    }
}

