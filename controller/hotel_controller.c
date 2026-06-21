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
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

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

    printf("Nome Fantasia: ");
    lerString(hotel->NomeFantasia, sizeof(hotel->NomeFantasia));
    
    printf("Razao Social: ");
    lerString(hotel->RazaoSocial, sizeof(hotel->RazaoSocial));
    
    printf("Inscricao Estadual: ");
    lerString(hotel->InscricaoEstadual, sizeof(hotel->InscricaoEstadual));
    
    printf("CNPJ: ");
    lerString(hotel->CNPJ, sizeof(hotel->CNPJ));
    
    printf("Email: ");
    lerString(hotel->Email, sizeof(hotel->Email));
    
    printf("Telefone: ");
    lerString(hotel->Telefone, sizeof(hotel->Telefone));
    
    printf("Nome do Responsavel: ");
    lerString(hotel->NomeResp, sizeof(hotel->NomeResp));
    
    printf("Telefone do Responsavel: ");
    lerString(hotel->TelefoneResp, sizeof(hotel->TelefoneResp));
    
    printf("Rua: ");
    lerString(hotel->endereco.rua, sizeof(hotel->endereco.rua));
    
    printf("Numero: ");
    lerString(hotel->endereco.numero, sizeof(hotel->endereco.numero));
    
    printf("Complemento: ");
    lerString(hotel->endereco.complemento, sizeof(hotel->endereco.complemento));
    
    printf("Bairro: ");
    lerString(hotel->endereco.bairro, sizeof(hotel->endereco.bairro));
    
    printf("Cidade: ");
    lerString(hotel->endereco.cidade, sizeof(hotel->endereco.cidade));
    
    printf("Estado: ");
    lerString(hotel->endereco.estado, sizeof(hotel->endereco.estado));
    
    printf("CEP: ");
    lerString(hotel->endereco.cep, sizeof(hotel->endereco.cep));
    
    printf("Check-in (HH:MM): ");
    lerString(hotel->CheckIn, sizeof(hotel->CheckIn));
    
    printf("Check-out (HH:MM): ");
    lerString(hotel->CheckOut, sizeof(hotel->CheckOut));
    
    printf("Margem de Lucro (%%): ");
    scanf("%lf", &hotel->MargemLucro);
    limparBuffer();
    
    printf(" 0. Salvar em TXT              \n");
    printf(" 1. Salvar em BIN              \n");
    printf(" 2. Nao salvar (apenas memoria)\n");
    printf("Tipo de Salvamento: ");
    scanf("%d", &hotel->TipoSalvamento);
    limparBuffer();

    return controllerHotelSalvar(hotel);
}