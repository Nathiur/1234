/*
 * LiczenieKrokow.c
 *
 * Created: 2017-01-03 18:04:55
 *  Author: Nathir
 */ 
#include "Naglowki.h"

void init_liczenie_krokow(void)
{  
    PORTE.PIN4CTRL  =    PORT_OPC_PULLUP_gc|         // podci¹gniêcie do zasilania
					    PORT_ISC_FALLING_gc;        // zdarzenie mam wyso³ywaæ zbocze malej¹ce
	// to jest pin taktowania silnika. liczymy bezposrednio takty wyslane do sterownika silnika
		//^ TEN PIN TAK NAPRAWDE JEST WYJSCIEM I TRZEBA ROZKMINIC CZY PODCIAGANIE JEST POTRZEBNE
	EVSYS.CH1MUX    =    EVSYS_CHMUX_PORTE_PIN4_gc;
	TCE0.CTRLB=TC_WGMODE_NORMAL_gc|TC0_CCAEN_bm|TC0_CCBEN_bm|TC0_CCCEN_bm|TC0_CCDEN_bm; //tryb normalny, cztery wartosci compare	
	TCE0.INTCTRLB=TC_CCAINTLVL_LO_gc|TC_CCBINTLVL_LO_gc|TC_CCCINTLVL_LO_gc|TC_CCDINTLVL_LO_gc; //dol, gora, moment hamowania, zadana
		
	TCE0.CCA=POZYCJA_KRANCOWKA_LEWA+ZAPASOWY_ODSTEP_OD_KRANCOWEK;//dol
	TCE0.CCB=8200;//gora
	TCE0.CCC=5250;
	TCE0.CCD=7000;
	PMIC.CTRL         |=    PMIC_LOLVLEN_bm;            // odblokowanie przerwañ o priorytecie LO
	TCE0.CTRLA=TC_CLKSEL_EVCH1_gc; // zrodlem taktowania timera E1 jest event channel 1

}

void kierunek_liczenie_krokow(uint8_t kierunek)
{
	if(kierunek==prawo)
		TCE0.CTRLFCLR     =    TC1_DIR_bm; //w gore
	if(kierunek==lewo)
		TCE0.CTRLFSET     =    TC1_DIR_bm; //w dol
}

void zeruj_liczenie_krokow(void)
{
	TCE0.CNT=0;
}

void nadpisz_liczenie_krokow(uint16_t wartosc)
{
	TCE0.CNT=wartosc;
}

uint16_t wartosc_licznika_krokow(void)
{
	return TCE0.CNT;
}


//KRANCOWKI
void init_krancowki(void)
{
	//krancowki sa podlaczone do stykow NC
	PORTD.PIN0CTRL= PORT_OPC_PULLUP_gc | PORT_ISC_RISING_gc; // na rosnace zbocze i pullup
	PORTD.INT0MASK= PIN0_bm;
	PORTD.PIN1CTRL= PORT_OPC_PULLUP_gc | PORT_ISC_RISING_gc; // na rosnace zbocze i pullup
	PORTD.INT1MASK= PIN1_bm;
	PORTD.INTCTRL= PORT_INT0LVL_HI_gc | PORT_INT1LVL_HI_gc;
	//pd0 generuje przerwanie d.0, pd1 d.1 oba sa HI
	PMIC.CTRL         |=    PMIC_HILVLEN_bm;            // odblokowanie przerwañ o priorytecie HI
	
}