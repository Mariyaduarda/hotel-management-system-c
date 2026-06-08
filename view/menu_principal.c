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

/* ── Utilitários internos ───────────────────────────────── */

static void limparTela(void) {
    printf("\033[H\033[J");
}

static void pausar(void) {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');
}

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

static void separador(const char *label) {
    linhaMeio();
    linhaTexto(label);
}

/* ── Cabeçalho / Rodapé ─────────────────────────────────── */

static void cabecalho(const char *titulo) {
    limparTela();
    linhaTopo();
    linhaTitulo(titulo);
    linhaMeio();
}

static void rodape(void) {
    linhaFundo();
    printf("\nOpcao: ");
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
    char op;

    do {
        cabecalho("CADASTROS");

        opcao("H", "Hospedes");
        opcao("A", "Acomodacoes");
        opcao("C", "Categorias");
        opcao("P", "Produtos");
        opcao("T", "Hotel");

        linhaMeio();
        opcao("V", "Voltar");

        rodape();

        scanf(" %c", &op);
        op = toupper(op);

        switch (op) {
        case 'H': menuHospede(listaHospede);                              break;
        case 'A': AcomodacaoControllerExecutar(listaAcomodacao,
                                               listaCategoria);           break;
        case 'C': CategoriaControllerExecutar(listaCategoria);            break;
        case 'P': ProdutoControllerExecutar(listaProduto);                break;
        case 'T': HotelControllerExecutar(hotel);                         break;
        case 'V': break;
        default:
            printf("\nOpcao invalida.\n");
            pausar();
        }

    } while (op != 'V');
}

/* ───────────────────────────────────────────────────────── */
/* Submenu: Reservas                                         */
/* ───────────────────────────────────────────────────────── */

static void menuReservas(ListaReserva    **listaReserva,
                         ListaAcomodacao **listaAcomodacao,
                         ListaCategoria  **listaCategoria,
                         ListaHospede    **listaHospede)
{
    char op;

    do {
        cabecalho("RESERVAS");

        opcao("R", "Gerenciar reservas");

        linhaMeio();
        opcao("V", "Voltar");

        rodape();

        scanf(" %c", &op);
        op = toupper(op);

        switch (op) {
        case 'R':
            ReservaControllerExecutar(listaReserva,
                                      listaAcomodacao,
                                      listaCategoria,
                                      listaHospede);
            break;
        case 'V': break;
        default:
            printf("\nOpcao invalida.\n");
            pausar();
        }

    } while (op != 'V');
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
    char op;

    do {
        cabecalho("TRANSACOES");

        opcao("N", "Nota fiscal");
        opcao("V", "Vendas");
        opcao("K", "Check-In");
        opcao("P", "Contas a pagar");
        opcao("R", "Contas a receber");

        linhaMeio();
        opcao("X", "Voltar");

        rodape();

        scanf(" %c", &op);
        op = toupper(op);

        switch (op) {
        case 'N': NotaFiscalControllerExecutar(listaNotaFiscal);          break;
        case 'V': VendaControllerExecutar(listaVenda);                    break;
        case 'K': CheckinControllerExecutar(listaCheckin);                break;
        case 'P': ContaPagarControllerExecutar(listaContaPagar);          break;
        case 'R': ContaReceberControllerExecutar(listaContaReceber);      break;
        case 'X': break;
        default:
            printf("\nOpcao invalida.\n");
            pausar();
        }

    } while (op != 'X');
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
    char op;

    do {
        cabecalho("HOTEL SISTEMA -- MENU PRINCIPAL");

        separador("GESTAO");
        opcao("C", "Cadastros");
        opcao("R", "Reservas");

        separador("OPERACOES");
        opcao("T", "Transacoes");
        opcao("F", "Relatorios");
        opcao("I", "Importar / Exportar");

        separador("SISTEMA");
        opcao("S", "Sair");

        rodape();

        scanf(" %c", &op);
        op = toupper(op);

        switch (op) {
        case 'C':
            menuCadastros(listaHospede,
                          listaAcomodacao,
                          listaCategoria,
                          listaProduto,
                          hotel);
            break;
        case 'R':
            menuReservas(listaReserva,
                         listaAcomodacao,
                         listaCategoria,
                         listaHospede);
            break;
        case 'T':
            menuTransacoes(listaNotaFiscal,
                          listaVenda,
                          listaCheckin,
                          listaContaPagar,
                          listaContaReceber);
            break;
        case 'F':
            RelatorioControllerExecutar(listaHospede,
                                        listaAcomodacao,
                                        listaCategoria,
                                        listaReserva,
                                        listaProduto);
            break;
        case 'I':
            printf("\nImportacao/exportacao ainda nao.\n");
            pausar();
            break;
        case 'S':
            break;
        default:
            printf("\nOpcao invalida.\n");
            pausar();
        }

    } while (op != 'S');
}