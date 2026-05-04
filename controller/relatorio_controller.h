#ifndef RELATORIO_CONTROLLER_H
#define RELATORIO_CONTROLLER_H

#include "../model/hospede.h"
#include "../model/acomodacao.h"
#include "../model/categoria_acomodacao.h"
#include "../model/reserva.h"
#include "../model/produto.h"

void RelatorioControllerExecutar(ListaHospede    **listaHospede,
                                  ListaAcomodacao **listaAcom,
                                  ListaCategoria  **listaCat,
                                  ListaReserva    **listaReserva,
                                  ListaProduto    **listaProduto);

#endif // RELATORIO_CONTROLLER_H