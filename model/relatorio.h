#ifndef RELATORIO_H
#define RELATORIO_H

#include "../model/hospede.h"
#include "../model/acomodacao.h"
#include "../model/categoria_acomodacao.h"
#include "../model/reserva.h"
#include "../model/produto.h"

// Destino do relatorio
#define RELATORIO_TELA    0
#define RELATORIO_ARQUIVO 1

typedef struct {
    int destino;        // RELATORIO_TELA ou RELATORIO_ARQUIVO
    char caminho[200];  // caminho do arquivo CSV, se destino == RELATORIO_ARQUIVO
} ConfigRelatorio;

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