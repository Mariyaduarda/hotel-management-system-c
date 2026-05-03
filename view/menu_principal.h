#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#include "../model/hospede.h"
#include "../model/reserva.h"
#include "../model/acomodacao.h"
#include "../model/categoria_acomodacao.h"
#include "../model/produto.h"
#include "../model/hotel.h"

void menuPrincipal(ListaHospede    **listaHospede,
                   ListaReserva    **listaReserva,
                   ListaAcomodacao **listaAcomodacao,
                   ListaCategoria  **listaCategoria,
                   ListaProduto    **listaProduto,
                   Hotel           *hotel);

#endif // MENU_PRINCIPAL_H