// Auta.cpp : Defines the entry point for the application.
//

#include "Hudba.h"

#include <stdio.h>
#include <ctype.h>              // tolower
#include <stdlib.h>				// system

#include "HudbaDB.h"

struct t_album* prvni = NULL; // globalni ukazatel na prvni album

void OnAdd()
{
	char my_interpret[INTERPRET_SIZE];
	char my_name[NAME_SIZE];
	int my_year;

	printf("\nNazev interpreta : ");         // dotazeme se na polozky
	fgets(my_interpret, INTERPRET_SIZE, stdin);
	my_interpret[strcspn(my_interpret, "\n")] = '\0';
	printf("\nNazev alba : ");
	fgets(my_name, NAME_SIZE, stdin);
	my_name[strcspn(my_name, "\n")] = '\0';
	printf("\nRok : ");
	scanf_s("%d", &my_year);
	while (getchar() != '\n');
	add(my_interpret, my_name, my_year, &prvni);         // volame pridavaci funkci
}

void OnDel()
{
	int my_name;

	printf("\nRok : ");
	scanf_s("%d", &my_name);
	while (getchar() != '\n');
	del(my_name, &prvni);         // volame mazaci funkci
}

void ShowAlbums()
{
	struct t_album* aktAlbum = prvni; // ukazatel na aktualni album
	char pocatecniPismeno;

	printf("Zadejte pocatecni pismeno interpreta: ");
	scanf(" %c", &pocatecniPismeno); // ziskani vstupu od uzivatele
	getchar(); // odstraneni nového řádku ze vstupního bufferu
	pocatecniPismeno = tolower(pocatecniPismeno); // převedení na malé písmeno pro porovnání

	printf("\nSeznam alb:\n");
	while (aktAlbum) // prochazeni seznamu
	{
		// kontrola, zda jméno interpreta začíná zadaným písmenem (case-insensitive)
		if (tolower(aktAlbum->interpret[0]) == pocatecniPismeno)
		{
			printf("%d: %s, %s\n", aktAlbum->rok, aktAlbum->interpret, aktAlbum->name); // tisk radku
		}
		aktAlbum = aktAlbum->dalsi; // posun na dalsi album
	}
	getchar(); // cekani na vstup pro zastaveni
}


int main()
{
	char  cmd;

	do
	{
		system("cls");		// smaze obrazovku
		printf("A: Pridat     ");
		printf("D: Smazat     ");
		printf("P: Tisk     ");
		printf("Q: Konec\n\n");

		cmd = tolower(getchar());
		while (getchar() != '\n');

		switch (cmd)
		{
		case 'a':
			OnAdd();					// volame pridani
			break;
		case 'd':
			OnDel();					// volame mazani
			break;
		case 'p':
			ShowAlbums();
			break;
		}
	} while (cmd != 'q');     // koncime az pri Q
	return 0;
}


