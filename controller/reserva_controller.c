#include "../common.h"
#include "reserva_controller.h"
#include "../view/reserva_view.h"

void ReservaControllerExecutar(ListaReserva    **listaReserva,
                                ListaCategoria **listaAcomodacao,
                                ListaCategoria  **listaCategoria,
                                ListaHospede    **listaHospede)
{
    int opcao;
    do {
        ReservaMenuExibir();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                ReservaCadastrarView(listaReserva, listaAcomodacao,
                                     listaCategoria, listaHospede);
                break;
            case 2:
                ReservaCancelarView(listaReserva);
                break;
            case 3:
                ReservaConsultarView(listaReserva);
                break;
            case 4:
                ReservaBuscarDisponiveisView(listaReserva, listaAcomodacao,
                                             listaCategoria);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}