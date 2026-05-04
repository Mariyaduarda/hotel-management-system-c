#include "../common.h"
#include "produto_controller.h"
#include "../view/produto_view.h"

void ProdutoControllerExecutar(ListaProduto **listaProduto) {
    int opcao;
    do {
        ProdutoMenuExibir();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                ProdutoCadastrarView(listaProduto);
                break;
            case 2:
                ProdutoListarView(listaProduto);
                break;
            case 3:
                ProdutoBuscarView(listaProduto);
                break;
            case 4:
                ProdutoAtualizarView(listaProduto);
                break;
            case 5:
                ProdutoExcluirView(listaProduto);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}