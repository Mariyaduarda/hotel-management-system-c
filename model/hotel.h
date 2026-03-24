#include "../common.h"

#ifndef HOTEL_H
#define HOTEL_H

    // Subdividi endereco para maximizar as info.
    typedef struct {
        char rua[100];
        int numero;
        char bairro[50];
        char cidade[50];
        char estado[3];
        char cep[10];
    } Endereco;

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

    void HotelInit(Hotel *hotel);
    void excluirHotel(Hotel *hotel);

    void HotelSalvarTxt(Hotel *hotel);
    void HotelSalvarBin(Hotel *hotel);

    void HotelExibirTxt(Hotel *hotel);
    void HotelExibirBin(Hotel *hotel);

#endif
