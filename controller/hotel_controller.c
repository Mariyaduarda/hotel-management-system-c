/* controller/hotel_controller.c */
#include "../common.h"
#include "hotel_controller.h"

void HotelControllerExecutar(Hotel *hotel) {
    HotelMenuExecutar(hotel);
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
    return HotelPrimeiroCadastroView(hotel);
}