#ifndef RESERVA_CONTROLLER_H
#define RESERVA_CONTROLLER_H

#include "../model/reserva.h"
#include "../model/acomodacao.h"
#include "../model/categoria_acomodacao.h"
#include "../model/hospede.h"

void ReservaControllerExecutar(ListaReserva    **listaReserva,
                                ListaCategoria **listaAcomodacao,
                                ListaCategoria  **listaCategoria,
                                ListaHospede    **listaHospede);

#endif // RESERVA_CONTROLLER_H