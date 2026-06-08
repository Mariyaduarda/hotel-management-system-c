#include "../common.h"
#include "contas_receber_view.h"
#include "../controller/contas_receber_controller.h"

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

void ContaReceberMenuView(ListaContaReceber **lista) {
    int opcao;
    do {
        printf("\n");
        cabecalho("CONTAS A RECEBER");
        imprimirOpcao("1", "Cadastrar conta a receber");
        imprimirOpcao("2", "Listar contas a receber");
        imprimirOpcao("3", "Buscar conta por ID");
        imprimirOpcao("4", "Dar baixa na conta");
        imprimirOpcao("5", "Salvar contas a receber");
        imprimirOpcao("6", "Carregar contas a receber");
        printf("%s\n", MEIO);
        imprimirOpcao("0", "Voltar");
        rodape();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: ContaReceberCadastrarView(lista); break;
            case 2: ContaReceberListarView(lista); break;
            case 3: ContaReceberBuscarView(lista); break;
            case 4: ContaReceberBaixarView(lista); break;
            case 5: ContaReceberSalvarView(lista); break;
            case 6: ContaReceberCarregarView(lista); break;
            case 0: break;
            default: printf(VERMELHO "  Opcao invalida.\n" RESET);
        }
    } while (opcao != 0);
}

void ContaReceberCadastrarView(ListaContaReceber **lista) {
    TipoContaReceber conta;
    ContaReceberInit(&conta);

    printf("\n");
    cabecalho("CADASTRAR CONTA A RECEBER");
    printf("%s\n", FUNDO);

    printf("Hospede ID: ");
    scanf("%d", &conta.idHospede);
    limparBuffer();
    printf("Descricao: ");
    lerString(conta.descricao, sizeof(conta.descricao));
    printf("Valor: ");
    scanf("%f", &conta.valor);
    limparBuffer();
    printf("Data de vencimento (DD/MM/AAAA): ");
    lerString(conta.dataVencimento, sizeof(conta.dataVencimento));

    if (controllerContaReceberCadastrar(lista, conta))
        printf(VERDE "  Conta a receber cadastrada com sucesso.\n" RESET);
    else
        printf(VERMELHO "  Erro ao cadastrar conta a receber.\n" RESET);
}

void ContaReceberListarView(ListaContaReceber **lista) {
    int filtrar;
    int idHospede = 0;
    char dataInicio[12] = "";
    char dataFim[12] = "";

    printf("\n");
    cabecalho("LISTAR CONTAS A RECEBER");
    printf("%s\n", FUNDO);
    printf("Filtrar por hospede? (1=Sim / 0=Nao): ");
    scanf("%d", &filtrar);
    limparBuffer();
    if (filtrar) {
        printf("Hospede ID: ");
        scanf("%d", &idHospede);
        limparBuffer();
    }
    printf("Filtrar por periodo? (1=Sim / 0=Nao): ");
    scanf("%d", &filtrar);
    limparBuffer();
    if (filtrar) {
        printf("Data inicio (DD/MM/AAAA): ");
        lerString(dataInicio, sizeof(dataInicio));
        printf("Data fim (DD/MM/AAAA): ");
        lerString(dataFim, sizeof(dataFim));
    }
    controllerContaReceberListar(lista, idHospede, dataInicio, dataFim);
}

void ContaReceberBuscarView(ListaContaReceber **lista) {
    int id;
    printf("\n");
    cabecalho("BUSCAR CONTA A RECEBER");
    printf("ID da conta: ");
    scanf("%d", &id);
    limparBuffer();
    TipoContaReceber *c = controllerContaReceberBuscar(lista, id);
    if (c) {
        printf("ID: %d\n", c->id);
        printf("Hospede ID: %d\n", c->idHospede);
        printf("Descricao: %s\n", c->descricao);
        printf("Valor: R$ %.2f\n", c->valor);
        printf("Vencimento: %s\n", c->dataVencimento);
        printf("Status: %s\n", c->status == CR_PENDENTE ? "Pendente" : "Recebido");
        printf("Data de recebimento: %s\n", strlen(c->dataRecebimento) ? c->dataRecebimento : "-");
    } else {
        printf(VERMELHO "  Conta a receber nao encontrada.\n" RESET);
    }
}

void ContaReceberBaixarView(ListaContaReceber **lista) {
    int id;
    char dataRecebimento[12];
    printf("\n");
    cabecalho("DAR BAIXA EM CONTA");
    printf("ID da conta: ");
    scanf("%d", &id);
    limparBuffer();
    printf("Data de recebimento (DD/MM/AAAA): ");
    lerString(dataRecebimento, sizeof(dataRecebimento));
    if (!controllerContaReceberBaixar(lista, id, dataRecebimento))
        printf(VERMELHO "  Falha ao dar baixa na conta.\n" RESET);
    else
        printf(VERDE "  Conta baixada com sucesso.\n" RESET);
}

void ContaReceberSalvarView(ListaContaReceber **lista) {
    if (!controllerContaReceberSalvar(*lista))
        printf(VERMELHO "  Falha ao salvar contas a receber.\n" RESET);
    else
        printf(VERDE "  Contas a receber salvas com sucesso.\n" RESET);
}

void ContaReceberCarregarView(ListaContaReceber **lista) {
    if (!controllerContaReceberCarregar(lista))
        printf(VERMELHO "  Falha ao carregar contas a receber.\n" RESET);
    else
        printf(VERDE "  Contas a receber carregadas com sucesso.\n" RESET);
}
