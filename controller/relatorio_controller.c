#include "../common.h"
#include "relatorio_controller.h"
#include "../view/relatorio_view.h"

void RelatorioControllerExecutar(ListaHospede    **listaHospede,
                                  ListaAcomodacao **listaAcom,
                                  ListaCategoria  **listaCat,
                                  ListaReserva    **listaReserva,
                                  ListaProduto    **listaProduto)
{
    RelatorioMenuExecutar(listaHospede, listaAcom, listaCat, listaReserva, listaProduto);
}