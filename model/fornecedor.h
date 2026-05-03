#ifndef FORNECEDOR_H
#define FORNECEDOR_H

typedef struct {
    int  id;
    char nomeFantasia[100];
    char razaoSocial[100];
    char inscricaoEstadual[30];
    char cnpj[20];
    char endereco[150];
    char telefone[20];
    char email[50];
    int  ativo;
} TipoFornecedor;

typedef struct ListaFornecedor {
    struct ListaFornecedor *proximo;
    TipoFornecedor fornecedor;
} ListaFornecedor;

// Funcoes base
void FornecedorInit(TipoFornecedor *fornecedor);
void FornecedorListaInit(ListaFornecedor *lista);

int  FornecedorCriar(ListaFornecedor **lista, TipoFornecedor fornecedor);
void FornecedorListar(ListaFornecedor **lista, int id);
TipoFornecedor* FornecedorBuscar(ListaFornecedor **lista, int id);
int  FornecedorExcluir(ListaFornecedor **lista, int id);
int  FornecedorAtualizar(ListaFornecedor **lista, int id, int op);
void FornecedorListaLiberar(ListaFornecedor *lista);

// Funcoes de arquivo
int FornecedorSalvarTxt(ListaFornecedor *lista);
int FornecedorSalvarBin(ListaFornecedor *lista);
int FornecedorLerTxt(ListaFornecedor **lista);
int FornecedorLerBin(ListaFornecedor **lista);

#endif // FORNECEDOR_H