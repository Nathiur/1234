#include "Naglowki.h"


int main(void) {
	
	Osc32MHz();
	konfiguracja();
	LcdInit(); 	
			Lcd("C");
			LcdDec(STALA_WCZESNEGO_HAMOWANIA_RAMPY_1);
			LcdGoto(9,0);

			Lcd("A");
			LcdDec(WARTOSC_PRZYSP);
			
			Lcd2;
			Lcd("S");
			LcdDec(DROGA_MIN_RAMPY_1);
			LcdGoto(9,1);
			
			Lcd("D");
			LcdDec(WARTOSC_HAMOW);
			
			LcdGoto(7,0);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
			_delay_ms(100);
	
	bazuj();
	init_krancowki();
	sei();// globalne odblokowanie przerwañ
	/*
		kierunek_silnik(prawo);
		kierunek_liczenie_krokow(prawo);
		ustaw_predkosc_silnik(1000);
		wlacz_silnik();
		LcdClear();
		Lcd2;
		*/
	GLOB_flaga_rampa_pozycja_osiagnieta=0;
	Rampa_Jedz_Do_Pozycji(4000);
	

		
 while(1) {
	 
	 
	 
	 //_delay_ms(10);                     // czekanie 100ms
	 
	 LcdClear();
	 LcdDec(TCC0.CNT);
	 while(GLOB_flaga_rampa_pozycja_osiagnieta==0);
	 GLOB_flaga_rampa_pozycja_osiagnieta=0;
	 Rampa_Jedz_Do_Pozycji(wartosc_licznika_krokow()-RegulatorPID(TCC0.CNT));
	 
	 
	 
	 
	 if(!(PORTE.IN & PIN5_bm)) {                    // je¿eli przycisk FLIP wciœniêty
		TCC0.CNT=0;
	 }
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
/*	 
	 // wyœwietlenie aktualnej wartoœci licznika CNT i PER
	 // CNT = ...ENC
	 // PER = ...
	 LcdClear();
	 Lcd2;
	 Lcd("KRK=");
	 LcdDec(TCE0.CNT);	 
	 LcdGoto(7,0);
	 Lcd("CCA=");
	 LcdDec(TCE1.CCA);
	 LcdGoto(0,0);
	 Lcd("FRQ=");
	 LcdDec(TCC0.CNT);//trzeba rozkminic czy nie dzielic na 4 licznika enkodera
	
	*/
	 
	 
	 
	 
	 /*
	 if(!(PORTE.IN & PIN5_bm)) {                    // je¿eli przycisk FLIP wciœniêty
		 if(stan)
		 {
			 kierunek_silnik(prawo);
			 kierunek_liczenie_krokow(prawo);
			 wlacz_silnik();
			 stan=0;
			 
		 }
		 else
		 {
			 wylacz_silnik();
			 TCE0.CNT=1000; //nadpisz licznik krokow
			 stan=1;
		 }
	 }
	 */
	 
	 
 }
	 
}