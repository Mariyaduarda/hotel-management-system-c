#ifndef CHECKIN_CONTROLLER_H
#define CHECKIN_CONTROLLER_H

#include "../model/checkin.h"

int          controllerCheckinCadastrar(ListaCheckin **lista, TipoCheckin checkin);
TipoCheckin *controllerCheckinBuscar(ListaCheckin **lista, int id);
TipoCheckin *controllerCheckinBuscarPorReserva(ListaCheckin **lista, int idReserva);
void         controllerCheckinListar(ListaCheckin **lista, int id);
int          controllerCheckinEncerrar(ListaCheckin **lista, int id, const char *dataCheckout);
int          controllerCheckinSalvar(ListaCheckin *lista);
int          controllerCheckinCarregar(ListaCheckin **lista);
void         controllerCheckinLiberar(ListaCheckin *lista);
void         CheckinControllerExecutar(ListaCheckin **lista);

#endif // CHECKIN_CONTROLLER_H
