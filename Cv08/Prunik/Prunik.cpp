// Prunik.cpp: Definuje vstupní bod pro aplikaci.
//

#include "Prunik.h"
#include "juroska.h"

using namespace std;

int main()
{
	double zacatek1;
	double konec1;
	double zacatek2;
	double konec2;
	double vysl_zacatek;
	double vysl_konec;
	printf("Zadej 2 intervaly, cisla oddeluj carkou : ");
	scanf_s("%lf, %lf, %lf, %lf", &zacatek1, &konec1, &zacatek2, &konec2);
	if (prunik(zacatek1, konec1, zacatek2, konec2, &vysl_zacatek, &vysl_konec)) {
		printf("Prunik funkci: (%lf, %lf)", vysl_zacatek, vysl_konec);
	}
	else {
		printf("Nema prunik");
	}

	return 0;
}
