/* controller/hotel_controller.c */
#include "../common.h"
#include "hotel_controller.h"

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