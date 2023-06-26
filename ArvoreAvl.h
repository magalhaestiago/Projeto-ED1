
typedef struct noavl NoAVL;

typedef struct {
  long int telefone;
  int ddd;
  char endereco[30];
  char nome[30];
}Usuario;

NoAVL* novoNo(Usuario *x);
NoAVL* inserir(NoAVL *raiz, Usuario *x);
NoAVL* remover(NoAVL *raiz, long int telefone);
void imprimirDadosUsuario(Usuario *user);
void imprimir(NoAVL *raiz, int nivel);
void imprimirEmOrdem(NoAVL *raiz);
void imprimirPosOrdem(NoAVL *raiz);
void imprimirPreOrdem(NoAVL *raiz);

NoAVL* rotacaoEsquerda(NoAVL *raiz);
NoAVL* rotacaoDireita(NoAVL *raiz);
NoAVL* rotacaoEsquerdaDireita(NoAVL *raiz);
NoAVL* rotacaoDireitaEsquerda(NoAVL *raiz);

NoAVL* balancear(NoAVL *raiz);
int maior(int a, int b);
int alturaDoNo(NoAVL *no);
int fatorDeBalanceamento(NoAVL *no);

