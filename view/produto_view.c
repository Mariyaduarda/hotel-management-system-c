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

void ProdutoMenuExecutar(ListaProduto **lista) {
    int opcao;
    do {
        ProdutoMenuExibir();
        opcao = ler_int("");

        switch (opcao) {
            case 1: ProdutoCadastrarView(lista); break;
            case 2: ProdutoListarView(lista);    break;
            case 3: ProdutoBuscarView(lista);    break;
            case 4: ProdutoAtualizarView(lista); break;
            case 5: ProdutoExcluirView(lista);   break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

void ProdutoCadastrarView(ListaProduto **lista) {
    TipoProduto p;
    ProdutoInit(&p);

    printf("\n-- Cadastro de Produto --\n");

    ler_string("Descricao: ", p.descricao, sizeof(p.descricao));
    p.estoque = ler_int("Estoque inicial: ");
    p.estoqueMinimo = ler_int("Estoque minimo: ");
    p.precoCusto = ler_float("Preco de custo: ");
    p.precoVenda = ler_float("Preco de venda: ");

    ProdutoCriar(lista, p);
}

void ProdutoListarView(ListaProduto **lista) {
    printf("\n-- Lista de Produtos --\n");
    ProdutoListar(lista, 0);
}

void ProdutoBuscarView(ListaProduto **lista) {
    int id;
    printf("\n-- Buscar Produto --\n");
    id = ler_int("ID do produto: ");

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
    id = ler_int("ID do produto: ");

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
    op = ler_int("Opcao: ");

    ProdutoAtualizar(lista, id, op);
}

void ProdutoExcluirView(ListaProduto **lista) {
    int id;
    printf("\n-- Excluir Produto --\n");
    id = ler_int("ID do produto: ");

    TipoProduto *p = ProdutoBuscar(lista, id);
    if (!p) {
        printf("Produto ID %d nao encontrado.\n", id);
        return;
    }

    printf("Confirma exclusao de \"%s\"? (1=Sim / 0=Nao): ", p->descricao);
    int confirma;
    confirma = ler_int("");

    if (confirma == 1)
        ProdutoExcluir(lista, id);
    else
        printf("Exclusao cancelada.\n");
}