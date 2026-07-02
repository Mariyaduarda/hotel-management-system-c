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
        opcao = ler_int("");

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

    ler_string("Data (DD/MM/AAAA): ", venda.data, sizeof(venda.data));
    venda.idHospede =      ler_int("Hospede ID: ");
    numItens =             ler_int("Numero de itens: ");
    venda.formaPagamento = ler_int("Forma de pagamento (1=Avista / 2=Anotar): ");

    if (numItens > MAX_ITENS_VENDA) numItens = MAX_ITENS_VENDA;
    venda.numItens = 0;
    venda.total = 0.0f;
    venda.lancadaNoCaixa = 0;

    for (int i = 0; i < numItens; i++) {
        ItemVenda item = {0};
        printf("\nItem %d\n", i + 1);
        item.idProduto = ler_int("ID do produto: ");
        item.quantidade = ler_int("Quantidade: ");
        item.precoUnitario = ler_float("Preco unitario: ");
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
    id = ler_int("ID da venda: ");
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
