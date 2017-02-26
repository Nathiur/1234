/*
 * RegulatorPID.c
 *
 * Created: 2017-02-14 19:46:44
 *  Author: Nathir
 */ 
#include "Naglowki.h"


float RegulatorPID(uint16_t wyjscie)
{
	uint16_t wart_zad = 1200;
	float k=2;
	float k_i=3;
	float k_d=2;
	
	float p,i,d,r;
	float u;
	static float u_p=0;
	static float su=0;
	
	
	u=wart_zad-wyjscie;
	
	//
	p=k*u;
	
	//
	su=su+u;
	i=k_i*su;
	
	//
	d=k_d*(u-u_p);
	u_p=u;
	r=p+i+d;
	return r;
	
}