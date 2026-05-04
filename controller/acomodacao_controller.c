// controller/acomodacao_controller.c
#include "../common.h"
#include "../model/acomodacao.h"
#include "acomodacao_controller.h"

void AcomodacaoControllerExecutar(ListaAcomodacao **lista,
                                  ListaCategoria  **listaCat)
{
    int opcao;
    do {
        printf("\n");
        AcomodacaoMenuExibir();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: AcomodacaoCadastrarView(lista, listaCat); break;
            case 2: AcomodacaoListarView(lista, listaCat);    break;
            case 3: AcomodacaoBuscarView(lista, listaCat);    break;
            case 4: AcomodacaoAtualizarView(lista, listaCat); break;
            case 5: AcomodacaoExcluirView(lista);             break;
            case 0: break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}