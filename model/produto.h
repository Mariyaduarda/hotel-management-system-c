#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int   id;
    char  descricao[100];
    int   estoque;
    int   estoqueMinimo;
    float precoCusto;
    float precoVenda;
    int   ativo;
} TipoProduto;

typedef struct ListaProduto {
    struct ListaProduto *proximo;
    TipoProduto produto;
} ListaProduto;

// Funcoes base
void ProdutoInit(TipoProduto *produto);
void ProdutoListaInit(ListaProduto *lista);

int  ProdutoCriar(ListaProduto **lista, TipoProduto produto);
void ProdutoListar(ListaProduto **lista, int id);
TipoProduto* ProdutoBuscar(ListaProduto **lista, int id);
int  ProdutoExcluir(ListaProduto **lista, int id);
int  ProdutoAtualizar(ListaProduto **lista, int id, int op);
void ProdutoListaLiberar(ListaProduto *lista);

// Funcoes de arquivo
int ProdutoSalvarTxt(ListaProduto *lista);
int ProdutoSalvarBin(ListaProduto *lista);
int ProdutoLerTxt(ListaProduto **lista);
int ProdutoLerBin(ListaProduto **lista);

#endif // PRODUTO_H