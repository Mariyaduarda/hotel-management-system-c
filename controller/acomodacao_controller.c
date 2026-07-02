// controller/acomodacao_controller.c
#include "../common.h"
#include "../model/acomodacao.h"
#include "acomodacao_controller.h"

void AcomodacaoControllerExecutar(ListaAcomodacao **lista,
                                  ListaCategoria  **listaCat)
{
    AcomodacaoMenuExecutar(lista, listaCat);
}