/*
 * ZmienneGlobalne.c
 *
 * Created: 2017-02-10 14:40:10
 *  Author: Nathir
 */ 
#include "Naglowki.h"

volatile signed char GLOB_kierunek_zmiany_predkosci; //do okreslania czy licznik deltaV ma hamowac czy przyspieszac
volatile uint8_t GLOB_flaga_rampa_pozycja_osiagnieta;