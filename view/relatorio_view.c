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

    printf(CIANO "\n  Saída: " RESET);
    printf("[1] Tela  [2] Arquivo CSV: ");
    int op;
    scanf("%d", &op);
    limparBuffer();

    if (op == 2) {
        cfg.destino = RELATORIO_ARQUIVO;
        printf("  Caminho (ex: relatorio.csv): ");
        lerString(cfg.caminho, sizeof(cfg.caminho));
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
    opcao("7", "Vendas");
    opcao("8", "Contas a receber");
    opcao("9", "Contas a pagar");
    opcao("10", "Movimentacao de caixa");
    separador();
    opcao("0", "Voltar");
    rodape();
}

// ──────────────────────────────────────────────
// Hospedes
// ──────────────────────────────────────────────

void RelatorioHospedesView(ListaHospede **lista) {
    printf("\n");
    cabecalho("RELATORIO DE HOSPEDES");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    int idMin = 0, idMax = 0;
    printf("Faixa de IDs (0 0 = todos): ");
    scanf("%d %d", &idMin, &idMax);
    limparBuffer();

    char sexo[10] = "";
    printf("Sexo (M/F ou vazio = todos): ");
    lerString(sexo, sizeof(sexo));

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
    printf("Faixa de IDs (0 0 = todos): ");
    scanf("%d %d", &idMin, &idMax);
    limparBuffer();

    int idCat = 0;
    printf("ID da categoria (0 = todas): ");
    scanf("%d", &idCat);
    limparBuffer();

    char dataDisp[11] = "";
    printf("Data disponivel DD/MM/AAAA (vazio = sem filtro): ");
    lerString(dataDisp, sizeof(dataDisp));

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
    printf("ID do hospede (0 = todos): ");
    scanf("%d", &idHosp);
    limparBuffer();

    printf("ID da acomodacao (0 = todas): ");
    scanf("%d", &idAcom);
    limparBuffer();

    char ini[11] = "", fim[11] = "";
    printf("Periodo inicio DD/MM/AAAA (vazio = sem filtro): ");
    lerString(ini, sizeof(ini));
    printf("Periodo fim    DD/MM/AAAA (vazio = sem filtro): ");
    lerString(fim, sizeof(fim));

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
    printf("ID da acomodacao (0 = todas): ");
    scanf("%d", &idAcom);
    limparBuffer();

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
    scanf("%d %d", &idMin, &idMax);
    limparBuffer();

    ConfigRelatorio cfg = pedirDestino();
    RelatorioProdutos(lista, &cfg, idMin, idMax);
}

void RelatorioProdutosEstoqueView(ListaProduto **lista) {
    printf("\n");
    cabecalho("PRODUTOS EM ESTOQUE MINIMO");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    int idMin = 0, idMax = 0;
    printf("Faixa de IDs (0 0 = todos): ");
    scanf("%d %d", &idMin, &idMax);
    limparBuffer();

    ConfigRelatorio cfg = pedirDestino();
    RelatorioProdutosEstoqueMinimo(lista, &cfg, idMin, idMax);
}

// ──────────────────────────────────────────────
// Vendas
// ──────────────────────────────────────────────

void RelatorioVendasView(ListaVenda **lista) {
    printf("\n");
    cabecalho("RELATORIO DE VENDAS");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    int formaPagamento = 0;
    printf("Forma de pagamento (0=todas, 1=A vista, 2=Para anotar): ");
    scanf("%d", &formaPagamento);
    limparBuffer();

    ConfigRelatorio cfg = pedirDestino();
    RelatorioVendas(lista, &cfg, formaPagamento);
}

// ──────────────────────────────────────────────
// Contas a Receber
// ──────────────────────────────────────────────

void RelatorioContasReceberView(ListaContaReceber **lista) {
    printf("\n");
    cabecalho("RELATORIO DE CONTAS A RECEBER");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    int idMin = 0, idMax = 0;
    printf("Faixa de codigo do hospede (0 0 = todos): ");
    scanf("%d %d", &idMin, &idMax);
    limparBuffer();

    char ini[11] = "", fim[11] = "";
    printf("Vencimento inicio DD/MM/AAAA (vazio = sem filtro): ");
    lerString(ini, sizeof(ini));
    printf("Vencimento fim    DD/MM/AAAA (vazio = sem filtro): ");
    lerString(fim, sizeof(fim));

    ConfigRelatorio cfg = pedirDestino();
    RelatorioContasReceber(lista, &cfg, idMin, idMax, ini, fim);
}

// ──────────────────────────────────────────────
// Contas a Pagar
// ──────────────────────────────────────────────

void RelatorioContasPagarView(ListaContaPagar **lista) {
    printf("\n");
    cabecalho("RELATORIO DE CONTAS A PAGAR");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    int idMin = 0, idMax = 0;
    printf("Faixa de codigo do fornecedor (0 0 = todos): ");
    scanf("%d %d", &idMin, &idMax);
    limparBuffer();

    char ini[11] = "", fim[11] = "";
    printf("Vencimento inicio DD/MM/AAAA (vazio = sem filtro): ");
    lerString(ini, sizeof(ini));
    printf("Vencimento fim    DD/MM/AAAA (vazio = sem filtro): ");
    lerString(fim, sizeof(fim));

    ConfigRelatorio cfg = pedirDestino();
    RelatorioContasPagar(lista, &cfg, idMin, idMax, ini, fim);
}

// ──────────────────────────────────────────────
// Movimentacao de Caixa
// ──────────────────────────────────────────────

void RelatorioMovimentacaoCaixaView(ListaCaixa **lista) {
    printf("\n");
    cabecalho("MOVIMENTACAO DE CAIXA");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    char ini[11] = "", fim[11] = "";
    printf("Periodo inicio DD/MM/AAAA (vazio = sem filtro): ");
    lerString(ini, sizeof(ini));
    printf("Periodo fim    DD/MM/AAAA (vazio = sem filtro): ");
    lerString(fim, sizeof(fim));

    ConfigRelatorio cfg = pedirDestino();
    RelatorioMovimentacaoCaixa(lista, &cfg, ini, fim);
}