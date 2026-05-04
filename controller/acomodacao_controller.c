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
        printf("=== ACOMODACOES ===\n");
        printf("[1] Cadastrar acomodacao\n");
        printf("[2] Listar acomodacao\n");
        printf("[3] Atualizar acomodacao\n");
        printf("[4] Excluir acomodacao\n");
        printf("[0] Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                AcomodacaoCadastrarView(lista, listaCat);
                break;
            case 2:
                AcomodacaoListarView(lista, listaCat);
                break;
            case 3:
                AcomodacaoAtualizarView(lista, listaCat);
                break;
            case 4:
                AcomodacaoExcluirView(lista);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}