#ifndef HOSPEDE_H
#define HOSPEDE_H

#include "../common.h"

/* ── Hospede Dados ────────────────────────────── */
typedef struct {
    int id;
    char nome[100];
    char cpf[20];
    char email[50];
    char telefone[20];
    char sexo[50];
    char dataNascimento[11];
    char estadoCivil[50];
    int ativo; // Verifica se existe ou nao
    Endereco endereco;
} TipoHospede;

/* ── Lista de Hospedes ─────────────────────────────────────────────── */
// usando lista encadeada para armazenar os hospedes
typedef struct ListaHospede {
    struct ListaHospede *proximo;
    TipoHospede hospede;
} ListaHospede;

/* ── Funcoes de inicialização e outras ────────────────────────────── */
void HospedeInit(TipoHospede *hospede);
void HospedeListaInit(ListaHospede *hospede);

/** * = sem necessiddade de alterar o endereco de memoria
    ** = com necessidade de alterar o endereco de memoria **/
int HospedeCriar(ListaHospede **lista, TipoHospede hospede);
void HospedeListar(ListaHospede **lista, int id);
TipoHospede* HospedeBuscar(ListaHospede **lista, int id);
int HospedeExcluir(ListaHospede **lista, int id);
int HospedeAtualizar(ListaHospede **lista, int id, int op);
void HospedeListaLiberar(ListaHospede *lista);

// Funcoes de arquivo
// Leitura de arquivo gera espaço na memoria
int HospedeSalvarTxt(ListaHospede *lista);
int HospedeSalvarBin(ListaHospede *lista);
int HospedeLerTxt(ListaHospede **lista);
int HospedeLerBin(ListaHospede **lista);

#endif // HOSPEDE_H