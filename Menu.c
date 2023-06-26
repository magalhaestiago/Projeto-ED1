#include <stdio.h>
#include <stdlib.h>
#include "TableHash.c"
#include <time.h>

#define NUM_NUMEROS 3
#define NUM_DIGITOS 9

int main(){
    int opcao;
    long int valor;
    int ddd;
    Usuario *u;
    Lista tabela[TAM];

    clock_t inicio, fim;    
    double tempo_decorrido;
    double segundos;

    char numeros[NUM_NUMEROS][NUM_DIGITOS + 1];
    srand(time(NULL));

    inicializarTabela(tabela);


    do{
        printf("\n\t---->Sistema de telefonia INETSYS<----\t\n");
        printf("\n\t1 - Inserir novo usuario\n\t2 - Remover usuario cadastrado\n\t3 - Imprimir lista de usuarios por DDD\n\t4 - Imprimir Tabela de DDD's\n\t6 - Encontrar dados usuario pelo telefone\n\t7 - Buscar telefone\n\t0 - Sair\n\t");
        scanf("%d", &opcao);

        switch(opcao){
            case 0:
            printf("Saindo!");

            break;
            
            case 1:
            //inicio = clock ();
            u = malloc(sizeof(Usuario));

            for (int i = 0; i < NUM_NUMEROS; i++) {
                gerarNumeroAleatorio(numeros[i]);
            }

            
            for (int i = 0; i < NUM_NUMEROS; i++) {
                printf("\t[X] - %s\n",  numeros[i]);
            }
            printf("\tDigite um dos numeros acima ou crie um seu: ");
            
            scanf("%d", &u->telefone);
            printf("\tDigite o nome a ser inserido: ");
            scanf("%s", u->nome);    
            printf("\tDigite o endereco a ser inserido: ");
            scanf("%s", u->endereco);
            printf("\tDigite o DDD: ");
            scanf("%d", &u->ddd);

            
            if(tabela[calcularFuncaoHash(u->ddd)].tamanho != 0){
                
                tabela[calcularFuncaoHash(u->ddd)].inicio->elementos = inserir(tabela[calcularFuncaoHash(u->ddd)].inicio->elementos, u);
                
            } 
            
            else {
                NoAVL* raiz = NULL;
                raiz = inserir(raiz, u);
                inserirHash(tabela, raiz);
            }

            fim = clock ();
            tempo_decorrido = ((float)(inicio - fim)/CLOCKS_PER_SEC);
            
            printf("%11f\n", tempo_decorrido); 
            
            break;

            case 2:
            printf("Digite o DDD do telefone que vc deseja remover: ");
            scanf("%d", &ddd);
            if(checandoDDDExiste(tabela,ddd) == 0){
                printf("\t\nDDD inexistente!\n");
                break;
            }
            printf("Digite o telefone que vc deseja remover: ");
            scanf("%ld", &valor);

            if(busca(tabela[calcularFuncaoHash(ddd)].inicio->elementos, valor)){
                tabela[calcularFuncaoHash(ddd)].inicio->elementos = remover(tabela[calcularFuncaoHash(ddd)].inicio->elementos, valor);
            } else {
                printf("Nao existe\n");
            }

            break;



            
            case 3:
            printf("\tDigite o DDD:\n");
            scanf("%d", &ddd);
            if(checandoDDDExiste(tabela,ddd) == 0){
                printf("\t\nDDD inexistente!\n");
                break;
            }
            printf("\t1 - Pre-ordem\n\t2 - Em Ordem (De telefone)\n\t3 - Pos-Ordem\n");
            scanf("%ld", &valor);
            escolhaImprimir(tabela[calcularFuncaoHash(ddd)].inicio->elementos, valor);

            break;

            case 4:
            imprimirHash(tabela);
            break;

            case 6:
            printf("Digite o DDD de onde vc busca: ");
            scanf("%d", &ddd);
            if(checandoDDDExiste(tabela,ddd) == 0){
                printf("\t\nDDD inexistente!\n");
                break;
            }
            printf("Digite o telefone que vc busca: ");
            scanf("%ld", &valor);


            if(busca(tabela[calcularFuncaoHash(ddd)].inicio->elementos, valor)){
                printarBusca(tabela[calcularFuncaoHash(ddd)].inicio->elementos, valor);
            } else {
                printf("Nao existe\n");
            }
            break;
            case 7:

            
            
            break;
            

            default:
            break;

        }
    }while(opcao != 0);
}



int buscaAproximada(int numero, int valorBuscado) {
    char strNumero[20];
    char strValorBuscado[20];
    
    sprintf(strNumero, "%d", numero);
    sprintf(strValorBuscado, "%d", valorBuscado);
    
    return strstr(strNumero, strValorBuscado) != NULL;
}

struct Telefone {
    long int numero;
};




int numeroRepetido(NoAVL* raiz, int numero){
    NoAVL* aux = raiz;
    while(aux != NULL){
        if(raiz->user->telefone == numero){
            return 1;
        }
        return 0;
    }
}

long int* gerarSugestao(NoAVL* raiz){
    srand(time(NULL));
    long int *vetorNumerosTelefones;

    for(int i = 0; i < 3; i++){
        do{
        vetorNumerosTelefones[i] = 990000000 + rand() % 100000000;
        } while(numeroRepetido(raiz, vetorNumerosTelefones[i]));
    }

    return vetorNumerosTelefones;
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
        printf("arvoreVazia!\n");
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

