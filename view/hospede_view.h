#ifndef HOSPEDE_VIEW_H
#define HOSPEDE_VIEW_H

#include "../model/hospede.h"

void menuHospede(ListaHospede **lista);
void HospedeCadastrarView(ListaHospede **lista);
void HospedeListarTodosView(ListaHospede **lista);
void HospedeBuscarView(ListaHospede **lista);
void HospedeAtualizarView(ListaHospede **lista);
void HospedeExcluirView(ListaHospede **lista);

#endif // HOSPEDE_VIEW_H