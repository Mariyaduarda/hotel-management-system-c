#include "../common.h"
#include "../view/relatorio_view.h"
#include "../utils/relatorio.h"
#include <string.h>
#include <stdio.h>

#define TOPO  "╔══════════════════════════════════╗"
#define MEIO  "╠══════════════════════════════════╣"
#define FUNDO "╚══════════════════════════════════╝"
#define BORDA "║"

static void cabecalho(const char *titulo) {
    printf(CIANO "%s\n" RESET, TOPO);
    printf(CIANO "%s" RESET "  " NEGRITO "%-32s" RESET CIANO "%s\n" RESET,
           BORDA, titulo, BORDA);
    printf(CIANO "%s\n" RESET, MEIO);
}

static void opcao(const char *num, const char *desc) {
    printf(CIANO "%s" RESET "  " VERDE "[%s]" RESET " %-28s" CIANO "%s\n" RESET,
           BORDA, num, desc, BORDA);
}

static void rodape(void) {
    printf(CIANO "%s\n" RESET, FUNDO);
    printf(CINZA "  Opcao: " RESET);
}

static void separador(void) {
    printf(CIANO "%s\n" RESET, MEIO);
}

// ──────────────────────────────────────────────
// Helper: destino do relatorio
// ──────────────────────────────────────────────

static ConfigRelatorio pedirDestino(void) {
    ConfigRelatorio cfg;
    cfg.destino = RELATORIO_TELA;
    strcpy(cfg.caminho, "");

    int op;
    printf(CIANO "\n  Saida: " RESET);
    op = ler_int("[1] Tela  [2] Arquivo CSV: ");
    if (op == 2) {
        cfg.destino = RELATORIO_ARQUIVO;
        ler_string("  Caminho (ex: relatorio.csv): ", cfg.caminho, sizeof(cfg.caminho));
    }
    return cfg;
}

// ──────────────────────────────────────────────
// Menu
// ──────────────────────────────────────────────

void RelatorioMenuExibir(void) {
    printf("\n");
    cabecalho("RELATORIOS");
    opcao("1", "Hospedes");
    opcao("2", "Acomodacoes");
    opcao("3", "Reservas");
    opcao("4", "Movimentacao de acomodacoes");
    opcao("5", "Produtos de consumo");
    opcao("6", "Produtos em estoque minimo");
    separador();
    opcao("0", "Voltar");
    rodape();
}

void RelatorioMenuExecutar(ListaHospede    **listaHospede,
                           ListaAcomodacao **listaAcom,
                           ListaCategoria  **listaCat,
                           ListaReserva    **listaReserva,
                           ListaProduto    **listaProduto)
{
    int opcao;
    do {
        RelatorioMenuExibir();
        opcao = ler_int("");

        switch (opcao) {
            case 1: RelatorioHospedesView(listaHospede);                              break;
            case 2: RelatorioAcomodacoesView(listaAcom, listaCat);                    break;
            case 3: RelatorioReservasView(listaReserva);                              break;
            case 4: RelatorioMovimentacaoView(listaReserva, listaAcom, listaCat);     break;
            case 5: RelatorioProdutosView(listaProduto);                              break;
            case 6: RelatorioProdutosEstoqueView(listaProduto);                       break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

// ──────────────────────────────────────────────
// Hospedes
// ──────────────────────────────────────────────

void RelatorioHospedesView(ListaHospede **lista) {
    printf("\n");
    cabecalho("RELATORIO DE HOSPEDES");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    int idMin = 0, idMax = 0;
    idMin = ler_int("ID minimo (0 = todos): ");
    idMax = ler_int("ID maximo (0 = todos): ");

    char sexo[10] = "";
    ler_string("Sexo (M/F ou vazio = todos): ", sexo, sizeof(sexo));

    ConfigRelatorio cfg = pedirDestino();
    RelatorioHospedes(lista, &cfg, idMin, idMax, sexo);
}

// ──────────────────────────────────────────────
// Acomodacoes
// ──────────────────────────────────────────────

void RelatorioAcomodacoesView(ListaAcomodacao **listaAcom,
                               ListaCategoria  **listaCat)
{
    printf("\n");
    cabecalho("RELATORIO DE ACOMODACOES");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    int idMin = 0, idMax = 0;
    idMin = ler_int("Faixa de IDs (0 0 = todos): ");
    idMax = ler_int("Faixa de IDs (0 0 = todos): ");

    int idCat = 0;
    idCat = ler_int("ID da categoria (0 = todas): ");

    char dataDisp[11] = "";
    ler_string("Data disponivel DD/MM/AAAA (vazio = sem filtro): ", dataDisp, sizeof(dataDisp));

    ConfigRelatorio cfg = pedirDestino();
    RelatorioAcomodacoes(listaAcom, listaCat, &cfg, idMin, idMax, idCat, dataDisp);
}

// ──────────────────────────────────────────────
// Reservas
// ──────────────────────────────────────────────

void RelatorioReservasView(ListaReserva **lista) {
    printf("\n");
    cabecalho("RELATORIO DE RESERVAS");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    int idHosp = 0, idAcom = 0;
    idHosp = ler_int("ID do hospede (0 = todos): ");
    idAcom = ler_int("ID da acomodacao (0 = todas): ");
    limparBuffer();

    char ini[11] = "", fim[11] = "";
    ler_string("Periodo inicio DD/MM/AAAA (vazio = sem filtro): ", ini, sizeof(ini));
    ler_string("Periodo fim    DD/MM/AAAA (vazio = sem filtro): ", fim, sizeof(fim));

    ConfigRelatorio cfg = pedirDestino();
    RelatorioReservas(lista, &cfg, idHosp, idAcom, ini, fim);
}

// ──────────────────────────────────────────────
// Movimentacao de acomodacoes
// ──────────────────────────────────────────────

void RelatorioMovimentacaoView(ListaReserva    **listaReserva,
                                ListaAcomodacao **listaAcom,
                                ListaCategoria  **listaCat)
{
    printf("\n");
    cabecalho("MOVIMENTACAO DE ACOMODACOES");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    int idAcom = 0;
    idAcom = ler_int("ID da acomodacao (0 = todas): ");

    ConfigRelatorio cfg = pedirDestino();
    RelatorioMovimentacaoAcomodacoes(listaReserva, listaAcom, listaCat, &cfg, idAcom);
}

// ──────────────────────────────────────────────
// Produtos
// ──────────────────────────────────────────────

void RelatorioProdutosView(ListaProduto **lista) {
    printf("\n");
    cabecalho("RELATORIO DE PRODUTOS");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    int idMin = 0, idMax = 0;
    printf("Faixa de IDs (0 0 = todos): ");
    idMin = ler_int("");
    idMax = ler_int("");

    ConfigRelatorio cfg = pedirDestino();
    RelatorioProdutos(lista, &cfg, idMin, idMax);
}

void RelatorioProdutosEstoqueView(ListaProduto **lista) {
    printf("\n");
    cabecalho("PRODUTOS EM ESTOQUE MINIMO");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    int idMin = 0, idMax = 0;
    printf("Faixa de IDs (0 0 = todos): ");
    idMin = ler_int("");
    idMax = ler_int("");

    ConfigRelatorio cfg = pedirDestino();
    RelatorioProdutosEstoqueMinimo(lista, &cfg, idMin, idMax);
}