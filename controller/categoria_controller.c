#include "../common.h"
#include "../model/categoria_acomodacao.h"
#include "categoria_controller.h"
#include "../view/categoria_view.h"

void CategoriaControllerExecutar(ListaCategoria **lista) {
    int opcao;
    do {
        CategoriaMenuExibir();
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: CategoriaCadastrarView(lista);  break;
            case 2: CategoriaListarTodosView(lista); break;
            case 3: CategoriaBuscarView(lista);     break;
            case 4: CategoriaAtualizarView(lista);  break;
            case 5: CategoriaExcluirView(lista);    break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}