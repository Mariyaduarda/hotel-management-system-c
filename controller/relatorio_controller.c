#include "../common.h"
#include "relatorio_controller.h"
#include "../view/relatorio_view.h"

void RelatorioControllerExecutar(ListaHospede    **listaHospede,
                                  ListaAcomodacao **listaAcom,
                                  ListaCategoria  **listaCat,
                                  ListaReserva    **listaReserva,
                                  ListaProduto    **listaProduto)
{
    int opcao;
    do {
        RelatorioMenuExibir();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: RelatorioHospedesView(listaHospede);                              break;
            case 2: RelatorioAcomodacoesView(listaAcom, listaCat);                    break;
            case 3: RelatorioReservasView(listaReserva);                              break;
            case 4: RelatorioMovimentacaoView(listaReserva, listaAcom, listaCat);     break;
            case 5: RelatorioProdutosView(listaProduto);                              break;
            case 6: RelatorioProdutosEstoqueView(listaProduto);                       break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}