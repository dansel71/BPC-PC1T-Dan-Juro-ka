// Funkce.cpp: Definuje vstupní bod pro aplikaci.
//

#include "Funkce.h"
#include <math.h>
#include "soucet.h"
#include "velikost.h"
#include "skalarniSoucin.h"
#include "vektorovySoucin.h"

using namespace std;

int main()
{
	double a[3];
	double b[3];
	double c[3];
	double d[3];

	printf("Vektor A (3 hodnoty oddelene carkou):");
	scanf_s("%lf,%lf,%lf", &a[0], &a[1], &a[2]);
	printf("Vektor B (3 hodnoty oddelene carkou):");
	scanf_s("%lf,%lf,%lf", &b[0], &b[1], &b[2]);
	
	printf("\n");
	soucet(a, b, c);
	printf("Soucet A + B: (%lf, %lf, %lf)\n", c[0], c[1], c[2]);

	printf("Velikost A: (%lf)\n", velikost(a));

	printf("Skalarni soucin: (%lf)\n", skalarniSoucin(a, b));

	vektorovySoucin(a, b, d);
	printf("Vektorovy soucin: (%lf,%lf,%lf)\n", d[0], d[1], d[2]);
}
