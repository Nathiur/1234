/*
 * RampaRuchu.c
 *
 * Created: 2017-02-11 12:56:05
 *  Author: Nathir
 */ 

#include "Naglowki.h"


/*
Potrzebne jest wyznaczenie od ktorego miejsca nalezy zaczac hamowanie.

Zakladam stala wartosc przyspieszenia.
Zakladam stala wartosc opoznienia (hamowania).

Mo¿liwe przypadki kszta³tu rampy ruchu: 2


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Pierwszy:::::::::::::::::::::::::::

Droga jest dluga. Wozek zdazy sie rozpedzic do pelnej predkosci. 
Wtedy:
Hamowanie zawsze od predkosci maksymalnej do minimalnej.
Czas hamowania (a raczej liczba krokow potrzebna do gladkiego hamowania) jest znana i stala.
Nie trzeba nic liczyc.
Moment hamowania = (pozycja koncowa) - (stala odleglosc hamowania).

A
|
|      ___ ____           <- Vmax
|     /        \
|    /          \
|   /            \
|  |              |
------------------------------------->

Pierwszy przypadek zachodzi dla s>= ((a+d)/(a*d))*(Vo*deltaV+ (1/2)*(deltaV)^2)
a-przysp.
d-hamowanie
Vo-pr. minimalna, poczatkowa i koncowa
deltaV- roznica miedzy maksymalna a Vo

Dla s mniejszego od tego wyrazenia mamy przypadek drugi:
_________________________________________________________________________________________________________________________________________________
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Drugi::::::::::::::::::::::::::

Droga jest krotka. Wozek nie zdazy osiagnac maksymalnej predkosci.
Trzeba obliczyc do jakiej predkosci sie rozpedzic, zeby zdazyc wyhamowac i jednoczesnie dojechac mozliwie szybko.



A
|________________________________  <- Vmax nigdy nie osiagnieta
|     
|     /\
|    /  \
|   /    \
|  |      |
------------------------------------->

Droga przyspieszania - x1
Droga hamowania - x2
Calkowita droga - x3
Wartosc przyspieszania - a
Wartosc hamowania - d

x1= x3*d/(a+d)
x2= x3*a/(a+d)



*/
void Rampa_Jedz_Do_Pozycji(uint16_t pozycja)
{
		uint8_t kierunek;
		
		if(pozycja>wartosc_licznika_krokow())
		kierunek=prawo;
		else
		kierunek=lewo;
		
		int8_t znak;
		if(kierunek==prawo) znak=1;
		else znak=-1;
		
	int16_t droga_wzgledna;
	droga_wzgledna=Przelicz_pozycje_bezwgledna_na_wzgledna_droge(pozycja);
	
	uint16_t modul_drogi;
	
	if(droga_wzgledna>= 0)
	modul_drogi=droga_wzgledna;
	else
	modul_drogi=((int16_t)((-1)*(droga_wzgledna)));
	
	
		if(TypRampy(modul_drogi)==drugi)
			R2_ustaw_wartosci_compare(modul_drogi,znak);
		else
			R1_ustaw_wartosci_compare(droga_wzgledna,znak);
		
	
	kierunek_silnik(kierunek);
	kierunek_liczenie_krokow(kierunek);
	wlacz_silnik_z_przyspieszaniem();
}

uint8_t TypRampy(uint16_t modul_drogi)
{
		
	if((modul_drogi>=DROGA_MIN_RAMPY_1))
		return pierwszy;
	else
		return drugi;
}


int16_t Przelicz_pozycje_bezwgledna_na_wzgledna_droge(uint16_t pozycja)
{
	return pozycja-wartosc_licznika_krokow();
}


void R1_ustaw_wartosci_compare(int16_t droga_wzgledna, int8_t znak)
{	
	TCE0.CCD=wartosc_licznika_krokow()+droga_wzgledna;
	TCE0.CCC=TCE0.CCD-znak*STALA_WCZESNEGO_HAMOWANIA_RAMPY_1;
}

void R2_ustaw_wartosci_compare(uint16_t modul_drogi,int8_t znak)
{
	TCE0.CCD=wartosc_licznika_krokow()+modul_drogi*znak;
	TCE0.CCC=(uint16_t)(TCE0.CCD-R2_licz_x2(modul_drogi)*znak);	
}


uint16_t R2_licz_x2(uint16_t modul_drogi)
{
	//x2 opisane w komentarzu powyzej. jest to droga potrzebna do hamowania. O wartosc tej drogi wczesniej trzeba zaczac hamowac
	return ((uint16_t)modul_drogi*WARTOSC_PRZYSP/(int32_t)(WARTOSC_PRZYSP+WARTOSC_HAMOW));
	
	
}

