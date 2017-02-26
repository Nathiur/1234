/*
 * Silnik.c
 *
 * Created: 2017-01-02 13:37:35
 *  Author: Nathir
 */ 
#include "Naglowki.h"


uint16_t przelicz_predkosc_na_compare(uint16_t czestotliwosc)
{
	//fclk 32mhz
	//n = 1
	if(czestotliwosc>44000) return 362; // ograniczenie maks obroty silnika
	if(czestotliwosc<250) return 0xFFFF; //dla malych czestotliwosci wychodza nieskonczone okresy
	return (uint16_t) (((F_CPU/2)/czestotliwosc))-1;
}


uint16_t przelicz_compare_na_predkosc(uint16_t compare)
{	
	return (uint16_t) (F_CPU/(2*(compare+1)));
}


void init_silnik(void)
{
		// konfiguracja timera wyjscia czestotliwosci
		PORTE.DIRSET	  =	PIN4_bm;
		TCE1.CTRLB        =    TC_WGMODE_FRQ_gc | TC1_CCAEN_bm;   // tryb czestot. i ustawienie compare A
		TCE1.CTRLA        =    TC_CLKSEL_DIV1_gc; // taktowanie zegarem glownym
			
		//konfig sterowania kierunkiem
		PORTE.DIRSET = PIN1_bm;
			
}

void wylacz_silnik(void)
{
	TCE1.CTRLA        =    TC_CLKSEL_OFF_gc;
	TCE1.CNT=0;
	
	wylacz_licznik_przyspieszania();
	//_delay_ms(5); /////////////////////////////// zastanowic sie. bezwladnosci, drgania paska itd
}
void wlacz_silnik(void)
{
	TCE1.CTRLA        =    TC_CLKSEL_DIV1_gc;
}
	
void kierunek_silnik(uint8_t kierunek)
{
	if(kierunek==prawo)
		PORTE.OUTSET=PIN1_bm;
	else if(kierunek==lewo)
		PORTE.OUTCLR=PIN1_bm;
}
void ustaw_predkosc_silnik(uint16_t predkosc)
{
	TCE1.CCABUF=przelicz_predkosc_na_compare(predkosc);
}
	
/*
Do przyspieszania uzywa sie TCC1 do rownego przyrostu predkosci
Przyrost predkosci realizowany w przerwaniach niskiego priorytetu
Przyrost moze byc zarowno dodatni jak i ujemny (przysp. i hamowanie). Kierunek obslugiwany jest w obsludze przerwania.
*/
void init_przyspieszanie(void)
{
	TCC1.CTRLB=TC_WGMODE_NORMAL_gc;
	TCC1.PER=OKRES_PRZYSPIESZANIA;
	TCC1.CNT=0;
	TCC1.INTCTRLA=TC_OVFINTLVL_LO_gc;
}
	

void wlacz_licznik_przyspieszania(void)
{
	TCC1.CTRLA=TC_CLKSEL_DIV64_gc;
}

void wylacz_licznik_przyspieszania(void)
{
	TCC1.CTRLA=TC_CLKSEL_OFF_gc;
	TCC1.CNT=0;
	//wylacz i zeruj
}

void wlacz_silnik_z_przyspieszaniem(void)
{
	ustaw_predkosc_silnik(PREDKOSC_POCZATKOWA_PRZYSPIESZANIA);
	GLOB_kierunek_zmiany_predkosci=przyspieszanie;
	wlacz_licznik_przyspieszania();
	wlacz_silnik();
	
}