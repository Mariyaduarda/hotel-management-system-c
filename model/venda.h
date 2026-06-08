#ifndef VENDA_H
#define VENDA_H

#include "../common.h"

#define VENDA_AVISTA  1
#define VENDA_ANOTAR  2

#define MAX_ITENS_VENDA 50

/* ── Item de Venda Dados ────────────────────────────── */
typedef struct {
    int   idProduto;
    int   quantidade;
    float precoUnitario;
    float subtotal;
} ItemVenda;

/* ── Venda Dados ────────────────────────────── */
typedef struct {
    int       id;
    int       idHospede;
    char      data[12];
    ItemVenda itens[MAX_ITENS_VENDA];
    int       numItens;
    float     total;
    int       formaPagamento; // VENDA_AVISTA ou VENDA_ANOTAR
    int       lancadaNoCaixa; // 1 se ja foi para o caixa
    int       ativo;
} TipoVenda;

/* ── Lista de Vendas ────────────────────────────── */
typedef struct ListaVenda {
    TipoVenda       venda;
    struct ListaVenda *proximo;
} ListaVenda;

/* ── Funções de inicialização e outras ────────────────────────────── */
void       VendaInit(TipoVenda *venda);
int        VendaCriar(ListaVenda **lista, TipoVenda venda);
TipoVenda *VendaBuscar(ListaVenda **lista, int id);
void       VendaListar(ListaVenda **lista, int id);
void       VendaListaLiberar(ListaVenda *lista);

/* ── Persistencia de Dados ────────────────────────────── */
int VendaSalvarTxt(ListaVenda *lista);
int VendaSalvarBin(ListaVenda *lista);
int VendaLerTxt(ListaVenda **lista);
int VendaLerBin(ListaVenda **lista);

#endif // VENDA_H