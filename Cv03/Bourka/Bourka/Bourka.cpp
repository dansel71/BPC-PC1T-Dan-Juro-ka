// Bourka.cpp: Definuje vstupní bod pro aplikaci.
//

#include "Bourka.h"

using namespace std;

int main()
{
	float cas;
	const double rychlost_zvuku = 340;

	printf("Kolik sekund jsi napocital potom, co blesk uhodil?: ");
	scanf_s("%fl", &cas);

	printf("Blesk je daleko: %lf\n", cas*rychlost_zvuku);

	return 0;
}
