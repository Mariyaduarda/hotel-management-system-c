#include "../common.h"
#include "contas_pagar_view.h"
#include "../controller/contas_pagar_controller.h"

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

void ContaPagarMenuView(ListaContaPagar **lista) {
    int opcao;
    do {
        printf("\n");
        cabecalho("CONTAS A PAGAR");
        imprimirOpcao("1", "Cadastrar conta a pagar");
        imprimirOpcao("2", "Listar contas a pagar");
        imprimirOpcao("3", "Buscar conta por ID");
        imprimirOpcao("4", "Dar baixa na conta");
        imprimirOpcao("5", "Salvar contas a pagar");
        imprimirOpcao("6", "Carregar contas a pagar");
        printf("%s\n", MEIO);
        imprimirOpcao("0", "Voltar");
        rodape();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: ContaPagarCadastrarView(lista); break;
            case 2: ContaPagarListarView(lista); break;
            case 3: ContaPagarBuscarView(lista); break;
            case 4: ContaPagarBaixarView(lista); break;
            case 5: ContaPagarSalvarView(lista); break;
            case 6: ContaPagarCarregarView(lista); break;
            case 0: break;
            default: printf(VERMELHO "  Opcao invalida.\n" RESET);
        }
    } while (opcao != 0);
}

void ContaPagarCadastrarView(ListaContaPagar **lista) {
    TipoContaPagar conta;
    ContaPagarInit(&conta);

    printf("\n");
    cabecalho("CADASTRAR CONTA A PAGAR");
    printf("%s\n", FUNDO);

    printf("Fornecedor ID: ");
    scanf("%d", &conta.idFornecedor);
    limparBuffer();
    printf("Nota fiscal ID: ");
    scanf("%d", &conta.idNotaFiscal);
    limparBuffer();
    printf("Descricao: ");
    lerString(conta.descricao, sizeof(conta.descricao));
    printf("Valor: ");
    scanf("%f", &conta.valor);
    limparBuffer();
    printf("Data de vencimento (DD/MM/AAAA): ");
    lerString(conta.dataVencimento, sizeof(conta.dataVencimento));
    printf("Numero da parcela: ");
    scanf("%d", &conta.numeroParcela);
    limparBuffer();
    printf("Total de parcelas: ");
    scanf("%d", &conta.totalParcelas);
    limparBuffer();

    if (controllerContaPagarCadastrar(lista, conta))
        printf(VERDE "  Conta a pagar cadastrada com sucesso.\n" RESET);
    else
        printf(VERMELHO "  Erro ao cadastrar conta a pagar.\n" RESET);
}

void ContaPagarListarView(ListaContaPagar **lista) {
    int filtrar;
    int idFornecedor = 0;
    char dataInicio[12] = "";
    char dataFim[12] = "";

    printf("\n");
    cabecalho("LISTAR CONTAS A PAGAR");
    printf("%s\n", FUNDO);
    printf("Filtrar por fornecedor? (1=Sim / 0=Nao): ");
    scanf("%d", &filtrar);
    limparBuffer();
    if (filtrar) {
        printf("Fornecedor ID: ");
        scanf("%d", &idFornecedor);
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
    controllerContaPagarListar(lista, idFornecedor, dataInicio, dataFim);
}

void ContaPagarBuscarView(ListaContaPagar **lista) {
    int id;
    printf("\n");
    cabecalho("BUSCAR CONTA A PAGAR");
    printf("ID da conta: ");
    scanf("%d", &id);
    limparBuffer();
    TipoContaPagar *c = controllerContaPagarBuscar(lista, id);
    if (c) {
        printf("ID: %d\n", c->id);
        printf("Fornecedor ID: %d\n", c->idFornecedor);
        printf("Nota fiscal ID: %d\n", c->idNotaFiscal);
        printf("Descricao: %s\n", c->descricao);
        printf("Valor: R$ %.2f\n", c->valor);
        printf("Vencimento: %s\n", c->dataVencimento);
        printf("Status: %s\n", c->status == CP_PENDENTE ? "Pendente" : "Pago");
        printf("Parcela: %d/%d\n", c->numeroParcela, c->totalParcelas);
        printf("Data de pagamento: %s\n", strlen(c->dataPagamento) ? c->dataPagamento : "-");
    } else {
        printf(VERMELHO "  Conta a pagar nao encontrada.\n" RESET);
    }
}

void ContaPagarBaixarView(ListaContaPagar **lista) {
    int id;
    char dataPagamento[12];
    printf("\n");
    cabecalho("DAR BAIXA EM CONTA");
    printf("ID da conta: ");
    scanf("%d", &id);
    limparBuffer();
    printf("Data de pagamento (DD/MM/AAAA): ");
    lerString(dataPagamento, sizeof(dataPagamento));
    if (!controllerContaPagarBaixar(lista, id, dataPagamento))
        printf(VERMELHO "  Falha ao dar baixa na conta.\n" RESET);
    else
        printf(VERDE "  Conta baixada com sucesso.\n" RESET);
}

void ContaPagarSalvarView(ListaContaPagar **lista) {
    if (!controllerContaPagarSalvar(*lista))
        printf(VERMELHO "  Falha ao salvar contas a pagar.\n" RESET);
    else
        printf(VERDE "  Contas a pagar salvas com sucesso.\n" RESET);
}

void ContaPagarCarregarView(ListaContaPagar **lista) {
    if (!controllerContaPagarCarregar(lista))
        printf(VERMELHO "  Falha ao carregar contas a pagar.\n" RESET);
    else
        printf(VERDE "  Contas a pagar carregadas com sucesso.\n" RESET);
}
