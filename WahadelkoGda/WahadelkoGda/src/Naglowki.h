/*
 * Naglowki.h
 *
 * Created: 2016-12-31 18:23:00
 *  Author: Nathir
 */ 

// Zastanow sie czy przerwanie osiagniecia pozycji zadanej nie powinno czasem miec priorytetu MID. Jest wazniejsze od np. przyspieszania/hamowania
//
/*
krancowki  - drgaja styki
okres drgan 1ms
drgania wystepuja przy zalaczaniu i wylaczaniu styku i jest kijowo
*/

//PODLACZENIA
/*
Sterownik silnika:
Pulse (przez tranzystor) - E4
DIR (tranzystor) - E1
krancowka lewa (normalnie zamknieta) - D0
krancowka prawa (normalnie zamknieta) - D1

*/

//WYKORZYSTYWANE PERYFERIA WEWNETRZNE
/*

//#########################################################################
****TIMERY*****
//#########################################################################
C0 - enkoder
C1 - przyspieszanie wozka
E0 - aktualne polozenie wozka
E1 - generowanie przebiegu silnika

//#########################################################################
*** SYSTEM ZDARZEN*****
//#########################################################################
CH0 - enkoder
CH1 - taktowanie licznika pozycji wozka

//#########################################################################
*** PRZERWANIA I PRIORYTETY ***
//#########################################################################

-------> LOW
(TCC1_OVF_vect) //od timera przyspieszania

(TCE0_CCA_vect) //pozycja: dolna granica
(TCE0_CCB_vect) //pozycja: gorna granica
(TCE0_CCC_vect) //pozycja: poczatek hamowania
(TCE0_CCD_vect) //pozycja: zadana

-------> MED



-------> HI
PORTD_INT0_vect //krancowka lewa
PORTD_INT1_vect //krancowka prawa
*/


#ifndef INCFILE1_H_
#define INCFILE1_H_
#endif /* INCFILE1_H_ */

#define F_CPU 32000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "hd44780.h"






//#########################################################################
//*****************STALE******************
//#########################################################################
#define lewo 0
#define prawo 1

//*********************************
//parametry silnika
#define MAKS_CZESTOTLIWOSC_SILNIKA 12000UL



//*********************************
//parametry przyspieszania i hamowania

		//PRZYSPIESZANIE
#define OKRES_PRZYSPIESZANIA 90UL //co jaki czas jest aktualizowana predkosc
#define KROK_PRZYSPIESZANIA 10UL // co jaka wartosc predkosc rosnie
#define PREDKOSC_POCZATKOWA_PRZYSPIESZANIA 1000

	//--wynikowe przyspieszenie
#define WARTOSC_PRZYSP ((500000/OKRES_PRZYSPIESZANIA)*(KROK_PRZYSPIESZANIA))


		//HAMOWANIE
#define OKRES_HAMOWANIA 90UL
#define KROK_HAMOWANIA 20UL
#define PREDKOSC_KONCOWA_HAMOWANIA (PREDKOSC_POCZATKOWA_PRZYSPIESZANIA)

	//--wynikowe hamowanie
#define WARTOSC_HAMOW ((500000/OKRES_HAMOWANIA)*(KROK_HAMOWANIA))

#define przyspieszanie 1
#define brak 0
#define hamowanie -1

		//RAMPY RUCHU
//Roznica miedzy maks i minimalna predkoscia
#define DELTA_V (MAKS_CZESTOTLIWOSC_SILNIKA-PREDKOSC_POCZATKOWA_PRZYSPIESZANIA)
//Minimalna droga dla rampy typu 1
#define DROGA_MIN_RAMPY_1 ((uint32_t)((((PREDKOSC_POCZATKOWA_PRZYSPIESZANIA*DELTA_V)+((float)(DELTA_V)*(DELTA_V)/2))/(float)WARTOSC_HAMOW/WARTOSC_PRZYSP)*(WARTOSC_HAMOW+WARTOSC_PRZYSP)))

#define STALA_WCZESNEGO_HAMOWANIA_RAMPY_1 ((uint32_t)((((float)PREDKOSC_POCZATKOWA_PRZYSPIESZANIA/WARTOSC_HAMOW*DELTA_V)+((float)DELTA_V/WARTOSC_HAMOW*DELTA_V/2)))) //rzutujemy floaty na inty

//typy rampy
#define pierwszy 1
#define drugi 2


//*********************************
//licznik pozycji
#define POZYCJA_KRANCOWKA_LEWA 100
#define ZAPASOWY_ODSTEP_OD_KRANCOWEK 400









//#########################################################################
//**************ZMIENNE GLOBALNE*******************
//#########################################################################

extern volatile signed char GLOB_kierunek_zmiany_predkosci;
extern volatile uint8_t GLOB_flaga_rampa_pozycja_osiagnieta;
//#########################################################################
//**************FUNKCJE*******************
//#########################################################################
		//PrzyMain
void Osc32MHz(void);
void konfiguracja(void);
void bazuj(void);


		//Silnik
uint16_t przelicz_predkosc_na_compare(uint16_t czestotliwosc);
uint16_t przelicz_compare_na_predkosc(uint16_t compare);
void init_silnik(void);
void wylacz_silnik(void);
void wlacz_silnik(void);
void kierunek_silnik(uint8_t kierunek);
void ustaw_predkosc_silnik(uint16_t predkosc);
void init_przyspieszanie(void);
void wlacz_licznik_przyspieszania(void);
void wylacz_licznik_przyspieszania(void);
void wlacz_silnik_z_przyspieszaniem(void);


		//Licznik krokow (aktualne polozenie)

void init_liczenie_krokow(void);
void kierunek_liczenie_krokow(uint8_t kierunek);
void zeruj_liczenie_krokow(void);
void nadpisz_liczenie_krokow(uint16_t wartosc);
uint16_t wartosc_licznika_krokow(void);
void init_krancowki(void);

		//Rampa ruchu

void Rampa_Jedz_Do_Pozycji(uint16_t pozycja);
uint8_t TypRampy(uint16_t modul_drogi);
int16_t Przelicz_pozycje_bezwgledna_na_wzgledna_droge(uint16_t pozycja);
void R1_ustaw_wartosci_compare(int16_t droga_wzgledna, int8_t znak);
void R2_ustaw_wartosci_compare(uint16_t modul_drogi,int8_t znak);
uint16_t R2_licz_x2(uint16_t modul_drogi);

		//Enkoder i odchylenie wahadla

void init_enkoder(void);
void zeruj_licznik_enkodera(void);
void nadpisz_licznik_enkodera(uint16_t wartosc);
void resetuj_punkt_odniesienia_enkodera(void);

		//RegulatorPID
		
float RegulatorPID(uint16_t wyjscie);