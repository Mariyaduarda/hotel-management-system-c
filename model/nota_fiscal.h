#ifndef NOTA_FISCAL_H
#define NOTA_FISCAL_H

#include "../common.h"

#define MAX_ITENS_NOTA 100

#define NF_AVISTA  1
#define NF_APRAZO  2

typedef struct {
    int   idProduto;
    char  descricao[100];
    float precoCusto;
    int   quantidade;
    float subtotal;
    float fretePorProduto;
    float impostoPorProduto;
    float precoVenda;         // calculado automaticamente
} ItemNotaFiscal;

typedef struct {
    int           id;
    int           idFornecedor;
    char          data[12];
    float         frete;
    float         imposto;
    ItemNotaFiscal itens[MAX_ITENS_NOTA];
    int           numItens;
    float         totalNota;
    int           formaPagamento;  // NF_AVISTA ou NF_APRAZO
    float         valorEntrada;    // se a prazo
    int           numParcelas;     // se a prazo
    int           ativo;
} TipoNotaFiscal;

typedef struct ListaNotaFiscal {
    TipoNotaFiscal    nota;
    struct ListaNotaFiscal *proximo;
} ListaNotaFiscal;

void            NotaFiscalInit(TipoNotaFiscal *nota);
int             NotaFiscalCriar(ListaNotaFiscal **lista, TipoNotaFiscal nota);
TipoNotaFiscal *NotaFiscalBuscar(ListaNotaFiscal **lista, int id);
void            NotaFiscalListar(ListaNotaFiscal **lista, int id);

// Calcula frete/imposto/precoVenda por produto
void NotaFiscalCalcular(TipoNotaFiscal *nota, float margemLucro);

void NotaFiscalListaLiberar(ListaNotaFiscal *lista);

int NotaFiscalSalvarTxt(ListaNotaFiscal *lista);
int NotaFiscalSalvarBin(ListaNotaFiscal *lista);
int NotaFiscalLerTxt(ListaNotaFiscal **lista);
int NotaFiscalLerBin(ListaNotaFiscal **lista);

#endif // NOTA_FISCAL_H