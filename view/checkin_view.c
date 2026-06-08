#include "../common.h"
#include "checkin_view.h"
#include "../controller/checkin_controller.h"

#define TOPO  "╔════════════════════════════════╗"
#define MEIO  "╠════════════════════════════════╣"
#define FUNDO "╚════════════════════════════════╝"
#define BORDA "║"

static void cabecalho(const char *titulo) {
    printf(CIANO "%s\n" RESET, TOPO);
    printf(CIANO "%s" RESET "  " NEGRITO "%-28s" RESET CIANO "%s\n" RESET,
           BORDA, titulo, BORDA);
    printf(CIANO "%s\n" RESET, MEIO);
}

static void imprimirOpcao(const char *num, const char *desc) {
    printf(CIANO "%s" RESET "  " VERDE "[%s]" RESET " %-28s" CIANO "%s\n" RESET,
           BORDA, num, desc, BORDA);
}

static void rodape(void) {
    printf(CIANO "%s\n" RESET, FUNDO);
    printf(CINZA "  Opcao: " RESET);
}

void CheckinMenuView(ListaCheckin **lista) {
    int opcao;
    do {
        printf("\n");
        cabecalho("CHECK-IN");
        imprimirOpcao("1", "Registrar check-in");
        imprimirOpcao("2", "Listar check-ins");
        imprimirOpcao("3", "Buscar check-in por ID");
        imprimirOpcao("4", "Buscar check-in por reserva");
        imprimirOpcao("5", "Encerrar check-in");
        imprimirOpcao("6", "Salvar check-ins");
        imprimirOpcao("7", "Carregar check-ins");
        printf("%s\n", MEIO);
        imprimirOpcao("0", "Voltar");
        rodape();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: CheckinCadastrarView(lista); break;
            case 2: CheckinListarView(lista); break;
            case 3: CheckinBuscarView(lista); break;
            case 4: CheckinBuscarPorReservaView(lista); break;
            case 5: CheckinEncerrarView(lista); break;
            case 6: CheckinSalvarView(lista); break;
            case 7: CheckinCarregarView(lista); break;
            case 0: break;
            default: printf(VERMELHO "  Opcao invalida.\n" RESET);
        }
    } while (opcao != 0);
}

void CheckinCadastrarView(ListaCheckin **lista) {
    TipoCheckin checkin;
    CheckinInit(&checkin);

    printf("\n");
    cabecalho("REGISTRAR CHECK-IN");
    printf("%s\n", FUNDO);

    printf("Reserva ID: ");
    scanf("%d", &checkin.idReserva);
    limparBuffer();
    printf("Hospede ID: ");
    scanf("%d", &checkin.idHospede);
    limparBuffer();
    printf("Acomodacao ID: ");
    scanf("%d", &checkin.idAcomodacao);
    limparBuffer();
    printf("Data de check-in (DD/MM/AAAA): ");
    lerString(checkin.dataCheckin, sizeof(checkin.dataCheckin));
    printf("Diarias pagas no check-in? (1=Sim / 0=Nao): ");
    scanf("%d", &checkin.diariasParas);
    limparBuffer();
    printf("Valor total das diarias: ");
    scanf("%f", &checkin.totalDiarias);
    limparBuffer();
    printf("Valor total de produtos: ");
    scanf("%f", &checkin.totalProdutos);
    limparBuffer();
    checkin.totalGeral = checkin.totalDiarias + checkin.totalProdutos;

    if (controllerCheckinCadastrar(lista, checkin))
        printf(VERDE "  Check-in registrado com sucesso.\n" RESET);
    else
        printf(VERMELHO "  Erro ao registrar check-in.\n" RESET);
}

void CheckinListarView(ListaCheckin **lista) {
    printf("\n");
    cabecalho("LISTAR CHECK-INS");
    controllerCheckinListar(lista, 0);
}

void CheckinBuscarView(ListaCheckin **lista) {
    int id;
    printf("\n");
    cabecalho("BUSCAR CHECK-IN");
    printf("ID do check-in: ");
    scanf("%d", &id);
    limparBuffer();
    controllerCheckinListar(lista, id);
}

void CheckinBuscarPorReservaView(ListaCheckin **lista) {
    int idReserva;
    printf("\n");
    cabecalho("BUSCAR CHECK-IN POR RESERVA");
    printf("ID da reserva: ");
    scanf("%d", &idReserva);
    limparBuffer();
    TipoCheckin *c = controllerCheckinBuscarPorReserva(lista, idReserva);
    if (c) {
        printf("ID: %d\n", c->id);
        printf("Reserva ID: %d\n", c->idReserva);
        printf("Hospede ID: %d\n", c->idHospede);
        printf("Acomodacao ID: %d\n", c->idAcomodacao);
        printf("Data de check-in: %s\n", c->dataCheckin);
        printf("Data de check-out: %s\n", strlen(c->dataCheckout) ? c->dataCheckout : "Em aberto");
        printf("Diarias: R$ %.2f\n", c->totalDiarias);
        printf("Produtos: R$ %.2f\n", c->totalProdutos);
        printf("Total geral: R$ %.2f\n", c->totalGeral);
        printf("Status: %s\n", c->encerrado ? "Check-out realizado" : "Hospedado");
    } else {
        printf(VERMELHO "  Check-in nao encontrado.\n" RESET);
    }
}

void CheckinEncerrarView(ListaCheckin **lista) {
    int id;
    char dataCheckout[12];
    printf("\n");
    cabecalho("ENCERRAR CHECK-IN");
    printf("ID do check-in: ");
    scanf("%d", &id);
    limparBuffer();
    printf("Data de checkout (DD/MM/AAAA): ");
    lerString(dataCheckout, sizeof(dataCheckout));
    if (!controllerCheckinEncerrar(lista, id, dataCheckout))
        printf(VERMELHO "  Falha ao encerrar check-in.\n" RESET);
    else
        printf(VERDE "  Check-in encerrado com sucesso.\n" RESET);
}

void CheckinSalvarView(ListaCheckin **lista) {
    if (!controllerCheckinSalvar(*lista))
        printf(VERMELHO "  Falha ao salvar check-ins.\n" RESET);
    else
        printf(VERDE "  Check-ins salvos com sucesso.\n" RESET);
}

void CheckinCarregarView(ListaCheckin **lista) {
    if (!controllerCheckinCarregar(lista))
        printf(VERMELHO "  Falha ao carregar check-ins.\n" RESET);
    else
        printf(VERDE "  Check-ins carregados com sucesso.\n" RESET);
}
