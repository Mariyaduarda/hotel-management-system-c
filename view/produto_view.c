#include "../common.h"
#include "produto_view.h"

void ProdutoMenuExibir(void) {
    printf("\n╔══════════════════════════════╗\n");
    printf(  "║       MENU DE PRODUTOS       ║\n");
    printf(  "╠══════════════════════════════╣\n");
    printf(  "║ 1. Cadastrar produto         ║\n");
    printf(  "║ 2. Listar produtos           ║\n");
    printf(  "║ 3. Buscar produto por ID     ║\n");
    printf(  "║ 4. Atualizar produto         ║\n");
    printf(  "║ 5. Excluir produto           ║\n");
    printf(  "║ 0. Voltar                    ║\n");
    printf(  "╚══════════════════════════════╝\n");
    printf("Opcao: ");
}

void ProdutoCadastrarView(ListaProduto **lista) {
    TipoProduto p;
    ProdutoInit(&p);

    printf("\n-- Cadastro de Produto --\n");

    printf("Descricao: ");
    scanf(" %99[^\n]", p.descricao);

    printf("Estoque inicial: ");
    scanf("%d", &p.estoque);
    limparBuffer();

    printf("Estoque minimo: ");
    scanf("%d", &p.estoqueMinimo);
    limparBuffer();

    printf("Preco de custo: ");
    scanf("%f", &p.precoCusto);
    limparBuffer();

    printf("Preco de venda: ");
    scanf("%f", &p.precoVenda);
    limparBuffer();

    ProdutoCriar(lista, p);
}

void ProdutoListarView(ListaProduto **lista) {
    printf("\n-- Lista de Produtos --\n");
    ProdutoListar(lista, 0);
}

void ProdutoBuscarView(ListaProduto **lista) {
    int id;
    printf("\n-- Buscar Produto --\n");
    printf("ID do produto: ");
    scanf("%d", &id);
    limparBuffer();

    TipoProduto *p = ProdutoBuscar(lista, id);
    if (!p) {
        printf("Produto ID %d nao encontrado.\n", id);
        return;
    }

    printf("\n%-5s %-30s %-8s %-10s %-12s %-12s %-6s\n",
           "ID", "Descricao", "Estoque", "Est.Min.", "Preco Custo", "Preco Venda", "Ativo");
    printf("--------------------------------------------------------------------------------\n");
    printf("%-5d %-30s %-8d %-10d %-12.2f %-12.2f %-6s\n",
           p->id, p->descricao, p->estoque, p->estoqueMinimo,
           p->precoCusto, p->precoVenda, p->ativo ? "Sim" : "Nao");
}

void ProdutoAtualizarView(ListaProduto **lista) {
    int id, op;
    printf("\n-- Atualizar Produto --\n");
    printf("ID do produto: ");
    scanf("%d", &id);
    limparBuffer();

    TipoProduto *p = ProdutoBuscar(lista, id);
    if (!p) {
        printf("Produto ID %d nao encontrado.\n", id);
        return;
    }

    printf("Produto encontrado: %s\n", p->descricao);
    printf("\nO que deseja atualizar?\n");
    printf("1. Descricao\n");
    printf("2. Estoque\n");
    printf("3. Estoque minimo\n");
    printf("4. Preco de custo\n");
    printf("5. Preco de venda\n");
    printf("6. Ativar/Desativar\n");
    printf("Opcao: ");
    scanf("%d", &op);
    limparBuffer();

    ProdutoAtualizar(lista, id, op);
}

void ProdutoExcluirView(ListaProduto **lista) {
    int id;
    printf("\n-- Excluir Produto --\n");
    printf("ID do produto: ");
    scanf("%d", &id);
    limparBuffer();

    TipoProduto *p = ProdutoBuscar(lista, id);
    if (!p) {
        printf("Produto ID %d nao encontrado.\n", id);
        return;
    }

    printf("Confirma exclusao de \"%s\"? (1=Sim / 0=Nao): ", p->descricao);
    int confirma;
    scanf("%d", &confirma);
    limparBuffer();

    if (confirma == 1)
        ProdutoExcluir(lista, id);
    else
        printf("Exclusao cancelada.\n");
}