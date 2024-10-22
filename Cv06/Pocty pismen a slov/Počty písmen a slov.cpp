// Počty písmen a slov.cpp: Definuje vstupní bod pro aplikaci.
//

#include "Počty písmen a slov.h"
#include <ctype.h>

using namespace std;

int PocetPismen(char* text) {
	int vysledek = 0;
	while (*(++text) != '\0') {
		if (isalpha(*text)) ++vysledek;
	}
	return vysledek;
}

int PocetCislic(char* text) {
	int vysledek = 0;
	while (*(++text) != '\0') {
		if (isdigit(*text)) ++vysledek;
	}
	return vysledek;
}

int DelkySlov(char* text) {
	typedef int slova [][2];;
        printf("\n");
        return 0;
	}
	

int main() {
	char text[] = "Toto jsou 2 vzorove vety, ktere budou zpracovavany Vasemi funkcemi. Auto Hyundai ix35 ma pres 120 konskych sil.";
	printf("Testovany text zde:\n");
	printf(text);
	printf("\n");
	printf("Pocet pismen: %d.\n", PocetPismen(text));
	printf("Pocet cislic: %d.\n", PocetCislic(text));
	printf("Delky slov: %d.\n", DelkySlov(text));

	return 0;
}
