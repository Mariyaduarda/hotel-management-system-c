#ifndef HOTEL_CONTROLLER_H
#define HOTEL_CONTROLLER_H

#include "../model/hotel.h"
#include "../view/hotel_view.h"

void HotelControllerExecutar(Hotel *hotel);
void  controllerHotelLer(Hotel *hotel);
int   controllerHotelSalvar(Hotel *hotel);
void  controllerHotelExcluir(Hotel *hotel);
float controllerHotelMargemLucro(Hotel *hotel);

#endif // HOTEL_CONTROLLER_H