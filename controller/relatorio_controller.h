#ifndef RELATORIO_CONTROLLER_H
#define RELATORIO_CONTROLLER_H

#include "../model/hospede.h"
#include "../model/acomodacao.h"
#include "../model/categoria_acomodacao.h"
#include "../model/reserva.h"
#include "../model/produto.h"
#include "../model/venda.h"
#include "../model/caixa.h"
#include "../model/contas_receber.h"
#include "../model/contas_pagar.h"

// Executa o menu de relatorios, recebendo todas as listas do sistema
void RelatorioControllerExecutar(ListaHospede        **listaHospede,
                                  ListaAcomodacao      **listaAcomodacao,
                                  ListaCategoria       **listaCategoria,
                                  ListaReserva         **listaReserva,
                                  ListaProduto         **listaProduto,
                                  ListaVenda           **listaVenda,
                                  ListaCaixa           **listaCaixa,
                                  ListaContaReceber    **listaContaReceber,
                                  ListaContaPagar      **listaContaPagar);

#endif // RELATORIO_CONTROLLER_H