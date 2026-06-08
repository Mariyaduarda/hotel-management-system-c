#ifndef CAIXA_H
#define CAIXA_H

#include "../common.h"

#define CAIXA_ENTRADA 1
#define CAIXA_SAIDA 2

#define PAGAMENTO_DINHEIRO 1
#define PAGAMENTO_CARTAO 2

/* ── Caixa Dados ────────────────────────────── */
typedef struct {
    int id;
    char data[12];
    int tipo; // Entrada ou Saída
    double valor;
    char descricao[200];
    int metodoPagamento; // Dinheiro ou Cartão
    int idReferencia; // ID da reserva ou acomodação relacionada (opcional)
    int ativo; // 1 para ativo, 0 para inativo (excluído logicamente)
} TipoCaixa;


/* ── Lista Caixa ────────────────────────────── */
typedef struct ListaCaixa {
    TipoCaixa caixa;
    struct ListaCaixa *proximo;
} ListaCaixa;

void CaixaInit(TipoCaixa *caixa);
int CaixaInserir(ListaCaixa **lista, TipoCaixa caixa);
TipoCaixa CaixaBuscar(ListaCaixa **lista, int id);
int CaixaListar(ListaCaixa **lista, char *dataInicio, char *dataFim);
double CaixaSaldo(ListaCaixa **lista);
void CaixaListaLiberar(ListaCaixa *lista);

/* ── Persistencia de Dados ────────────────────────────── */
int CaixaSalvarTxt(ListaCaixa *lista);
int CaixaSalvarBin(ListaCaixa *lista);
int CaixaLerTxt(ListaCaixa **lista);
int CaixaLerBin(ListaCaixa **lista);

#endif // CAIXA_H