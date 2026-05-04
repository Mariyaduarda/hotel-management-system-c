#ifndef RESERVA_CONTROLLER_H
#define RESERVA_CONTROLLER_H

#include "../model/reserva.h"
#include "../model/acomodacao.h"   // TipoCategoria esta aqui tambem
#include "../model/hospede.h"

// Funcoes no padrao controller* (usadas pela view)
int          controllerReservaCriar(ListaReserva **lista, TipoReserva reserva,
                                     ListaAcomodacao **listaAcom);
TipoReserva *controllerReservaBuscar(ListaReserva **lista, int id);
int          controllerReservaCancelar(ListaReserva **lista, int id);
int          controllerReservaDisponivel(ListaReserva **lista, int idAcomodacao,
                                          const char *entrada, const char *saida);

#endif // RESERVA_CONTROLLER_H