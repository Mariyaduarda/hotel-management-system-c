#ifndef HOTEL_VIEW_H
#define HOTEL_VIEW_H

#include "../model/hotel.h"

void HotelMenuExibir(void);
void HotelMenuExecutar(Hotel *hotel);
void HotelExibir(Hotel *hotel);
void HotelEditarView(Hotel *hotel);
int HotelPrimeiroCadastroView(Hotel *hotel);

#endif // HOTEL_VIEW_H