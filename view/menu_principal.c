#include "../common.h"
#include "menu_principal.h"
#include "hospede_view.h"

#include "../controller/acomodacao_controller.h"
#include "../controller/reserva_controller.h"
#include "../controller/relatorio_controller.h"
#include "../controller/produto_controller.h"
#include "../controller/hotel_controller.h"
#include "../controller/categoria_controller.h"
#include "../controller/nota_fiscal_controller.h"
#include "../controller/venda_controller.h"
#include "../controller/checkin_controller.h"
#include "../controller/contas_pagar_controller.h"
#include "../controller/contas_receber_controller.h"

#define LARGURA 56

/* ── Bordas ─────────────────────────────────────────────── */

static void linhaTopo(void) {
    printf("╔");
    for (int i = 0; i < LARGURA - 2; i++) printf("═");
    printf("╗\n");
}

static void linhaMeio(void) {
    printf("╠");
    for (int i = 0; i < LARGURA - 2; i++) printf("═");
    printf("╣\n");
}

static void linhaFundo(void) {
    printf("╚");
    for (int i = 0; i < LARGURA - 2; i++) printf("═");
    printf("╝\n");
}

/* ── Texto alinhado ─────────────────────────────────────── */

static void linhaTexto(const char *texto) {
    printf("║ %-*s ║\n", LARGURA - 4, texto);
}

static void linhaTitulo(const char *titulo) {
    int espaco   = LARGURA - 2;
    int tamanho  = (int)strlen(titulo);
    int esquerda = (espaco - tamanho) / 2;
    int direita  = espaco - tamanho - esquerda;

    printf("║");
    for (int i = 0; i < esquerda; i++) printf(" ");
    printf("%s", titulo);
    for (int i = 0; i < direita;  i++) printf(" ");
    printf("║\n");
}

static void opcao(const char *tecla, const char *desc) {
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "[%s] %s", tecla, desc);
    printf("║ %-*s ║\n", LARGURA - 4, buffer);
}

static void separadorMenuPrincipal(const char *label) {
    linhaMeio();
    linhaTexto(label);
}

/* ── Cabecalho / Rodape ─────────────────────────────────── */

static void cabecalho(const char *titulo) {
    limparTela();
    linhaTopo();
    linhaTitulo(titulo);
    linhaMeio();
}

static void rodape(void) {
    linhaFundo();
}

/* ───────────────────────────────────────────────────────── */
/* Submenu: Cadastros                                        */
/* ───────────────────────────────────────────────────────── */

static void menuCadastros(ListaHospede    **listaHospede,
                          ListaAcomodacao **listaAcomodacao,
                          ListaCategoria  **listaCategoria,
                          ListaProduto    **listaProduto,
                          Hotel           *hotel)
{
    int op;

    do {
        // mostra o menu
        cabecalho("CADASTROS");
        opcao("1", "Hospedes");
        opcao("2", "Acomodacoes");
        opcao("3", "Categorias");
        opcao("4", "Produtos");
        opcao("5", "Hotel");
        linhaMeio();
        opcao("0", "Voltar");
        rodape();

        op = ler_int_intervalo("\n =>", 0, 5);

        switch (op) {
        case 1: menuHospede(listaHospede);                              break;
        case 2: AcomodacaoControllerExecutar(listaAcomodacao,
                                               listaCategoria);           break;
        case 3: CategoriaControllerExecutar(listaCategoria);            break;
        case 4: ProdutoControllerExecutar(listaProduto);                break;
        case 5: HotelControllerExecutar(hotel);                         break;
        case 0: break;
        default:
            printf("\nOpcao invalida.\n");
            pausar();
        }

    } while (op != 0);
}

/* ───────────────────────────────────────────────────────── */
/* Submenu: Reservas                                         */
/* ───────────────────────────────────────────────────────── */

static void menuReservas(ListaReserva    **listaReserva,
                         ListaAcomodacao **listaAcomodacao,
                         ListaCategoria  **listaCategoria,
                         ListaHospede    **listaHospede)
{
    int op;

    do {
        cabecalho("RESERVAS");

        opcao("1", "Gerenciar reservas");

        linhaMeio();
        opcao("0", "Voltar");

        rodape();

        op = ler_int("\n =>");

        switch (op) {
        case 1:
            ReservaControllerExecutar(listaReserva,
                                      listaAcomodacao,
                                      listaCategoria,
                                      listaHospede);
            break;
        case 0: break;
        default:
            printf("\nOpcao invalida.\n");
            pausar();
        }

    } while (op != 0);
}

/* ───────────────────────────────────────────────────────── */
/* Submenu: Transacoes                                       */
/* ───────────────────────────────────────────────────────── */

static void menuTransacoes(ListaNotaFiscal **listaNotaFiscal,
                           ListaVenda      **listaVenda,
                           ListaCheckin    **listaCheckin,
                           ListaContaPagar **listaContaPagar,
                           ListaContaReceber **listaContaReceber)
{
    int op;

    do {
        cabecalho("TRANSACOES");

        opcao("1", "Nota fiscal");
        opcao("2", "Vendas");
        opcao("3", "Check-In");
        opcao("4", "Contas a pagar");
        opcao("5", "Contas a receber");

        linhaMeio();
        opcao("0", "Voltar");

        rodape();

        op = ler_int("\n =>");

        switch (op) {
        case 1: NotaFiscalControllerExecutar(listaNotaFiscal);          break;
        case 2: VendaControllerExecutar(listaVenda);                    break;
        case 3: CheckinControllerExecutar(listaCheckin);                break;
        case 4: ContaPagarControllerExecutar(listaContaPagar);          break;
        case 5: ContaReceberControllerExecutar(listaContaReceber);      break;
        case 0: break;
        default:
            printf("\nOpcao invalida.\n");
            pausar();
        }

    } while (op != 0);
}

/* ───────────────────────────────────────────────────────── */
/* Menu principal                                            */
/* ───────────────────────────────────────────────────────── */

void menuPrincipal(ListaHospede    **listaHospede,
                   ListaReserva    **listaReserva,
                   ListaAcomodacao **listaAcomodacao,
                   ListaCategoria  **listaCategoria,
                   ListaProduto    **listaProduto,
                   Hotel           *hotel,
                   ListaNotaFiscal **listaNotaFiscal,
                   ListaVenda      **listaVenda,
                   ListaCheckin    **listaCheckin,
                   ListaContaPagar **listaContaPagar,
                   ListaContaReceber **listaContaReceber)
{
    int op;

    do {
        cabecalho("HOTEL SISTEMA -- MENU PRINCIPAL");

        separadorMenuPrincipal("GESTAO");
        opcao("1", "Cadastros");
        opcao("2", "Reservas");

        separadorMenuPrincipal("OPERACOES");
        opcao("3", "Transacoes");
        opcao("4", "Relatorios");
        opcao("5", "Importar / Exportar");

        separadorMenuPrincipal("SISTEMA");
        opcao("0", "Sair");

        rodape();

        op = ler_int("\n =>");

        switch (op) {
        case 1:
            menuCadastros(listaHospede,
                          listaAcomodacao,
                          listaCategoria,
                          listaProduto,
                          hotel);
            break;
        case 2:
            menuReservas(listaReserva,
                         listaAcomodacao,
                         listaCategoria,
                         listaHospede);
            break;
        case 3:
            menuTransacoes(listaNotaFiscal,
                          listaVenda,
                          listaCheckin,
                          listaContaPagar,
                          listaContaReceber);
            break;
        case 4:
            RelatorioControllerExecutar(listaHospede,
                                        listaAcomodacao,
                                        listaCategoria,
                                        listaReserva,
                                        listaProduto);
            break;
        case 5:
            printf("\nImportacao/exportacao ainda nao.\n");
            pausar();
            break;
        case 0:
            break;
        default:
            printf("\nOpcao invalida.\n");
            pausar();
        }

    } while (op != 0);
}