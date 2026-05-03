// view/menu_principal.c
#include "../common.h"
#include "menu_principal.h"
#include "hospede_view.h"
// Descomente conforme for criando os outros menus:
// #include "reserva_view.h"
// #include "relatorio_view.h"

/* ── Cores ANSI ─────────────────────────────────────────── */
#define RESET    "\033[0m"
#define NEGRITO  "\033[1m"
#define CIANO    "\033[1;36m"
#define AMARELO  "\033[1;33m"
#define VERDE    "\033[1;32m"
#define VERMELHO "\033[1;31m"
#define CINZA    "\033[0;90m"
#define MAGENTA  "\033[1;35m"

/* ── Bordas UTF-8 ───────────────────────────────────────── */
#define TOPO  "╔══════════════════════════╗"
#define MEIO  "╠══════════════════════════╣"
#define FUNDO "╚══════════════════════════╝"
#define BORDA "║"

/* ── Utilitários internos ───────────────────────────────── */
static void limparTela(void)  { printf("\033[H\033[J"); }

static void pausar(void) {
    printf(CINZA "\n  Pressione Enter para continuar..." RESET);
    while (getchar() != '\n');
    getchar();
}

static void cabecalho(const char *titulo) {
    limparTela();
    printf(CIANO "%s\n" RESET, TOPO);
    printf(CIANO "%s" RESET "  " NEGRITO "%-26s" RESET CIANO "%s\n" RESET,
           BORDA, titulo, BORDA);
    printf(CIANO "%s\n" RESET, MEIO);
}

static void rodape(void) {
    printf(CIANO "%s\n" RESET, FUNDO);
    printf(CINZA "  Opção: " RESET);
}

static void opcao(const char *tecla, const char *desc, const char *cor) {
    printf(CIANO "%s" RESET "  %s[%s]" RESET " %-22s" CIANO "%s\n" RESET,
           BORDA, cor, tecla, desc, BORDA);
}

static void separador(const char *label) {
    printf(CIANO "%s\n" RESET, MEIO);
    printf(CIANO "%s" RESET "  " CINZA "%-26s" RESET CIANO "%s\n" RESET,
           BORDA, label, BORDA);
}

/* ── Submenu: Cadastros ─────────────────────────────────── */
static void menuCadastros(ListaHospede    **listaHospede,
                           ListaAcomodacao **listaAcomodacao,
                           ListaCategoria  **listaCategoria,
                           ListaProduto    **listaProduto,
                           Hotel           *hotel)
{
    char op;
    do {
        cabecalho("📋  CADASTROS");
        opcao("H", "Hóspedes",           VERDE);
        opcao("A", "Acomodações",        VERDE);
        opcao("C", "Categorias",         VERDE);
        opcao("P", "Produtos",           VERDE);
        opcao("T", "Hotel",              AMARELO);
        opcao("V", "Voltar",             CINZA);
        rodape();
        scanf(" %c", &op);
        op = toupper(op);

        switch (op) {
        case 'H':
            menuHospede(listaHospede);
            break;
        case 'A':
            // menuAcomodacao(listaAcomodacao, listaCategoria);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'C':
            // menuCategoria(listaCategoria);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'P':
            // menuProduto(listaProduto);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'T':
            // menuHotel(hotel);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'V': break;
        default:
            printf(VERMELHO "  ✘ Opção inválida.\n" RESET);
            pausar();
        }
    } while (op != 'V');
}

/* ── Submenu: Reservas ──────────────────────────────────── */
static void menuReservas(ListaReserva    **listaReserva,
                          ListaAcomodacao **listaAcomodacao,
                          ListaCategoria  **listaCategoria,
                          ListaHospede    **listaHospede)
{
    char op;
    do {
        cabecalho("📅  RESERVAS");
        opcao("N", "Nova reserva",       VERDE);
        opcao("C", "Cancelar reserva",   VERMELHO);
        opcao("B", "Buscar disponíveis", AMARELO);
        opcao("L", "Consultar por ID",   AMARELO);
        opcao("V", "Voltar",             CINZA);
        rodape();
        scanf(" %c", &op);
        op = toupper(op);

        switch (op) {
        case 'N':
            // ReservaCadastrarView(listaReserva, listaAcomodacao, listaCategoria, listaHospede);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'C':
            // ReservaCancelarView(listaReserva);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'B':
            // ReservaBuscarDisponiveisView(listaReserva, listaAcomodacao, listaCategoria);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'L':
            // ReservaConsultarView(listaReserva);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'V': break;
        default:
            printf(VERMELHO "  ✘ Opção inválida.\n" RESET);
            pausar();
        }
    } while (op != 'V');
}

/* ── Submenu: Relatórios ────────────────────────────────── */
static void menuRelatorios(ListaHospede    **listaHospede,
                            ListaAcomodacao **listaAcomodacao,
                            ListaCategoria  **listaCategoria,
                            ListaReserva    **listaReserva,
                            ListaProduto    **listaProduto)
{
    char op;
    do {
        cabecalho("📊  RELATÓRIOS");
        opcao("H", "Hóspedes",             AMARELO);
        opcao("A", "Acomodações",          AMARELO);
        opcao("R", "Reservas",             AMARELO);
        opcao("M", "Movim. acomodações",   AMARELO);
        opcao("P", "Produtos",             AMARELO);
        opcao("E", "Estoque mínimo",       VERMELHO);
        opcao("V", "Voltar",               CINZA);
        rodape();
        scanf(" %c", &op);
        op = toupper(op);

        switch (op) {
        case 'H':
            // RelatorioHospedesView(listaHospede);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'A':
            // RelatorioAcomodacoesView(listaAcomodacao, listaCategoria);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'R':
            // RelatorioReservasView(listaReserva);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'M':
            // RelatorioMovimentacaoView(listaReserva, listaAcomodacao, listaCategoria);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'P':
            // RelatorioProdutosView(listaProduto);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'E':
            // RelatorioProdutosEstoqueView(listaProduto);
            printf(AMARELO "\n  [Em construção]\n" RESET);
            pausar();
            break;
        case 'V': break;
        default:
            printf(VERMELHO "  ✘ Opção inválida.\n" RESET);
            pausar();
        }
    } while (op != 'V');
}

/* ── Menu principal (entry point público) ───────────────── */
void menuPrincipal(ListaHospede    **listaHospede,
                   ListaReserva    **listaReserva,
                   ListaAcomodacao **listaAcomodacao,
                   ListaCategoria  **listaCategoria,
                   ListaProduto    **listaProduto,
                   Hotel           *hotel)
{
    char op;
    do {
        cabecalho("🏨  HOTEL SYSTEM");
        separador("  GESTÃO");
        opcao("C", "Cadastros",          VERDE);
        opcao("R", "Reservas",           CIANO);
        separador("  OPERAÇÕES");
        opcao("T", "Transações",         AMARELO);
        opcao("F", "Relatórios",         MAGENTA);
        opcao("I", "Importar / Exportar",CINZA);
        separador("  SISTEMA");
        opcao("S", "Sair",               VERMELHO);
        rodape();
        scanf(" %c", &op);
        op = toupper(op);

        switch (op) {
        case 'C':
            menuCadastros(listaHospede, listaAcomodacao,
                          listaCategoria, listaProduto, hotel);
            break;
        case 'R':
            menuReservas(listaReserva, listaAcomodacao,
                         listaCategoria, listaHospede);
            break;
        case 'T':
            printf(AMARELO "\n  [Módulo de Transações em construção]\n" RESET);
            pausar();
            break;
        case 'F':
            menuRelatorios(listaHospede, listaAcomodacao,
                           listaCategoria, listaReserva, listaProduto);
            break;
        case 'I':
            printf(AMARELO "\n  [Módulo de Importação/Exportação em construção]\n" RESET);
            pausar();
            break;
        case 'S': break;
        default:
            printf(VERMELHO "  ✘ Opção inválida.\n" RESET);
            pausar();
        }
    } while (op != 'S');
}