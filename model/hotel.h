#include "../common.h"

#ifndef HOTEL_H
#define HOTEL_H

    /* ── Dados do Hotel ─────────────────────────────────────────────── */
    typedef struct {
        char NomeFantasia[100];
        char RazaoSocial[100];
        char InscricaoEstadual[20];
        char CNPJ[20];
        Endereco endereco;
        char Email[50];
        char NomeResp[50];
        char TelefoneResp[20];
        char Telefone[20];
        char CheckIn[6];
        char CheckOut[6];
        double MargemLucro;
        int ativo; // Verifica se existe ou nao
    } Hotel;

    /* ── Funcoes de inicializacao e outras ─────────────────────────────────────────────── */
    void HotelInit(Hotel *hotel);
    void excluirHotel(Hotel *hotel);

    int HotelSalvarTxt(Hotel *hotel);
    int HotelSalvarBin(Hotel *hotel);

    int HotelLerTxt(Hotel *hotel);
    int HotelLerBin(Hotel *hotel);

#endif
