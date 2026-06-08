#include "../common.h"
#include "nota_fiscal_view.h"
#include "../controller/nota_fiscal_controller.h"

#define TOPO  "╔════════════════════════════════════╗"
#define MEIO  "╠════════════════════════════════════╣"
#define FUNDO "╚════════════════════════════════════╝"
#define BORDA "║"

static void cabecalho(const char *titulo) {
    printf(CIANO "%s\n" RESET, TOPO);
    printf(CIANO "%s" RESET "  " NEGRITO "%-32s" RESET CIANO "%s\n" RESET,
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

void NotaFiscalMenuView(ListaNotaFiscal **lista) {
    int opcao;
    do {
        printf("\n");
        cabecalho("NOTA FISCAL");
        imprimirOpcao("1", "Cadastrar nota fiscal");
        imprimirOpcao("2", "Listar notas fiscais");
        imprimirOpcao("3", "Buscar nota fiscal por ID");
        imprimirOpcao("4", "Salvar notas fiscais");
        imprimirOpcao("5", "Carregar notas fiscais");
        printf("%s\n", MEIO);
        imprimirOpcao("0", "Voltar");
        rodape();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: NotaFiscalCadastrarView(lista); break;
            case 2: NotaFiscalListarView(lista); break;
            case 3: NotaFiscalBuscarView(lista); break;
            case 4: NotaFiscalSalvarView(lista); break;
            case 5: NotaFiscalCarregarView(lista); break;
            case 0: break;
            default: printf(VERMELHO "  Opcao invalida.\n" RESET);
        }
    } while (opcao != 0);
}

void NotaFiscalCadastrarView(ListaNotaFiscal **lista) {
    TipoNotaFiscal nota;
    NotaFiscalInit(&nota);
    int numItens = 0;
    float margemLucro = 10.0f;

    printf("\n");
    cabecalho("CADASTRAR NOTA FISCAL");
    printf("%s\n", FUNDO);

    printf("Fornecedor ID: ");
    scanf("%d", &nota.idFornecedor);
    limparBuffer();
    printf("Data (DD/MM/AAAA): ");
    lerString(nota.data, sizeof(nota.data));
    printf("Frete: ");
    scanf("%f", &nota.frete);
    limparBuffer();
    printf("Imposto: ");
    scanf("%f", &nota.imposto);
    limparBuffer();
    printf("Forma de pagamento (1=Avista / 2=Aprazo): ");
    scanf("%d", &nota.formaPagamento);
    limparBuffer();

    if (nota.formaPagamento == NF_APRAZO) {
        printf("Valor de entrada: ");
        scanf("%f", &nota.valorEntrada);
        limparBuffer();
        printf("Numero de parcelas: ");
        scanf("%d", &nota.numParcelas);
        limparBuffer();
    }

    printf("Margem de lucro (percentual): ");
    scanf("%f", &margemLucro);
    limparBuffer();
    printf("Numero de itens: ");
    scanf("%d", &numItens);
    limparBuffer();

    if (numItens > MAX_ITENS_NOTA) numItens = MAX_ITENS_NOTA;
    nota.numItens = 0;
    nota.totalNota = 0.0f;

    for (int i = 0; i < numItens; i++) {
        ItemNotaFiscal item = {0};
        printf("\nItem %d\n", i + 1);
        printf("ID do produto: ");
        scanf("%d", &item.idProduto);
        limparBuffer();
        printf("Descricao: ");
        lerString(item.descricao, sizeof(item.descricao));
        printf("Preco de custo: ");
        scanf("%f", &item.precoCusto);
        limparBuffer();
        printf("Quantidade: ");
        scanf("%d", &item.quantidade);
        limparBuffer();
        item.subtotal = item.precoCusto * item.quantidade;
        nota.itens[nota.numItens++] = item;
    }

    NotaFiscalCalcular(&nota, margemLucro);
    if (controllerNotaFiscalCadastrar(lista, nota))
        printf(VERDE "  Nota fiscal cadastrada com sucesso.\n" RESET);
    else
        printf(VERMELHO "  Erro ao cadastrar nota fiscal.\n" RESET);
}

void NotaFiscalListarView(ListaNotaFiscal **lista) {
    printf("\n");
    cabecalho("LISTAR NOTAS FISCAIS");
    controllerNotaFiscalListar(lista, 0);
}

void NotaFiscalBuscarView(ListaNotaFiscal **lista) {
    int id;
    printf("\n");
    cabecalho("BUSCAR NOTA FISCAL");
    printf("ID da nota fiscal: ");
    scanf("%d", &id);
    limparBuffer();
    controllerNotaFiscalListar(lista, id);
}

void NotaFiscalSalvarView(ListaNotaFiscal **lista) {
    if (!controllerNotaFiscalSalvar(*lista))
        printf(VERMELHO "  Falha ao salvar notas fiscais.\n" RESET);
    else
        printf(VERDE "  Notas fiscais salvas com sucesso.\n" RESET);
}

void NotaFiscalCarregarView(ListaNotaFiscal **lista) {
    if (!controllerNotaFiscalCarregar(lista))
        printf(VERMELHO "  Falha ao carregar notas fiscais.\n" RESET);
    else
        printf(VERDE "  Notas fiscais carregadas com sucesso.\n" RESET);
}
