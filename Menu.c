/* Funções auxiliares e complementares abaixo da "main" */


/* Inserção das bibliotecas necessárias */
#include <stdio.h>
#include <stdlib.h>
#include "TableHash.c" // Biblioteca interna feita pelo grupo, contém todas estruturas necessárias
#include <time.h>

/* Definição de constantes que serão necessárias para a função de sugestão de números solicitado no projeto */
#define NUM_NUMEROS 3 // 3 define a quantidade de sugestões que serão feitas em uma inserção
#define NUM_DIGITOS 9 // 9 define a quantidade de digitos que é necessário para o campo telefone

int main(){
    /* Declaração de variáveis */
    /* Aprendemos muito bem na disciplina de Conceitos de Linguagem de Programação com a professora Ana Luiza que a declaração de variáveis globais comprometem a segurança do código e é considerado uma má prática de programação, porém infelizmente a linguagem C não permite a criação de variáveis dentro do (switch case), onde fizemos o menu do programa*/

    int opcao; // Variável utilizada para navegar pelo menu
    long int auxTelefone; // Variável utilizada para auxiliar nas funções que requerem "telefone" como parâmetro
    int ddd; // Variável utilizada para auxiliar nas funções que requerem "ddd" como parâmetro
    Usuario *u; // Declaração do TAD usuário, para que dentro do menu seja manipulado
    Lista tabela[TAM]; // Declaração da tabela Hash com tamanho definido

    

    char numeros[NUM_NUMEROS][NUM_DIGITOS + 1];
    srand(time(NULL));

    // Inicializar a tabela hash com todos elementos como NULL
    inicializarTabela(tabela);


    /* Menu utilizando (do while para repetiçao e switch case para escolha)*/
    do{
        printf("\n\t---->Sistema de telefonia INETSYS<----\t\n");
        printf("\n\t1 - Inserir novo usuario\n\t2 - Remover usuario cadastrado\n\t3 - Imprimir lista de usuarios por DDD\n\t4 - Imprimir Tabela de DDD's\n\t5 - Encontrar dados usuario pelo telefone\n\t0 - Sair\n\t");
        scanf("%d", &opcao);

        switch(opcao){
            case 0: // Condição de saída e parada do programa
            printf("Saindo!");

            break;
            
            case 1: // Condição para inserir um novo usuário
            
            u = malloc(sizeof(Usuario)); // Aloca memória, assim criando um novo usuário e armazenando-o na variável "u"

             /* Gerando números aleatórios utilizando a biblioteca time.h */
            for (int i = 0; i < NUM_NUMEROS; i++) {
                gerarNumeroAleatorio(numeros[i]);
            }
            for (int i = 0; i < NUM_NUMEROS; i++) {
                printf("\t[X] - %s\n",  numeros[i]);
            }

            /* Etapa em que o usuário poderá adicionar os dados */
            printf("\tDigite um dos numeros acima ou crie um seu: ");
            scanf("%d", &u->telefone);
            printf("\tDigite o nome a ser inserido: ");
            scanf("%s", u->nome);    
            printf("\tDigite o endereco a ser inserido: ");
            scanf("%s", u->endereco);
            printf("\tDigite o DDD: ");
            scanf("%d", &u->ddd);

            // Checando se a lista encadeada presente na posição calculada da tabela hash já possui elementos, se sim apenas insere um novo...
            if(tabela[calcularFuncaoHash(u->ddd)].tamanho != 0){
                
                tabela[calcularFuncaoHash(u->ddd)].inicio->elementos = inserir(tabela[calcularFuncaoHash(u->ddd)].inicio->elementos, u);
                
            } 
            // .. senão, cria uma nova raiz e insere o usuário na raiz, e a raiz é inserida na tabela hash
            else {
                NoAVL* raiz = NULL;
                raiz = inserir(raiz, u);
                inserirHash(tabela, raiz);
            }

            
            
            
            
            break;

            case 2: // Condição para remover um usuário
            printf("Digite o DDD do telefone que vc deseja remover: ");
            scanf("%d", &ddd); // Coletando em que árvore o usuário está
            if(checandoDDDExiste(tabela,ddd) == 0){ // Checando se o essa árvore existe
                printf("\t\nDDD inexistente!\n");
                break;
            }
            printf("Digite o telefone que vc deseja remover: "); // Coletando o telefone do usuário que será removido
            scanf("%ld", &auxTelefone);

            if(busca(tabela[calcularFuncaoHash(ddd)].inicio->elementos, auxTelefone)){ // Checando se o telefone existe, caso exista remove...
                tabela[calcularFuncaoHash(ddd)].inicio->elementos = remover(tabela[calcularFuncaoHash(ddd)].inicio->elementos, auxTelefone);
            } else { // senão, apenas imprime:
                printf("Nao existe\n");
            }

            break;



            
            case 3: // Condição para impressão de uma árvore
            printf("\tDigite o DDD:\n");
            scanf("%d", &ddd); // Coletando em que árvore o usuário está
            if(checandoDDDExiste(tabela,ddd) == 0){ // Checando se o essa árvore existe
                printf("\t\nDDD inexistente!\n");
                break;
            }
            printf("\t1 - Pre-ordem\n\t2 - Em Ordem (De telefone)\n\t3 - Pos-Ordem\n"); // Oferecendo as opções possiveis para impressão para o usuário
            scanf("%ld", &auxTelefone); // Coletando a escolha
            escolhaImprimir(tabela[calcularFuncaoHash(ddd)].inicio->elementos, auxTelefone); // Executando a função "escolhaImprimir" passando como parâmetro os dados coletados acima, e realizando a impressão pedida pelo usuário

            break;

            case 4: // Condição de impressão da tabela Hash onde os DDD's estão
            imprimirHash(tabela); // Apenas imprime a tabela de DDD's completa
            break;

            case 5: // Condição para encontrar os dados do usuario pelo telefone e DDD
            printf("Digite o DDD de onde vc busca: ");
            scanf("%d", &ddd); // Coletando em que árvore o usuário está
            if(checandoDDDExiste(tabela,ddd) == 0){ // Checando se o essa árvore existe
                printf("\t\nDDD inexistente!\n");
                break;
            }
            printf("Digite o telefone que vc busca: "); // Coletando o telefone que está sendo buscado
            scanf("%ld", &auxTelefone);


            if(busca(tabela[calcularFuncaoHash(ddd)].inicio->elementos, auxTelefone)){ // Checando se o telefone existe
                printarBusca(tabela[calcularFuncaoHash(ddd)].inicio->elementos, auxTelefone);
            } else { // Se não, apenas imprime:
                printf("Nao existe\n");
            }
            break;
            default:
            printf("\tOpcao invalida!\n");
            break;

        }
    }while(opcao != 0);
}









// Função auxiliar da main, que permite o usuario escolher como vai imprimir a arvore
void escolhaImprimir(NoAVL *raiz, int escolha){
    if(raiz != NULL){
        switch(escolha){
        case 1:
        imprimirPreOrdem(raiz);
        break;
        case 2:
        imprimirEmOrdem(raiz);
        break;
        case 3:
        imprimirPosOrdem(raiz);
        break;
        default:
        printf("Opcao invalida!\n");
        break;
    }
    } else {
        printf("arvore Vazia!\n");
    }
    
}


void gerarNumeroAleatorio(char* numero) {
    // Começa com o número 9
    numero[0] = '9';

    // Gera os dígitos restantes
    for (int i = 1; i < NUM_DIGITOS; i++) {
        // Gera um dígito aleatório entre 0 e 9
        int digito = rand() % 10;

        // Converte o dígito para o formato de caractere e adiciona ao número
        numero[i] = '0' + digito;
    }

    // Termina a string com o caractere nulo
    numero[NUM_DIGITOS] = '\0';
}

