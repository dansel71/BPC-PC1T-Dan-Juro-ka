
#include "22_restauracni_zarizeni.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkce.h"
#include "macros.h"


/*



// ------------------------------------------------------------------
typedef struct MenuItem {
    char name[MAX_NAME_LEN];
    double price;
    struct MenuItem* next;
} MenuItem;

MenuItem* createMenuItem(const char* name) {
    MenuItem* newItem = (MenuItem*)malloc(sizeof(MenuItem));
    strcpy(newItem->name, name);
    newItem->next = NULL;
    return newItem;
}



/*
void addRestaurant(Restaurant** head, char* name) {
    Restaurant* new_restaurant = createRestaurant(name);
    new_restaurant->next = *head;
    *head = new_restaurant;
    system("cls");
    printf("Restaurace %s byla pridana.\n", name);
}

Restaurant* createRestaurant(char* name) {
    Restaurant* new_restaurant = (Restaurant*)malloc(sizeof(Restaurant));
    strcpy(new_restaurant->name, name);
    new_restaurant->reviews = NULL;
    new_restaurant->next = NULL;
    return new_restaurant;
}




// add menu to restaurant
void addMenuItem(Restaurant* restaurant) {
    if (restaurant == NULL) {
        printf("Restaurace nebyla nalezena.\n");
        return;
    }

    struct Restaurant* restaurant;

    char itemName[MAX_NAME_LEN];
    double price;
    printf("Zadejte název jídla: ");
    scanf_s(" %[^\n]", itemName);
    printf("Zadejte cenu jídla: ");
    scanf_s("%lf", &price);

    MenuItem* newItem = createMenuItem(itemName);
    if (newItem == NULL) {
        return;
    }
    
    ;
   }
 
*/
//--------------------------------------------------------------------






int main() {
    Restaurant* restaurants = NULL;
    Restaurant* restaurant = NULL;  // Deklarace proměnné před switch

    int choice;
    char name[MAX_NAME_LEN];
    int rating;
    char comment[MAX_COMMENT_LEN];
   
    loadDatabase(&restaurants);
    sortRestaurantsAlphabetically(&restaurants); // Na začátku se restaurace pokaždé seřadí, aby se zabránilo převrácení seznamu vzůru nohama

    do {
        
        printf("\n1. Pridat restauraci\n");
        printf("2. Odstranit restauraci\n");
        printf("3. Pridat hodnoceni\n");
        printf("4. Vypsat restaurace\n");
        printf("5. Radit restaurace podle nazvu\n");
        printf("6. Radit podle hodnoceni\n");
        printf("0. Ulozit a ukoncit\n\n");
        printf("Vyberte moznost: ");
        if ((scanf("%d", &choice)) == 1) { // Skenuje hodnotu choice a zároveň filtruje písmena
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
                /*    if (strcmp(&restaurants->name[0], name) == 0) { // Porovnání řetězců
                        system("cls");
                        printf("Restaurace jiz existuje.\n");
                        break;
                    }*/
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
                //sortRestaurants(restaurants, count);
                printf("Restaurace byly serazeny podle nazvu.\n");
                listRestaurants(restaurants);
                break;
            }
            case 6: {
                system("cls");
                sortByRating(&restaurants);
                //sortRestaurants(restaurants, count);
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
