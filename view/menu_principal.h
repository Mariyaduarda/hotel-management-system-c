#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#include "../model/hospede.h"
#include "../model/reserva.h"
#include "../model/acomodacao.h"
#include "../model/categoria_acomodacao.h"
#include "../model/produto.h"
#include "../model/hotel.h"
#include "../model/nota_fiscal.h"
#include "../model/venda.h"
#include "../model/checkin.h"
#include "../model/contas_pagar.h"
#include "../model/contas_receber.h"

void menuPrincipal(ListaHospede    **listaHospede,
                   ListaReserva    **listaReserva,
                   ListaAcomodacao **listaAcomodacao,
                   ListaCategoria  **listaCategoria,
                   ListaProduto    **listaProduto,
                   Hotel           *hotel,
                   ListaNotaFiscal **listaNotaFiscal,
                   ListaVenda      **listaVenda,
                   ListaCheckin    **listaCheckin,
                   ListaContaPagar **listaContaPagar,
                   ListaContaReceber **listaContaReceber);

#endif // MENU_PRINCIPAL_H