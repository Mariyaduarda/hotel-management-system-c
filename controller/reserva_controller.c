#include "../common.h"
#include "reserva_controller.h"
#include "../view/reserva_view.h"

void ReservaControllerExecutar(ListaReserva    **listaReserva,
                                ListaAcomodacao **listaAcomodacao,
                                ListaCategoria  **listaCategoria,
                                ListaHospede    **listaHospede)
{
    ReservaMenuExecutar(listaReserva, listaAcomodacao, listaCategoria, listaHospede);
}