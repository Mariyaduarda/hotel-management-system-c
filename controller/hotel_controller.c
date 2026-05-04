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

void controllerHotelLer(Hotel *hotel) {
    HotelLerBin(hotel);
}

int controllerHotelSalvar(Hotel *hotel) {
    if (!HotelSalvarTxt(hotel)) return 0;
    if (!HotelSalvarBin(hotel)) return 0;
    return 1;
}

void controllerHotelExcluir(Hotel *hotel) {
    ExcluirHotel(hotel);
}

float controllerHotelMargemLucro(Hotel *hotel) {
    return (float)hotel->MargemLucro;
}