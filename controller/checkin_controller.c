/* controller/checkin_controller.c */
#include "../common.h"
#include "../model/checkin.h"
#include "../view/checkin_view.h"
#include "checkin_controller.h"

int controllerCheckinCadastrar(ListaCheckin **lista, TipoCheckin checkin) {
    return CheckinCriar(lista, checkin);
}

TipoCheckin *controllerCheckinBuscar(ListaCheckin **lista, int id) {
    return CheckinBuscar(lista, id);
}

TipoCheckin *controllerCheckinBuscarPorReserva(ListaCheckin **lista, int idReserva) {
    return CheckinBuscarPorReserva(lista, idReserva);
}

void controllerCheckinListar(ListaCheckin **lista, int id) {
    CheckinListar(lista, id);
}

int controllerCheckinEncerrar(ListaCheckin **lista, int id, const char *dataCheckout) {
    return CheckinEncerrar(lista, id, dataCheckout);
}

int controllerCheckinSalvar(ListaCheckin *lista) {
    if (!CheckinSalvarTxt(lista)) return 0;
    if (!CheckinSalvarBin(lista)) return 0;
    return 1;
}

int controllerCheckinCarregar(ListaCheckin **lista) {
    if (CheckinLerBin(lista)) return 1;
    return CheckinLerTxt(lista);
}

void controllerCheckinLiberar(ListaCheckin *lista) {
    CheckinListaLiberar(lista);
}

void CheckinControllerExecutar(ListaCheckin **lista) {
    CheckinMenuView(lista);
}
