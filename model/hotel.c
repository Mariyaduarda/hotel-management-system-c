#include "hotel.h"
#include "../common.h"
#include <string.h>

void HotelInit(Hotel *hotel){
    
    strcpy(hotel->NomeFantasia,      "-");
    strcpy(hotel->RazaoSocial,       "-");
    strcpy(hotel->InscricaoEstadual, "-");
    strcpy(hotel->CNPJ,              "-");
    strcpy(hotel->Email,             "-");
    strcpy(hotel->Telefone,          "-");
    strcpy(hotel->NomeResp,          "-");
    strcpy(hotel->CheckIn,           "00:00");
    strcpy(hotel->CheckOut,          "00:00");
    strcpy(hotel->TelefoneResp,      "-");

    hotel->ativo = 0; // Evita exclusao fisica

    // Inicializa endereco
    strcpy(hotel->endereco.rua,     "-");
    strcpy(hotel->endereco.bairro,  "-");
    strcpy(hotel->endereco.cidade,  "-");
    strcpy(hotel->endereco.estado,  "--"); 
    strcpy(hotel->endereco.cep,     "-");
    hotel->endereco.numero = 0;

    hotel->MargemLucro = 0.0f;
}

void ExcluirHotel(Hotel *hotel){
    HotelInit(hotel);    // Remove em mem
    
    remove("hotel.txt"); //Remove em texto
    remove("hotel.bin");  // Remove em bin

    printf("Sistema resetado. Todos os dados do hotel foram excluidos.\n");
}

    void HotelSalvarTxt(Hotel *hotel);
    void HotelSalvarBin(Hotel *hotel);

    void HotelExibirTxt(Hotel *hotel);
    void HotelExibirBin(Hotel *hotel);
