/*
 * FunkcjePrzyMain.c
 *
 * Created: 2017-02-07 23:48:33
 *  Author: Nathir
 */ 

#include "Naglowki.h"

void Osc32MHz(void) {
	OSC.CTRL     =    OSC_RC32MEN_bm;       // w³¹czenie oscylatora 32MHz
	while(!(OSC.STATUS & OSC_RC32MRDY_bm)); // czekanie na ustabilizowanie siê generatora
	CPU_CCP      =    CCP_IOREG_gc;         // odblokowanie zmiany Ÿród³a sygna³u
	CLK.CTRL     =    CLK_SCLKSEL_RC32M_gc; // zmiana Ÿród³a sygna³u na RC 32MHz
	
}

void konfiguracja(void)
{
	// konfiguracja przycisku FLIP
	PORTE.DIRCLR    =  PIN5_bm;             // pin E5 jako wejœcie
	PORTE.PIN5CTRL  =  PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;  // podci¹gniêcie do zasilania i zbocze opadajace
	///////////////////////////////////////^^^^^^^^^^^^!!!!!!!!!!!!!!!!#########$$$$$$$$$$$ to trzeba bedzie chyba potem wywalic.
	init_liczenie_krokow();
	init_silnik();
	init_przyspieszanie();
	init_enkoder();
}

void bazuj(void)
{
	wylacz_silnik();
	kierunek_silnik(lewo);
	ustaw_predkosc_silnik(1500);
	PORTD.PIN0CTRL= PORT_OPC_PULLUP_gc; //podciaganie na wejsciach krancowek
	PORTD.PIN1CTRL= PORT_OPC_PULLUP_gc;
	wlacz_silnik();
		while (!(PORTD.IN & PIN0_bm)) //czekamy az napotka krancowke
		{
		}
	wylacz_silnik();
	nadpisz_liczenie_krokow(POZYCJA_KRANCOWKA_LEWA);
	kierunek_silnik(prawo);
	kierunek_liczenie_krokow(prawo);
	wlacz_silnik();
	while (wartosc_licznika_krokow()<=POZYCJA_KRANCOWKA_LEWA+ZAPASOWY_ODSTEP_OD_KRANCOWEK)
	{
	}
	wylacz_silnik();
	
	if(PORTD.INTFLAGS&& 0b1) //czyszczenie flag przerwan od krancowek. lewa
	PORTD.INTFLAGS=0b1;
		
	if(PORTD.INTFLAGS&& 0b10) //czyszczenie flag przerwan od krancowek. prawa
	PORTD.INTFLAGS=0b10;
	
}