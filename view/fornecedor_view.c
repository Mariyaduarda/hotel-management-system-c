/* view/fornecedor_view.c */
#include "../common.h"
#include "../controller/fornecedor_controller.h"
#include "fornecedor_view.h"

#define TOPO  "╔══════════════════════════════════════════════════════════╗"
#define MEIO  "╠══════════════════════════════════════════════════════════╣"
#define FUNDO "╚══════════════════════════════════════════════════════════╝"
#define BORDA "║"

static void cabecalho(const char *titulo) {
    printf("%s\n", TOPO);
    printf("%s  %-54s%s\n", BORDA, titulo, BORDA);
    printf("%s\n", MEIO);
}

static void opcao(const char *tecla, const char *desc) {
    printf("%s  [%s] %-52s%s\n", BORDA, tecla, desc, BORDA);
}

static void rodape(void) {
    printf("%s\n", FUNDO);
    printf("  Opcao: ");
}

static void separador(void) {
    printf("%s\n", MEIO);
}

/* ── Cadastrar ───────────────────────────────────────────── */
static void viewFornecedorCadastrar(ListaFornecedor **lista) {
    TipoFornecedor f;
    FornecedorInit(&f);

    printf("\n--- Novo Fornecedor ---\n");
    ler_string("  Nome Fantasia      : ", f.nomeFantasia,      sizeof(f.nomeFantasia));
    ler_string("  Razao Social       : ", f.razaoSocial,       sizeof(f.razaoSocial));
    ler_string("  Inscricao Estadual : ", f.inscricaoEstadual, sizeof(f.inscricaoEstadual));
    ler_string("  CNPJ               : ", f.cnpj,              sizeof(f.cnpj));
    ler_string("  Endereco completo  : ", f.endereco,          sizeof(f.endereco));
    ler_string("  Telefone           : ", f.telefone,          sizeof(f.telefone));
    ler_string("  E-mail             : ", f.email,             sizeof(f.email));



    if (controllerFornecedorCadastrar(lista, f))
        printf("\nFornecedor cadastrado com sucesso!\n");
    else
        printf("\nErro ao cadastrar fornecedor.\n");
}

/* ── Listar ─────────────────────────────────────────────── */
static void viewFornecedorListar(ListaFornecedor **lista) {
    int id;
    id = ler_int("\n  ID do fornecedor: ");
    controllerFornecedorListar(lista, id);
}

/* ── Atualizar ───────────────────────────────────────────── */
static void viewFornecedorAtualizar(ListaFornecedor **lista) {
    int id;
    id = ler_int("\n  ID do fornecedor: ");

    printf("  [1] Nome Fantasia\n");
    printf("  [2] Razao Social\n");
    printf("  [3] Inscricao Estadual\n");
    printf("  [4] CNPJ\n");
    printf("  [5] Endereco\n");
    printf("  [6] Telefone\n");
    printf("  [7] E-mail\n");
    int op;
    op = ler_int("  Campo: ");

    if (controllerFornecedorAtualizar(lista, id, op))
        printf("\n  Dados atualizados!\n");
    else
        printf("\n  Fornecedor nao encontrado.\n");
}

/* ── Excluir ─────────────────────────────────────────────── */
static void viewFornecedorExcluir(ListaFornecedor **lista) {
    int id;
    id = ler_int("\n  ID do fornecedor: ");

    if (controllerFornecedorExcluir(lista, id))
        printf("\n  Fornecedor desativado.\n");
    else
        printf("\n  Fornecedor nao encontrado.\n");
}

/* ── Menu principal ─────────────────────────────────────── */
void menuFornecedor(ListaFornecedor **lista) {
    char op;
    do {
        limparTela();
        cabecalho("FORNECEDORES");
        opcao("C", "Cadastrar");
        opcao("L", "Listar por ID");
        opcao("A", "Atualizar");
        opcao("E", "Excluir");
        separador();
        opcao("V", "Voltar");
        rodape();
        op = ler_char("");
        op = toupper(op);

        switch (op) {
        case 'C': viewFornecedorCadastrar(lista); pausar(); break;
        case 'L': viewFornecedorListar(lista);    pausar(); break;
        case 'A': viewFornecedorAtualizar(lista); pausar(); break;
        case 'E': viewFornecedorExcluir(lista);   pausar(); break;
        case 'V': break;
        default:
            printf("\n  Opcao invalida.\n");
            pausar();
        }
    } while (op != 'V');
}