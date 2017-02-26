/*
 * ObslugaPrzerwan.c
 *
 * Created: 2017-02-07 23:47:39
 *  Author: Nathir
 */ 

#include "Naglowki.h"

//#########################################################################
//**************HIGH*******************
//#########################################################################


ISR(PORTD_INT0_vect)//PRIO:HI //osiagnieto lewa krancowke
{
	wylacz_silnik();	
	LcdClear();		
	Lcd("Kran l");
	Lcd2;
	Lcd("KRK=");
	LcdDec(TCE0.CNT);
	while(1); //WIECZNA PETLA ZLOWIESZCZA
	
}

ISR(PORTD_INT1_vect)//PRIO:HI // osiagnieto prawa krancowke
{
	wylacz_silnik();	
	LcdClear();
	Lcd("Kran p");
	Lcd2;
	Lcd("KRK=");
	LcdDec(TCE0.CNT);
	while(1);// WIECZNA PETLA
}


//#########################################################################
//**************MEDIUM*******************
//#########################################################################




//#########################################################################
//**************LOW*******************
//#########################################################################


ISR(TCC1_OVF_vect)//PRIO: LOW //od timera przyspieszania
{
	if(GLOB_kierunek_zmiany_predkosci==przyspieszanie)
	{
		if(przelicz_compare_na_predkosc(TCE1.CCA)<MAKS_CZESTOTLIWOSC_SILNIKA) //jesli nie ma jeszcze predkosci maksymalnej
			TCE1.CCABUF=przelicz_predkosc_na_compare( przelicz_compare_na_predkosc(TCE1.CCA) + KROK_PRZYSPIESZANIA); //zwieksz predkosc o krok_przyspieszania
		else
		{
			GLOB_kierunek_zmiany_predkosci=brak;
			wylacz_licznik_przyspieszania();
		}
	}
	else if(GLOB_kierunek_zmiany_predkosci==hamowanie)
	{
		if(przelicz_compare_na_predkosc(TCE1.CCA)>PREDKOSC_KONCOWA_HAMOWANIA) //jesli nie ma jeszcze predkosci minimalnej
				TCE1.CCABUF=przelicz_predkosc_na_compare( przelicz_compare_na_predkosc(TCE1.CCA) + (int16_t)(-1)*KROK_HAMOWANIA); //zmniejsz predkosc o krok_hamowania
		else
		{
			GLOB_kierunek_zmiany_predkosci=brak;
			wylacz_licznik_przyspieszania();
						
		}
	}
}


ISR(TCE0_CCA_vect) // przerwanie przepe³nienia TCE0 dol
{                                   
	
	//wylacz_silnik();
	LcdClear();
	Lcd("Tutaj");
	/*
	_delay_ms(100);
	
	wylacz_silnik();
	kierunek_silnik(prawo);
	kierunek_liczenie_krokow(prawo);
	
	ustaw_predkosc_silnik(1000);
	//wlacz_silnik();
		wlacz_silnik_z_przyspieszaniem();
	*/
}

ISR(TCE0_CCB_vect) // przerwanie przepe³nienia TCE0 gora (prawo)
{                                   
		
	//wylacz_silnik();
	LcdClear();
	Lcd("Tutaj");
	//Rampa_Jedz_Do_Pozycji(2000);          
	
}

ISR(TCE0_CCC_vect) //przerwanie od hamowania
{	
	GLOB_kierunek_zmiany_predkosci=hamowanie;
	wlacz_licznik_przyspieszania();
	LcdClear();/////////////////////////////
}

ISR(TCE0_CCD_vect) //przerwanie od osiagniecia pozycji zadanej
{
	
	wylacz_silnik();
	GLOB_flaga_rampa_pozycja_osiagnieta=1;
	/*
	//pozycje to 600, 5000, 8000
	
	
	if(wartosc_licznika_krokow()>500 && wartosc_licznika_krokow()< 700) //gdy jestesmy w 600
	Rampa_Jedz_Do_Pozycji(5000);
	if(wartosc_licznika_krokow()>4900 && wartosc_licznika_krokow()< 5100)
	Rampa_Jedz_Do_Pozycji(8000);
	if(wartosc_licznika_krokow()>7900 && wartosc_licznika_krokow()< 8100)
	Rampa_Jedz_Do_Pozycji(600);
	*/
	
}