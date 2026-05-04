// controller/hospede_controller.h
#ifndef HOSPEDE_CONTROLLER_H
#define HOSPEDE_CONTROLLER_H

#include "../model/hospede.h"

int          controllerHospedeCadastrar (ListaHospede **lista, TipoHospede h);
void         controllerHospedeListar    (ListaHospede **lista, int id);
TipoHospede *controllerHospedeBuscar    (ListaHospede **lista, int id);
int          controllerHospedeAtualizar (ListaHospede **lista, int id, int op);
int          controllerHospedeExcluir   (ListaHospede **lista, int id);
int          controllerHospedeSalvar    (ListaHospede  *lista);
int          controllerHospedeCarregar  (ListaHospede **lista);
void         controllerHospedeLiberar   (ListaHospede  *lista);
void         HospedeControllerExecutar  (ListaHospede **lista);

#endif