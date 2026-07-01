#include "../common.h"
#include "relatorio_controller.h"
#include "../view/relatorio_view.h"

void RelatorioControllerExecutar(ListaHospede        **listaHospede,
                                  ListaAcomodacao      **listaAcomodacao,
                                  ListaCategoria       **listaCategoria,
                                  ListaReserva         **listaReserva,
                                  ListaProduto         **listaProduto,
                                  ListaVenda           **listaVenda,
                                  ListaCaixa           **listaCaixa,
                                  ListaContaReceber    **listaContaReceber,
                                  ListaContaPagar      **listaContaPagar)
{
    int opcao;

    do {
        RelatorioMenuExibir();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                RelatorioHospedesView(listaHospede);
                break;

            case 2:
                RelatorioAcomodacoesView(listaAcomodacao, listaCategoria);
                break;

            case 3:
                RelatorioReservasView(listaReserva);
                break;

            case 4:
                RelatorioMovimentacaoView(listaReserva, listaAcomodacao, listaCategoria);
                break;

            case 5:
                RelatorioProdutosView(listaProduto);
                break;

            case 6:
                RelatorioProdutosEstoqueView(listaProduto);
                break;

            case 7:
                RelatorioVendasView(listaVenda);
                break;

            case 8:
                RelatorioContasReceberView(listaContaReceber);
                break;

            case 9:
                RelatorioContasPagarView(listaContaPagar);
                break;

            // case 10: Movimentacao de Caixa -> aguardando integracao do modulo de Caixa no main

            case 0:
                printf("\nVoltando ao menu anterior...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (opcao != 0);
}