#ifndef RELATORIO_VIEW_H
#define RELATORIO_VIEW_H

#include "../model/relatorio.h"
#include "../model/venda.h"
#include "../model/caixa.h"
#include "../model/contas_receber.h"
#include "../model/contas_pagar.h"

static void cabecalho(const char *titulo);

static void opcao(const char *num, const char *desc);

static void rodape(void);

static void separador(void);

// ──────────────────────────────────────────────
// Helper: destino do relatorio
// ──────────────────────────────────────────────

static ConfigRelatorio pedirDestino(void);

// ──────────────────────────────────────────────
// Menu
// ──────────────────────────────────────────────

void RelatorioMenuExibir(void);

// ──────────────────────────────────────────────
// Hospedes
// ──────────────────────────────────────────────

void RelatorioHospedesView(ListaHospede **lista);

// ──────────────────────────────────────────────
// Acomodacoes
// ──────────────────────────────────────────────

void RelatorioAcomodacoesView(ListaAcomodacao **listaAcom,
                               ListaCategoria  **listaCat);

// ──────────────────────────────────────────────
// Reservas
// ──────────────────────────────────────────────

void RelatorioReservasView(ListaReserva **lista);

// ──────────────────────────────────────────────
// Movimentacao de acomodacoes
// ──────────────────────────────────────────────

void RelatorioMovimentacaoView(ListaReserva    **listaReserva,
                                ListaAcomodacao **listaAcom,
                                ListaCategoria  **listaCat);

// ──────────────────────────────────────────────
// Produtos
// ──────────────────────────────────────────────

void RelatorioProdutosView(ListaProduto **lista);

void RelatorioProdutosEstoqueView(ListaProduto **lista);

// ──────────────────────────────────────────────
// Vendas
// ──────────────────────────────────────────────
void RelatorioVendasView(ListaVenda **lista);

// ──────────────────────────────────────────────
// Contas a Receber
// ──────────────────────────────────────────────
void RelatorioContasReceberView(ListaContaReceber **lista);

// ──────────────────────────────────────────────
// Contas a Pagar
// ──────────────────────────────────────────────
void RelatorioContasPagarView(ListaContaPagar **lista);

// ──────────────────────────────────────────────
// Movimentacao de Caixa
// ──────────────────────────────────────────────
void RelatorioMovimentacaoCaixaView(ListaCaixa **lista);

#endif // RELATORIO_VIEW_H