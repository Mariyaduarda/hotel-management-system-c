#ifndef CONTAS_RECEBER_H
#define CONTAS_RECEBER_H

#include "../common.h"

#define CR_PENDENTE  1
#define CR_RECEBIDO  2

typedef struct {
    int   id;
    int   idHospede;
    char  descricao[150];
    float valor;
    char  dataVencimento[12];   // data que a operadora paga ao hotel
    char  dataRecebimento[12];  // preenchida ao dar baixa
    int   status;               // CR_PENDENTE ou CR_RECEBIDO
    int   ativo;
} TipoContaReceber;

typedef struct ListaContaReceber {
    TipoContaReceber    conta;
    struct ListaContaReceber *proximo;
} ListaContaReceber;

void              ContaReceberInit(TipoContaReceber *conta);
int               ContaReceberCriar(ListaContaReceber **lista, TipoContaReceber conta);
TipoContaReceber *ContaReceberBuscar(ListaContaReceber **lista, int id);
void              ContaReceberListar(ListaContaReceber **lista, int idHospede,
                                      const char *dataInicio, const char *dataFim);
int               ContaReceberBaixar(ListaContaReceber **lista, int id,
                                      const char *dataRecebimento);
void              ContaReceberListaLiberar(ListaContaReceber *lista);

int ContaReceberSalvarTxt(ListaContaReceber *lista);
int ContaReceberSalvarBin(ListaContaReceber *lista);
int ContaReceberLerTxt(ListaContaReceber **lista);
int ContaReceberLerBin(ListaContaReceber **lista);

#endif // CONTAS_RECEBER_H