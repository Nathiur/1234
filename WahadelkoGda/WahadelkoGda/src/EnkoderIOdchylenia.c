/*
 * EnkoderIOdchylenia.c
 *
 * Created: 2017-02-14 19:09:31
 *  Author: Nathir
 */ 
#include "Naglowki.h"

void init_enkoder(void)
{
	

	// wejœcia enkodera
	PORTCFG.MPCMASK    =    PIN0_bm | PIN1_bm;                // wybór pinów 0 i 1 do konfiguracji
	PORTA.PIN0CTRL     =    PORT_ISC_LEVEL_gc |               // reagowanie na poziom niski
	PORT_OPC_PULLUP_gc;               // podci¹gniêcie do zasilania
	
	// konfiguracja systemu zdarzeñ
	EVSYS.CH0MUX       =    EVSYS_CHMUX_PORTA_PIN0_gc;        // pin A0 wywo³uje zdarzenie
	EVSYS.CH0CTRL      =    EVSYS_QDEN_bm|                    // w³¹czenie dekodera w systemie zdarzeñ
	EVSYS_DIGFILT_8SAMPLES_gc;        // filtr cyfrowy
	
	// konfiguracja timera
	TCC0.CTRLA         =    TC_CLKSEL_EVCH0_gc;               // taktowanie systemem zdarzeñ
	TCC0.CTRLD         =    TC_EVACT_QDEC_gc |                // w³¹czenie dekodera kwadraturowego
	TC_EVSEL_CH0_gc;                  // dekoder zlicza impulsy z kana³u 0
	
}

void zeruj_licznik_enkodera(void)
{
	TCC0.CNT=0;
}

void nadpisz_licznik_enkodera(uint16_t wartosc)
{
	TCC0.CNT=wartosc;
}

void resetuj_punkt_odniesienia_enkodera(void)
{
	wylacz_silnik();
	wylacz_licznik_przyspieszania();
	///////////// ZAMIENIC NA INNY SPOSOB. JESLI CZTERY KOLEJNE PROBKI Z LICZNIKA SA TAKIE SAME (stale) to wahadlo sie nie rusza. probkowac np. co 20ms. wtedy wyzerowac.
	int i;
	for(i=0;i<50;i++)
	_delay_ms(150);
	
	zeruj_licznik_enkodera();	
}