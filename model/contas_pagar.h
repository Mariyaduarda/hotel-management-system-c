#ifndef CONTAS_PAGAR_H
#define CONTAS_PAGAR_H

#include "../common.h"

#define CP_PENDENTE 1
#define CP_PAGO     2

typedef struct {
    int   id;
    int   idFornecedor;
    int   idNotaFiscal;
    char  descricao[150];
    float valor;
    char  dataVencimento[12];
    char  dataPagamento[12];   // preenchida ao dar baixa
    int   numeroParcela;
    int   totalParcelas;
    int   status;              // CP_PENDENTE ou CP_PAGO
    int   ativo;
} TipoContaPagar;

typedef struct ListaContaPagar {
    TipoContaPagar    conta;
    struct ListaContaPagar *proximo;
} ListaContaPagar;

void             ContaPagarInit(TipoContaPagar *conta);
int              ContaPagarCriar(ListaContaPagar **lista, TipoContaPagar conta);
TipoContaPagar  *ContaPagarBuscar(ListaContaPagar **lista, int id);
void             ContaPagarListar(ListaContaPagar **lista, int idFornecedor,
                                   const char *dataInicio, const char *dataFim);
// Baixa: marca como pago e debita do caixa
int              ContaPagarBaixar(ListaContaPagar **lista, int id,
                                   const char *dataPagamento);
void             ContaPagarListaLiberar(ListaContaPagar *lista);

int ContaPagarSalvarTxt(ListaContaPagar *lista);
int ContaPagarSalvarBin(ListaContaPagar *lista);
int ContaPagarLerTxt(ListaContaPagar **lista);
int ContaPagarLerBin(ListaContaPagar **lista);

#endif // CONTAS_PAGAR_H