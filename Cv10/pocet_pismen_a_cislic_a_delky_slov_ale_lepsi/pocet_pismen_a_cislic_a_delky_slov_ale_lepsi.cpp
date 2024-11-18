// pocet_pismen_a_cislic_a_delky_slov_ale_lepsi.cpp: Definuje vstupní bod pro aplikaci.
//

#include "pocet_pismen_a_cislic_a_delky_slov_ale_lepsi.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

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

void DelkySlov(char* text) {
	int delkaslova = 0;
	int poprve = 0;
	while (*text) {
		if (isalpha(*text)) {
			++delkaslova;
		}
		else {
			if (delkaslova != 0) {
				if (poprve == 0) {
					printf("%d", delkaslova);
					poprve = 1;
				}
				else {
					printf(", %d", delkaslova);
				}
			}
			delkaslova = 0;
		}
		text++;
	}
}




int main()
{
	const char* CestaVstup = "..\\..\\..\\vstup.txt";
	FILE* vstup;
	fopen_s(&vstup, CestaVstup, "r");
	char text;
	long length;
	char c;

	// Přejdeme na konec souboru, abychom zjistili jeho velikost
	fseek(vstup, 0, SEEK_END);
	length = ftell(vstup);
	fseek(vstup, 0, SEEK_SET);  // Vraťme se zpět na začátek souboru

	// Alokování paměti pro buffer
	text = (char)malloc(length + 1);  // +1 pro nulový terminátor

	// Čtení souboru do bufferu
	fread(&text, 1, length, vstup);
	text[&length] = '\0';  // Přidání nulového terminátoru na konec řetězce

	printf("Testovany text zde:\n");
	printf("\n");
	printf_s("Pocet pismen: %d.\n", PocetPismen(&text));
	printf_s("Pocet cislic: %d.\n", PocetCislic(&text));
	printf_s("Delky slov: ");
	DelkySlov(&text);

	return 0;
}
