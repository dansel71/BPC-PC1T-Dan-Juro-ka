
#include "22_restauracni_zarizeni.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkce.h"
#include "macros.h"



int main() {
    Restaurant* restaurants = NULL;
    Restaurant* restaurant = NULL;  // Deklarace promenne pred switch

    int choice;
    char name[MAX_NAME_LEN];
    int rating;
    char comment[MAX_COMMENT_LEN];

    loadDatabase(&restaurants);
    sortRestaurantsAlphabetically(&restaurants); // Na zacatku se restaurace pokazde seradi, aby se zabranilo prevraceni seznamu vzhuru nohama:p

    do {
        //printAscii();

        printf("\n1. Pridat restauraci\n");
        printf("2. Odstranit restauraci\n");
        printf("3. Pridat hodnoceni\n");
        printf("4. Vypsat restaurace\n");
        printf("5. Radit restaurace podle nazvu\n");
        printf("6. Radit podle hodnoceni\n");
        printf("0. Ulozit a ukoncit\n\n");
        printf("Vyberte moznost: ");
        if ((scanf("%d", &choice)) == 1) { // Skenuje hodnotu choice a zaroven filtruje pismena
            getchar();

            switch (choice) {
            default: {
                system("cls");
                printf("Neplatna volba.\n");
                break;
            }
            case 1: {
                system("cls");
                printf("Zadejte nazev restaurace: ");
                int x = 0;
                fgets(name, MAX_NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';
                addRestaurant(&restaurants, name, 1);

                break;
            }
            case 2: {
                system("cls");
                listRestaurants(restaurants);
                printf("\nZadejte nazev restaurace pro odstraneni: ");
                fgets(name, MAX_NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';
                deleteRestaurant(&restaurants, name);
                break;
            }
            case 3: {
                system("cls");
                listRestaurants(restaurants);
                printf("\nZadejte nazev restaurace pro pridani hodnoceni: ");
                fgets(name, MAX_NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';
                Restaurant* restaurant = findRestaurant(restaurants, name);
                if (restaurant != NULL) {
                    system("cls");
                    printf("Zadejte hodnoceni (1-5): ");
                    scanf("%d", &rating);
                    if (rating < 1 || rating > 5) {
                        system("cls");
                        printf("Neplatne hodnoceni. Zadejte hodnotu mezi 1 a 5.\n");
                        break;
                    }
                    else {
                        printf("Zadejte komentar: ");
                        getchar();
                        fgets(comment, MAX_COMMENT_LEN, stdin);
                        comment[strcspn(comment, "\n")] = '\0';
                        addReview(restaurant, rating, comment, 1);
                    }
                }
                else {
                    system("cls");
                    printf("Restaurace nebyla nalezena.\n");
                }
                break;
            }
            case 4: {
                system("cls");
                listRestaurants(restaurants);
                break;
            }
            case 5: {
                system("cls");
                sortRestaurantsAlphabetically(&restaurants);
                printf("Restaurace byly serazeny podle nazvu.\n");
                listRestaurants(restaurants);
                break;
            }
            case 6: {
                system("cls");
                sortByRating(&restaurants);
                printf("Restaurace byly serazeny podle hodnoceni.\n");
                listRestaurants(restaurants);
                break;
            }
            case 0: {
                system("cls");
                saveDatabase(&restaurants);
                printf("Konec programu.\n");
                break;
            }
            }
        }
        else {
            system("cls");
            printf("Neplatna volba.\n");
            while (getchar() != '\n');
        }
    } while (choice != 0); // Vypne program

    return 0;
}
