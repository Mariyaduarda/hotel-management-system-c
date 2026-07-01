#ifndef RELATORIO_H
#define RELATORIO_H

#include "../model/hospede.h"
#include "../model/acomodacao.h"
#include "../model/categoria_acomodacao.h"
#include "../model/reserva.h"
#include "../model/produto.h"
#include "../model/venda.h"
#include "../model/caixa.h"
#include "../model/contas_receber.h"
#include "../model/contas_pagar.h"

// Destino do relatorio
#define RELATORIO_TELA    0
#define RELATORIO_ARQUIVO 1

typedef struct {
    int destino;        // RELATORIO_TELA ou RELATORIO_ARQUIVO
    char caminho[200];  // caminho do arquivo CSV, se destino == RELATORIO_ARQUIVO
} ConfigRelatorio;

// ── Vendas ────────────────────────────────────
void RelatorioVendas(ListaVenda **lista,
                      ConfigRelatorio *cfg,
                      int formaPagamento); // 0 = todas, VENDA_AVISTA ou VENDA_ANOTAR

// ── Contas a Receber ──────────────────────────
void RelatorioContasReceber(ListaContaReceber **lista,
                             ConfigRelatorio *cfg,
                             int idMin, int idHospedeMax,  // faixa de codigo do hospede
                             const char *dataInicio, const char *dataFim); // periodo

// ── Contas a Pagar ────────────────────────────
void RelatorioContasPagar(ListaContaPagar **lista,
                           ConfigRelatorio *cfg,
                           int idFornecedorMin, int idFornecedorMax,
                           const char *dataInicio, const char *dataFim); // vencimento

// ── Movimentacao de Caixa ─────────────────────
void RelatorioMovimentacaoCaixa(ListaCaixa **lista,
                                 ConfigRelatorio *cfg,
                                 const char *dataInicio, const char *dataFim);

// ── Hospedes ──────────────────────────────────
void RelatorioHospedes(ListaHospede **lista,
                       ConfigRelatorio *cfg,
                       int idMin, int idMax,   // faixa de codigos (0,0 = todos)
                       const char *sexo);       // "" = todos

// ── Acomodacoes ───────────────────────────────
void RelatorioAcomodacoes(ListaAcomodacao **listaAcom,
                           ListaCategoria  **listaCat,
                           ConfigRelatorio *cfg,
                           int idMin, int idMax,
                           int idCategoria,          // 0 = todas
                           const char *dataDisponivel); // "" = sem filtro de data

// ── Reservas ──────────────────────────────────
void RelatorioReservas(ListaReserva **lista,
                        ConfigRelatorio *cfg,
                        int idHospede,       // 0 = todos
                        int idAcomodacao,    // 0 = todas
                        const char *periodoInicio,  // "" = sem filtro
                        const char *periodoFim);

// ── Produtos ──────────────────────────────────
void RelatorioProdutos(ListaProduto **lista,
                        ConfigRelatorio *cfg,
                        int idMin, int idMax);

void RelatorioProdutosEstoqueMinimo(ListaProduto **lista,
                                     ConfigRelatorio *cfg,
                                     int idMin, int idMax);

// ── Movimentacao de acomodacoes ───────────────
void RelatorioMovimentacaoAcomodacoes(ListaReserva    **listaReserva,
                                       ListaAcomodacao **listaAcom,
                                       ListaCategoria  **listaCat,
                                       ConfigRelatorio *cfg,
                                       int idAcomodacao); // 0 = todas

#endif // RELATORIO_H