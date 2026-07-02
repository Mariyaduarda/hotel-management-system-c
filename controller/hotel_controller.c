/* controller/hotel_controller.c */
#include "../common.h"
#include "hotel_controller.h"

void HotelControllerExecutar(Hotel *hotel) {
    int opcao;
    do {
        printf("\n=== CONFIGURACAO DO HOTEL ===\n");
        printf("[1] Ver dados do hotel\n");
        printf("[2] Editar hotel\n");
        printf("[3] Excluir hotel\n");
        printf("[0] Voltar\n");
        opcao = ler_int("Opcao: ");
        
        switch (opcao) {
            case 1:
                HotelExibir(hotel);
                break;
            case 2:
                HotelEditarView(hotel);
                controllerHotelSalvar(hotel);
                break;
            case 3:
                controllerHotelExcluir(hotel);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

int controllerHotelSalvar(Hotel *hotel) {
    return HotelSalvar(hotel);
}

void controllerHotelExcluir(Hotel *hotel) {
    ExcluirHotel(hotel);
}

float controllerHotelMargemLucro(Hotel *hotel) {
    return (float)hotel->MargemLucro;
}

// Primeiro cadastro do hotel, caso nao tenha nenhum dado salvo
int controllerHotelPrimeiroCadastro(Hotel *hotel) {

    printf("\n=== Cadastrar Hotel ===\n");

    ler_string(" Nome Fantasia: ",           hotel->NomeFantasia,         sizeof(hotel->NomeFantasia)         );
    ler_string(" Razao Social: ",            hotel->RazaoSocial,          sizeof(hotel->RazaoSocial)          );
    ler_string(" Inscricao Estadual: ",      hotel->InscricaoEstadual,    sizeof(hotel->InscricaoEstadual)    );
    ler_string(" CNPJ: ",                    hotel->CNPJ,                 sizeof(hotel->CNPJ)                 );
    ler_string(" Email: ",                   hotel->Email,                sizeof(hotel->Email)                );
    ler_string(" Telefone: ",                hotel->Telefone,             sizeof(hotel->Telefone)             );
    ler_string(" Nome do Responsavel: ",     hotel->NomeResp,             sizeof(hotel->NomeResp)             );
    ler_string(" Telefone do Responsavel: ", hotel->TelefoneResp,         sizeof(hotel->TelefoneResp)         );
    ler_string(" Rua: ",                     hotel->endereco.rua,         sizeof(hotel->endereco.rua)         );
    ler_string(" Numero: ",                  hotel->endereco.numero,      sizeof(hotel->endereco.numero)      );
    ler_string(" Complemento: ",             hotel->endereco.complemento, sizeof(hotel->endereco.complemento) );
    ler_string(" Bairro: ",                  hotel->endereco.bairro,      sizeof(hotel->endereco.bairro)      );
    ler_string(" Cidade: ",                  hotel->endereco.cidade,      sizeof(hotel->endereco.cidade)      );
    ler_string(" Estado: ",                  hotel->endereco.estado,      sizeof(hotel->endereco.estado)      );
    ler_string(" CEP: ",                     hotel->endereco.cep,         sizeof(hotel->endereco.cep)         );
    ler_string(" Check-in (HH:MM): ",        hotel->CheckIn,              sizeof(hotel->CheckIn)              );
    ler_string(" Check-out (HH:MM): ",       hotel->CheckOut,             sizeof(hotel->CheckOut)             );
    hotel->MargemLucro = ler_float(" Margem de Lucro (%%): ");
    hotel->TipoSalvamento = ler_int(" Tipo de Salvamento (0-TXT, 1-BIN, 2-Nao salvar): ");
    return controllerHotelSalvar(hotel);
}