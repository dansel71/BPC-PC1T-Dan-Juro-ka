// fce cpp

#include "22_restauracni_zarizeni.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkce.h"
#include "macros.h"




// Struktura pro hodnoceni restaurace
typedef struct Review {
    int review; // Bodove hodnoceni 1-5
    char comment[MAX_COMMENT_LEN]; // Slovni komentar
    struct Review* next; // Ukazatel na dalsi hodnoceni
} Review;

// Struktura pro restauraci
typedef struct Restaurant {
    char name[MAX_NAME_LEN]; // nazev restaurace
    Review* reviews; // Ukazatel na seznam hodnoceni
    struct Restaurant* next; // Ukazatel na dalsi restauraci
    struct menuItem* menu;
} Restaurant;


// vytvoreni nove restaurace
Restaurant* createRestaurant(char* name) {
    Restaurant* new_restaurant = (Restaurant*)malloc(sizeof(Restaurant));
    strcpy(new_restaurant->name, name);
    new_restaurant->reviews = NULL;
    new_restaurant->next = NULL;
    return new_restaurant;
}

// pridani restaurace do seznamu
void addRestaurant(Restaurant** head, char* name, int writeInfo) {
    Restaurant* current = *head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (writeInfo == 1) {
                printf("Restaurace %s jiz existuje.\n", name);
            }
            return;
        }
        current = current->next;
    }
    Restaurant* new_restaurant = createRestaurant(name);
    new_restaurant->next = *head;
    *head = new_restaurant;
    if (writeInfo == 1) {
        system("cls");
        printf("Restaurace %s byla pridana.\n", name);
    }
}

// najdi restauraci podle nazvu
Restaurant* findRestaurant(Restaurant* head, char* name) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// odstraneni restaurace ze seznamu
void deleteRestaurant(Restaurant** head, char* name) {
    Restaurant* current = *head;
    Restaurant* previous = NULL;

    while (current != NULL && strcmp(current->name, name) != 0) { // funkce, ktera vyplni diru v seznamu
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        system("cls");
        printf("Restaurace %s nebyla nalezena.\n", name);
        return;
    }

    if (previous == NULL) {
        *head = current->next;
    }
    else {
        previous->next = current->next;
    }

    // uvolneni pameti pro hodnoceni restaurace
    Review* review = current->reviews;
    while (review != NULL) {
        Review* temp = review;
        review = review->next;
        free(temp);
    }

    free(current);
    system("cls");
    printf("Restaurace %s byla odstranena.\n", name);
}


// vytvoreni noveho hodnoceni
Review* createReview(int rating, char* comment) {
    Review* new_review = (Review*)malloc(sizeof(Review));
    new_review->review = rating;
    strcpy(new_review->comment, comment);
    new_review->next = NULL;
    return new_review;
}

// pridani hodnoceni k restauraci
void addReview(Restaurant* restaurant, int rating, char* comment, int writeInfo) {
    if (restaurant == NULL) {
        system("cls");
        printf("Restaurace nebyla nalezena.\n");
        return;
    }

    Review* new_review = createReview(rating, comment);
    new_review->next = restaurant->reviews;
    restaurant->reviews = new_review;
    if (writeInfo == 1) {
        system("cls");
        printf("Hodnoceni %d s komentarem \"%s\" bylo pridano k restauraci %s.\n", rating, comment, restaurant->name);
    }
}

// vypsani vsech restauraci
void listRestaurants(Restaurant* head) {
    printf("Restaurace:\n\n");
    while (head != NULL) {
        printf("\t%s\n", head->name);
        Review* review = head->reviews;
        while (review != NULL) {
            printf("\t  Hodnoceni: %d\tKomentar: %s\n", review->review, review->comment);
            review = review->next;
        }
        head = head->next;
    }
}

//------------------------------------------------------------------

// funkce pro serazeni restauraci podle nazvu
void sortRestaurantsAlphabetically(Restaurant** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; // prazdny nebo 1prvkovy seznam, nic k razeni
    }

    int swapped;
    Restaurant* current;
    Restaurant* previous = NULL;
    Restaurant* lptr = NULL; // oznaczje konec jiz serazene casti seznamu

    do {
        swapped = 0;
        current = *head;
        previous = NULL;

        // prochazeni seznamu
        while (current->next != lptr) {
            // pokud je jmeno aktualniho prvku vetsi nez nasledujiciho, vymeni se
            if (strcmp(current->name, current->next->name) > 0) {
                // prehozeni ukazatele mezi current a current->next

                Restaurant* next = current->next;

                // pokud pprehazuje na zacatku seznamu
                if (previous == NULL) {
                    *head = next;  // aktualizujeme hlavu seznamu
                }
                else {
                    previous->next = next;  // nastavime predchozi uzel tak aby ukazoval na 'next'
                }

                current->next = next->next;  // aktualni prvek uz ukazuje na uzel po 'next'
                next->next = current;        // 'next' ukazuje na aktualni prvek

                swapped = 1; // prehazovani ukazatelu je hotove

                previous = next;// posuneme previous na 'next' (novy predek 'current')
            }
            else {
                // posuneme se dal, pokud nebyla vymena
                previous = current;
                current = current->next;
            }
        }
        lptr = current; // aktualizujeme lptr, posledni prvek je nyni na spravnem miste
    } while (swapped);
}



// Funkce pro serazeni restauraci dle hodnoceni
void sortByRating(Restaurant** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; // prazdny nebo 1prvkovy seznam, neni nic k razeni
    }

    int swapped;
    Restaurant* current;
    Restaurant* previous = NULL;
    Restaurant* lptr = NULL; // oznacuje konec uz serazene casti seznamu

    do {
        swapped = 0;
        current = *head;
        previous = NULL;
        int cur = 0;
        int nex = 0;

        // prochazeni seznamu
        while (current->next != lptr) {
            // Pokud je jmeno aktualniho prvku vetsi nez nasledujiciho, vymenime je
            if (current->reviews == NULL) {                    // pokud restaurace nema review tak je automatiocky
                //0 -> horsi jak nejmensi hodnocení coz je 1
                cur = 0;
            }
            else {
                cur = current->reviews->review;
            }
            if (current->next->reviews == NULL) {
                nex = 0;
            }
            else {
                nex = current->next->reviews->review;
            }

            if (cur < nex) {
                // prehodime ukazatele mezi current a current->next

                Restaurant* next = current->next;

                // pokud prehazujeme na zacatku seznamu
                if (previous == NULL) {
                    *head = next;  // Aktualizujeme hlavu seznamu
                }
                else {
                    previous->next = next;  // nastavime predchozi uzel tak, aby ukazoval na 'next'
                }

                current->next = next->next;  // Aktuální prvek nyní ukazuje na uzel po 'next'
                next->next = current;        // 'next' ukazuje na aktuální prvek

                swapped = 1; //prehazovani je dokonceno

                previous = next; // posuneme previous na 'next' (novy predek 'current')
            }
            else {
                // Posuneme se dal, pokud nebyla vymena
                previous = current;
                current = current->next;
            }
        }
        lptr = current; // Aktualizujeme lptr, posledni prvek je nyni na spravnem miste
    } while (swapped);
}

// Funkce pro ulozeni databaze
void saveDatabase(Restaurant** head) {
    if (head == NULL) {
        return; // prazdny seznam, nic k zapsani
    }
    Restaurant* restaurant;
    restaurant = *head;
    const char* CestaDatabaze = "..\\..\\..\\databaze.txt";
    FILE* databaze = fopen(CestaDatabaze, "w");
    while (restaurant != NULL) {
        Review* review = restaurant->reviews;
        review = restaurant->reviews; //prepne na komentare souvisejici s aktualni restauraci
        fprintf(databaze, "%s\n", restaurant->name);
        while (review != NULL) {
            fprintf(databaze, "\t%x", review->review);
            fprintf(databaze, "\t%s\n", review->comment);
            review = review->next;
        }
        restaurant = restaurant->next; //Ukazatel na dalsi restauraci
    }
    fclose(databaze);
    printf("Databaze ulozena.\n");
}

// Funkce pro nacteni databaze
void loadDatabase(Restaurant** head) {
    int pocetRestauraci = 0;
    int pocetHodnoceni = 0;
    const char* CestaVstup = "..\\..\\..\\databaze.txt";
    FILE* vstup;
    if (fopen_s(&vstup, CestaVstup, "r") != 0 || vstup == NULL) {
        perror("Error opening file");
        return;
    }
    long length;

    // prejdeme na konec souboru, abychom zjistili jeho velikost
    fseek(vstup, 0, SEEK_END);
    length = ftell(vstup);
    fseek(vstup, 0, SEEK_SET);  // vratime se zpet na zacatek souboru

    // alokovani pameti pro buffer
    char* databaze = (char*)malloc(length + 1);  // +1 pro nulovy terminator

    // cteni souboru do bufferu
    size_t bytesRead = fread(databaze, 1, length, vstup);
    databaze[bytesRead] = '\0';  // pridani nul. termin. na konec prectenych dat

    // Funkce pro ukladani
    // rozdeleni retezce na jednotlive radky
    char* line = strtok(databaze, "\n");
    while (line != NULL) {
        if (line[0] == '\t') {
            int rating = line[1] - 48; // Proè -48? cislice se z nejakeho duvodu prepisou na ASCII znak, kde 1 se prepise na 49...takto vratime 49 zpet na 1
            char comment[MAX_COMMENT_LEN];
            strcpy(comment, line + 3);
            addReview(*head, rating, comment, 0); // 0 na konci rika, ze funkce nebude tisknout info
            line = strtok(NULL, "\n");  // ziskani dalsiho radku
            pocetHodnoceni += 1;
        }
        else {
            addRestaurant(head, line, 0);  // pridani nazvu restaurace do seznamu,   0 na konci rika, ze funkce nebude tisknout info
            line = strtok(NULL, "\n");  // ziskani dalsiho radku
            pocetRestauraci += 1;
        }
    }
    system("cls");
    switch (pocetRestauraci)
    {
    case 1:
        printf("Byla nactena 1 restaurace a %d hodnoceni.\n", pocetHodnoceni);
        break;
    case 2:
        printf("Byly nacteny %d restaurace a %d hodnoceni.\n", pocetRestauraci, pocetHodnoceni);
        break;
    case 3:
        printf("Byly nacteny %d restaurace a %d hodnoceni.\n", pocetRestauraci, pocetHodnoceni);
        break;
    default:
        printf("Bylo nacteno %d restauraci a %d hodnoceni.\n", pocetRestauraci, pocetHodnoceni);
        break;
    }


    fclose(vstup);
    free(databaze);

}