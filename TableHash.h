
typedef struct noHash NoHash;

typedef struct {
    NoHash *inicio;
    int tamanho;
} Lista;

void inicializarLista(Lista *list);
void inserirLista(Lista *list, NoAVL* raiz);

int buscarLista(Lista *list, int ddd);
void imprimirLista(Lista *list);
void inicializarTabela(Lista t[]);
int calcularFuncaoHash(int chave);
void inserirHash(Lista t[], NoAVL *raiz);
int buscaTabela(Lista t[], int ddd);

void imprimirHash(Lista t[]);
//int checandoDDDExiste


