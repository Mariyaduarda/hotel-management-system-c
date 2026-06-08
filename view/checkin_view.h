#ifndef CHECKIN_VIEW_H
#define CHECKIN_VIEW_H

#include "../model/checkin.h"

void CheckinMenuView(ListaCheckin **lista);
void CheckinCadastrarView(ListaCheckin **lista);
void CheckinListarView(ListaCheckin **lista);
void CheckinBuscarView(ListaCheckin **lista);
void CheckinBuscarPorReservaView(ListaCheckin **lista);
void CheckinEncerrarView(ListaCheckin **lista);
void CheckinSalvarView(ListaCheckin **lista);
void CheckinCarregarView(ListaCheckin **lista);

#endif // CHECKIN_VIEW_H
