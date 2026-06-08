#include "../common.h"
#include "venda_view.h"
#include "../controller/venda_controller.h"

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

void VendaMenuView(ListaVenda **lista) {
    int opcao;
    do {
        printf("\n");
        cabecalho("VENDAS");
        imprimirOpcao("1", "Cadastrar venda");
        imprimirOpcao("2", "Listar vendas");
        imprimirOpcao("3", "Buscar venda por ID");
        imprimirOpcao("4", "Salvar vendas");
        imprimirOpcao("5", "Carregar vendas");
        printf("%s\n", MEIO);
        imprimirOpcao("0", "Voltar");
        rodape();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: VendaCadastrarView(lista); break;
            case 2: VendaListarView(lista); break;
            case 3: VendaBuscarView(lista); break;
            case 4: VendaSalvarView(lista); break;
            case 5: VendaCarregarView(lista); break;
            case 0: break;
            default: printf(VERMELHO "  Opcao invalida.\n" RESET);
        }
    } while (opcao != 0);
}

void VendaCadastrarView(ListaVenda **lista) {
    TipoVenda venda;
    VendaInit(&venda);
    int numItens = 0;

    printf("\n");
    cabecalho("CADASTRAR VENDA");
    printf("%s\n", FUNDO);

    printf("Hospede ID: ");
    scanf("%d", &venda.idHospede);
    limparBuffer();
    printf("Data (DD/MM/AAAA): ");
    lerString(venda.data, sizeof(venda.data));
    printf("Forma de pagamento (1=Avista / 2=Anotar): ");
    scanf("%d", &venda.formaPagamento);
    limparBuffer();
    printf("Numero de itens: ");
    scanf("%d", &numItens);
    limparBuffer();

    if (numItens > MAX_ITENS_VENDA) numItens = MAX_ITENS_VENDA;
    venda.numItens = 0;
    venda.total = 0.0f;
    venda.lancadaNoCaixa = 0;

    for (int i = 0; i < numItens; i++) {
        ItemVenda item = {0};
        printf("\nItem %d\n", i + 1);
        printf("ID do produto: ");
        scanf("%d", &item.idProduto);
        limparBuffer();
        printf("Quantidade: ");
        scanf("%d", &item.quantidade);
        limparBuffer();
        printf("Preco unitario: ");
        scanf("%f", &item.precoUnitario);
        limparBuffer();
        item.subtotal = item.precoUnitario * item.quantidade;
        venda.total += item.subtotal;
        venda.itens[venda.numItens++] = item;
    }

    if (controllerVendaCadastrar(lista, venda))
        printf(VERDE "  Venda cadastrada com sucesso.\n" RESET);
    else
        printf(VERMELHO "  Erro ao cadastrar venda.\n" RESET);
}

void VendaListarView(ListaVenda **lista) {
    printf("\n");
    cabecalho("LISTAR VENDAS");
    controllerVendaListar(lista, 0);
}

void VendaBuscarView(ListaVenda **lista) {
    int id;
    printf("\n");
    cabecalho("BUSCAR VENDA");
    printf("ID da venda: ");
    scanf("%d", &id);
    limparBuffer();
    controllerVendaListar(lista, id);
}

void VendaSalvarView(ListaVenda **lista) {
    if (!controllerVendaSalvar(*lista))
        printf(VERMELHO "  Falha ao salvar vendas.\n" RESET);
    else
        printf(VERDE "  Vendas salvas com sucesso.\n" RESET);
}

void VendaCarregarView(ListaVenda **lista) {
    if (!controllerVendaCarregar(lista))
        printf(VERMELHO "  Falha ao carregar vendas.\n" RESET);
    else
        printf(VERDE "  Vendas carregadas com sucesso.\n" RESET);
}
