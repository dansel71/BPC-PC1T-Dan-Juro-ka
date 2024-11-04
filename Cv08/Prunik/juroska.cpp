#pragma once 
#include "juroska.h"

int prunik(double zacatek1, double konec1, double zacatek2, double konec2,
	double* vysl_zacatek, double* vysl_konec) {
	double pruhoz;
	if (zacatek1 > konec1) { // když je první cislo intervalu vetsi nez druhe, tak se cisla prohodi
		pruhoz = zacatek1;
		zacatek1 = konec1;
		konec1 = pruhoz;
	}
	if (zacatek2 > konec2) { // když je první cislo intervalu vetsi nez druhe, tak se cisla prohodi
		pruhoz = zacatek2;
		zacatek2 = konec2;
		konec2 = pruhoz;
	}
	if (zacatek1 > zacatek2) { // když je zacatek1 intervalu vetsi nez zacatek2, tak se cisla prohodi
		pruhoz = zacatek1;
		zacatek1 = zacatek2;
		zacatek2 = pruhoz;
		pruhoz = konec1;
		konec1 = konec2;
		konec2 = pruhoz;
	}
	
	
	
	if (konec1 >= zacatek2) {
		*vysl_zacatek = zacatek2;
		if (konec1 < konec2) {
		*vysl_konec = konec1;
		}
		else {
		*vysl_konec = konec2;
		}
		
		return 1;
	}
	else {
		return 0;
	}
}