// fce cpp

#include "22_restauracni_zarizeni.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkce.h"
#include "macros.h"

// Struktura pro hodnocení restaurace
typedef struct Review {
    int review; // Bodové hodnocení (napø. 1-5)
    char comment[MAX_COMMENT_LEN]; // Slovní komentáø
    struct Review* next; // Ukazatel na další hodnocení
} Review;

// Struktura pro restauraci
typedef struct Restaurant {
    char name[MAX_NAME_LEN]; // Název restaurace
    Review* reviews; // Ukazatel na seznam hodnocení
    struct Restaurant* next; // Ukazatel na další restauraci
    struct menuItem* menu;
} Restaurant;


// Vytvoøení nové restaurace
Restaurant* createRestaurant(char* name) {
    Restaurant* new_restaurant = (Restaurant*)malloc(sizeof(Restaurant));
    strcpy(new_restaurant->name, name);
    new_restaurant->reviews = NULL;
    new_restaurant->next = NULL;
    return new_restaurant;
}

// Pøidání restaurace do seznamu
void addRestaurant(Restaurant** head, char* name, int writeInfo) {
    Restaurant* current = *head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (writeInfo == 1) {
                printf("Restaurace %s ji existuje\n", name);
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

// Najdi restauraci podle názvu
Restaurant* findRestaurant(Restaurant* head, char* name) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// Odstranìní restaurace ze seznamu
void deleteRestaurant(Restaurant** head, char* name) {
    Restaurant* current = *head;
    Restaurant* previous = NULL;

    while (current != NULL && strcmp(current->name, name) != 0) { // Funkce, která vyplní "díru" v seznamu
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

    // Uvolnìní pamìti pro hodnocení restaurace
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


// Vytvoøení nového hodnocení
Review* createReview(int rating, char* comment) {
    Review* new_review = (Review*)malloc(sizeof(Review));
    new_review->review = rating;
    strcpy(new_review->comment, comment);
    new_review->next = NULL;
    return new_review;
}

// Pøidání hodnocení k restauraci
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

// Vypsání všech restaurací
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

// Funkce pro seøazení restaurací podle názvu
void sortRestaurantsAlphabetically(Restaurant** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; // Prázdnı nebo jedno-prvkovı seznam, nic k øazení
    }

    int swapped;
    Restaurant* current;
    Restaurant* previous = NULL;
    Restaurant* lptr = NULL; // Oznaèuje konec ji seøazené èásti seznamu

    do {
        swapped = 0;
        current = *head;
        previous = NULL;

        // Procházení seznamu
        while (current->next != lptr) {
            // Pokud je jméno aktuálního prvku vìtší ne následujícího, vymìníme je
            if (strcmp(current->name, current->next->name) > 0) {
                // Pøehodíme ukazatele mezi current a current->next

                Restaurant* next = current->next;

                // Pokud pøehazujeme na zaèátku seznamu
                if (previous == NULL) {
                    *head = next;  // Aktualizujeme hlavu seznamu
                }
                else {
                    previous->next = next;  // Nastavíme pøedchozí uzel tak, aby ukazoval na 'next'
                }

                current->next = next->next;  // Aktuální prvek nyní ukazuje na uzel po 'next'
                next->next = current;        // 'next' ukazuje na aktuální prvek

                // Pøehazování ukazatelù je hotové
                swapped = 1;

                // Posuneme previous na 'next' (novı pøedek 'current')
                previous = next;
            }
            else {
                // Posuneme se dál, pokud nebyla vımìna
                previous = current;
                current = current->next;
            }
        }
        lptr = current; // Aktualizujeme lptr, poslední prvek je nyní na správném místì
    } while (swapped);
}



// Funkce pro seøazení restaurací podle hodnocení
void sortByRating(Restaurant** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; // Prázdnı nebo jedno-prvkovı seznam, nic k øazení
    }

    int swapped;
    Restaurant* current;
    Restaurant* previous = NULL;
    Restaurant* lptr = NULL; // Oznaèuje konec ji seøazené èásti seznamu

    do {
        swapped = 0;
        current = *head;
        previous = NULL;
        int cur = 0;
        int nex = 0;

        // Procházení seznamu
        while (current->next != lptr) {
            // Pokud je jméno aktuálního prvku vìtší ne následujícího, vymìníme je
            if (current->reviews == NULL) {                    // Pokud restaurace nemá rewie tak je automatiocky
                                                                //0 -> hroší jak nejmepší hodnocení co je 1
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
                // Pøehodíme ukazatele mezi current a current->next

                Restaurant* next = current->next;

                // Pokud pøehazujeme na zaèátku seznamu
                if (previous == NULL) {
                    *head = next;  // Aktualizujeme hlavu seznamu
                }
                else {
                    previous->next = next;  // Nastavíme pøedchozí uzel tak, aby ukazoval na 'next'
                }

                current->next = next->next;  // Aktuální prvek nyní ukazuje na uzel po 'next'
                next->next = current;        // 'next' ukazuje na aktuální prvek

                // Pøehazování ukazatelù je hotové
                swapped = 1;

                // Posuneme previous na 'next' (novı pøedek 'current')
                previous = next;
            }
            else {
                // Posuneme se dál, pokud nebyla vımìna
                previous = current;
                current = current->next;
            }
        }
        lptr = current; // Aktualizujeme lptr, poslední prvek je nyní na správném místì
    } while (swapped);
}

// Funkce pro uloení databáze
void saveDatabase(Restaurant** head) {
    if (head == NULL) {
        return; // Prázdnı seznam, nic k zapsání
    }
    Restaurant* restaurant;
    restaurant = *head;
    const char* CestaDatabaze = "..\\..\\..\\databaze.txt";
    FILE* databaze = fopen(CestaDatabaze, "w");
    while (restaurant != NULL) {
        Review* review = restaurant->reviews;
        review = restaurant->reviews; //Pøepne na komentáøe související s aktuální restaurací
        fprintf(databaze, "%s\n", restaurant->name);
        while (review != NULL) {
            fprintf(databaze, "\t%x", review->review);
            fprintf(databaze, "\t%s\n", review->comment);
            review = review->next;
        }
        restaurant = restaurant->next; //Ukazatel na další restauraci
    }
    fclose(databaze);
    printf("Databaze ulozena.\n");
}

// Funkce pro neètení databáze
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

    // Pøejdeme na konec souboru, abychom zjistili jeho velikost
    fseek(vstup, 0, SEEK_END);
    length = ftell(vstup);
    fseek(vstup, 0, SEEK_SET);  // Vrame se zpìt na zaèátek souboru

    if (length != 0) {
        // Alokování pamìti pro buffer
        char* databaze = (char*)malloc(length + 1);  // +1 pro nulovı terminátor

        // Ètení souboru do bufferu
        size_t bytesRead = fread(databaze, 1, length, vstup);
        databaze[bytesRead] = '\0';  // Pøidání nulového terminátoru na konec pøeètenıch dat

        // Funkce pro ukládání
        // Rozdìlení øetìzce na jednotlivé øádky
        char* line = strtok(databaze, "\n");
        while (line != NULL) {
            if (line[0] == '\t') {
                int rating = line[1] - 48; // Proè -48? èíslice se pøepíšou na ASCII znak, kde 1 se pøepíše na 49...takto vrátíme 49 zpìt na 1
                char comment[MAX_COMMENT_LEN];
                strcpy(comment, line + 3);
                addReview(*head, rating, comment, 0); // 0 na konci øíká, e funkce nebude tisknout info
                line = strtok(NULL, "\n");  // Získání dalšího øádku
                pocetHodnoceni += 1;
            }
            else {
                addRestaurant(head, line, 0);  // Pøidání názvu restaurace do seznamu,   0 na konci øíká, e funkce nebude tisknout info
                line = strtok(NULL, "\n");  // Získání dalšího øádku
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
        free(databaze);
    }
    fclose(vstup);
}