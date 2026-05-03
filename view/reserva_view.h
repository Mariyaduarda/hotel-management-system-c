#ifndef RESERVA_VIEW_H
#define RESERVA_VIEW_H

#include "../model/reserva.h"
#include "../model/acomodacao.h"
#include "../model/categoria_acomodacao.h"
#include "../model/hospede.h"

// Menus
void ReservaMenuExibir();
void ReservaCadastrarView(ListaReserva **listaReserva,
                          ListaAcomodacao **listaAcomodacao,
                          ListaCategoria  **listaCategoria,
                          ListaHospede    **listaHospede);
void ReservaCancelarView(ListaReserva **lista);
void ReservaConsultarView(ListaReserva **lista);
void ReservaBuscarDisponiveisView(ListaReserva    **listaReserva,
                                   ListaAcomodacao **listaAcomodacao,
                                   ListaCategoria  **listaCategoria);

#endif // RESERVA_VIEW_H