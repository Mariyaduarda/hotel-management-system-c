// controller/hospede_controller.c
#include "../common.h"
#include "../model/hospede.h"
#include "hospede_controller.h"

/* ──────────────────────────────────────────────────────────
   Cadastrar novo hóspede
   Retorna 1 em sucesso, 0 em falha
   ────────────────────────────────────────────────────────── */
int controllerHospedeCadastrar(ListaHospede **lista, TipoHospede h) {
    return HospedeCriar(lista, h);
}

/* ──────────────────────────────────────────────────────────
   Listar hóspede por ID
   ────────────────────────────────────────────────────────── */
void controllerHospedeListar(ListaHospede **lista, int id) {
    HospedeListar(lista, id);
}

/* ──────────────────────────────────────────────────────────
   Buscar hóspede por ID
   Retorna ponteiro para TipoHospede ou NULL se não encontrado
   ────────────────────────────────────────────────────────── */
TipoHospede *controllerHospedeBuscar(ListaHospede **lista, int id) {
    return HospedeBuscar(lista, id);
}

/* ──────────────────────────────────────────────────────────
   Atualizar campo(s) do hóspede
   op: 1=todos 2=nome 3=cpf 4=email 5=tel 6=sexo 7=nasc 8=est.civil
   Retorna 1 em sucesso, 0 em falha
   ────────────────────────────────────────────────────────── */
int controllerHospedeAtualizar(ListaHospede **lista, int id, int op) {
    return HospedeAtualizar(lista, id, op);
}

/* ──────────────────────────────────────────────────────────
   Exclusão lógica do hóspede (ativo = 0)
   Retorna 1 em sucesso, 0 se não encontrado
   ────────────────────────────────────────────────────────── */
int controllerHospedeExcluir(ListaHospede **lista, int id) {
    return HospedeExcluir(lista, id);
}

/* ──────────────────────────────────────────────────────────
   Persistência — salvar
   ────────────────────────────────────────────────────────── */
int controllerHospedeSalvar(ListaHospede *lista) {
    if (!HospedeSalvarTxt(lista)) return 0;
    if (!HospedeSalvarBin(lista)) return 0;
    return 1;
}

/* ──────────────────────────────────────────────────────────
   Persistência — carregar (tenta .bin, cai em .txt)
   ────────────────────────────────────────────────────────── */
int controllerHospedeCarregar(ListaHospede **lista) {
    if (HospedeLerBin(lista)) return 1;
    return HospedeLerTxt(lista);
}

/* ──────────────────────────────────────────────────────────
   Liberar lista da memória
   ────────────────────────────────────────────────────────── */
void controllerHospedeLiberar(ListaHospede *lista) {
    HospedeListaLiberar(lista);
}