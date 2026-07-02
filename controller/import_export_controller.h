#ifndef IMPORT_EXPORT_CONTROLLER_H
#define IMPORT_EXPORT_CONTROLLER_H

#include "../model/hospede.h"
#include "../model/reserva.h"
#include "../model/acomodacao.h"
#include "../model/categoria_acomodacao.h"
#include "../model/produto.h"
#include "../model/hotel.h"
#include "../model/operador.h"
#include "../model/nota_fiscal.h"
#include "../model/venda.h"
#include "../model/caixa.h"
#include "../model/checkin.h"
#include "../model/contas_pagar.h"
#include "../model/contas_receber.h"
#include "../model/fornecedor.h"

#include "../common.h"

void ImportExportControllerExecutar(ListaHospede **listaHospede,
                                   ListaReserva **listaReserva,
                                   ListaAcomodacao **listaAcomodacao,
                                   ListaCategoria **listaCategoria,
                                   ListaProduto **listaProduto,
                                   Hotel *hotel,
                                   ListaOperador **listaOperador,
                                   ListaNotaFiscal **listaNotaFiscal,
                                   ListaVenda **listaVenda,
                                   ListaCaixa **listaCaixa,
                                   ListaCheckin **listaCheckin,
                                   ListaContaPagar **listaContaPagar,
                                   ListaContaReceber **listaContaReceber);

#endif
