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
        opcao = ler_int("");

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

    // cabecalho
    printf("\n");
    cabecalho("CADASTRAR NOTA FISCAL");
    printf("%s\n", FUNDO);

    // ler dados
    nota.idFornecedor = ler_int("Fornecedor ID: ");
    ler_string("Data (DD/MM/AAAA): ", nota.data, sizeof(nota.data));
    nota.frete = ler_float("Frete: ");
    nota.imposto = ler_float("Imposto: ");
    nota.formaPagamento = ler_int("Forma de pagamento (1=Avista / 2=Aprazo): ");
    if (nota.formaPagamento == NF_APRAZO) {
        nota.valorEntrada = ler_float("Valor de entrada: ");
        nota.numParcelas = ler_int("Numero de parcelas: ");
    }
    margemLucro = ler_float("Margem de lucro (percentual): ");
    numItens = ler_int("Numero de itens: ");

    if (numItens > MAX_ITENS_NOTA) numItens = MAX_ITENS_NOTA;
    nota.numItens = 0;
    nota.totalNota = 0.0f;

    for (int i = 0; i < numItens; i++) {

        ItemNotaFiscal item = {0};
        printf("\nItem %d\n", i + 1);

        item.idProduto = ler_int("ID do produto: ");
        ler_string("Descricao: ", item.descricao, sizeof(item.descricao));    
        item.precoCusto = ler_float("Preco de custo: ");
        item.quantidade = ler_int("Quantidade: ");
        
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
    id = ler_int("ID da nota fiscal: ");
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
