// fce cpp

#include "22_restauracni_zarizeni.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkce.h"
#include "macros.h"

// Struktura pro hodnocen� restaurace
typedef struct Review {
    int review; // Bodov� hodnocen� (nap�. 1-5)
    char comment[MAX_COMMENT_LEN]; // Slovn� koment��
    struct Review* next; // Ukazatel na dal�� hodnocen�
} Review;

// Struktura pro restauraci
typedef struct Restaurant {
    char name[MAX_NAME_LEN]; // N�zev restaurace
    Review* reviews; // Ukazatel na seznam hodnocen�
    struct Restaurant* next; // Ukazatel na dal�� restauraci
    struct menuItem* menu;
} Restaurant;


// Vytvo�en� nov� restaurace
Restaurant* createRestaurant(char* name) {
    Restaurant* new_restaurant = (Restaurant*)malloc(sizeof(Restaurant));
    strcpy(new_restaurant->name, name);
    new_restaurant->reviews = NULL;
    new_restaurant->next = NULL;
    return new_restaurant;
}

// P�id�n� restaurace do seznamu
void addRestaurant(Restaurant** head, char* name, int writeInfo) {
    Restaurant* current = *head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (writeInfo == 1) {
                printf("Restaurace %s ji� existuje\n", name);
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

// Najdi restauraci podle n�zvu
Restaurant* findRestaurant(Restaurant* head, char* name) {
    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// Odstran�n� restaurace ze seznamu
void deleteRestaurant(Restaurant** head, char* name) {
    Restaurant* current = *head;
    Restaurant* previous = NULL;

    while (current != NULL && strcmp(current->name, name) != 0) { // Funkce, kter� vypln� "d�ru" v seznamu
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

    // Uvoln�n� pam�ti pro hodnocen� restaurace
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


// Vytvo�en� nov�ho hodnocen�
Review* createReview(int rating, char* comment) {
    Review* new_review = (Review*)malloc(sizeof(Review));
    new_review->review = rating;
    strcpy(new_review->comment, comment);
    new_review->next = NULL;
    return new_review;
}

// P�id�n� hodnocen� k restauraci
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

// Vyps�n� v�ech restaurac�
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

// Funkce pro se�azen� restaurac� podle n�zvu
void sortRestaurantsAlphabetically(Restaurant** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; // Pr�zdn� nebo jedno-prvkov� seznam, nic k �azen�
    }

    int swapped;
    Restaurant* current;
    Restaurant* previous = NULL;
    Restaurant* lptr = NULL; // Ozna�uje konec ji� se�azen� ��sti seznamu

    do {
        swapped = 0;
        current = *head;
        previous = NULL;

        // Proch�zen� seznamu
        while (current->next != lptr) {
            // Pokud je jm�no aktu�ln�ho prvku v�t�� ne� n�sleduj�c�ho, vym�n�me je
            if (strcmp(current->name, current->next->name) > 0) {
                // P�ehod�me ukazatele mezi current a current->next

                Restaurant* next = current->next;

                // Pokud p�ehazujeme na za��tku seznamu
                if (previous == NULL) {
                    *head = next;  // Aktualizujeme hlavu seznamu
                }
                else {
                    previous->next = next;  // Nastav�me p�edchoz� uzel tak, aby ukazoval na 'next'
                }

                current->next = next->next;  // Aktu�ln� prvek nyn� ukazuje na uzel po 'next'
                next->next = current;        // 'next' ukazuje na aktu�ln� prvek

                // P�ehazov�n� ukazatel� je hotov�
                swapped = 1;

                // Posuneme previous na 'next' (nov� p�edek 'current')
                previous = next;
            }
            else {
                // Posuneme se d�l, pokud nebyla v�m�na
                previous = current;
                current = current->next;
            }
        }
        lptr = current; // Aktualizujeme lptr, posledn� prvek je nyn� na spr�vn�m m�st�
    } while (swapped);
}



// Funkce pro se�azen� restaurac� podle hodnocen�
void sortByRating(Restaurant** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return; // Pr�zdn� nebo jedno-prvkov� seznam, nic k �azen�
    }

    int swapped;
    Restaurant* current;
    Restaurant* previous = NULL;
    Restaurant* lptr = NULL; // Ozna�uje konec ji� se�azen� ��sti seznamu

    do {
        swapped = 0;
        current = *head;
        previous = NULL;
        int cur = 0;
        int nex = 0;

        // Proch�zen� seznamu
        while (current->next != lptr) {
            // Pokud je jm�no aktu�ln�ho prvku v�t�� ne� n�sleduj�c�ho, vym�n�me je
            if (current->reviews == NULL) {                    // Pokud restaurace nem� rewie tak je automatiocky
                                                                //0 -> hro�� jak nejmep�� hodnocen� co� je 1
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
                // P�ehod�me ukazatele mezi current a current->next

                Restaurant* next = current->next;

                // Pokud p�ehazujeme na za��tku seznamu
                if (previous == NULL) {
                    *head = next;  // Aktualizujeme hlavu seznamu
                }
                else {
                    previous->next = next;  // Nastav�me p�edchoz� uzel tak, aby ukazoval na 'next'
                }

                current->next = next->next;  // Aktu�ln� prvek nyn� ukazuje na uzel po 'next'
                next->next = current;        // 'next' ukazuje na aktu�ln� prvek

                // P�ehazov�n� ukazatel� je hotov�
                swapped = 1;

                // Posuneme previous na 'next' (nov� p�edek 'current')
                previous = next;
            }
            else {
                // Posuneme se d�l, pokud nebyla v�m�na
                previous = current;
                current = current->next;
            }
        }
        lptr = current; // Aktualizujeme lptr, posledn� prvek je nyn� na spr�vn�m m�st�
    } while (swapped);
}

// Funkce pro ulo�en� datab�ze
void saveDatabase(Restaurant** head) {
    if (head == NULL) {
        return; // Pr�zdn� seznam, nic k zaps�n�
    }
    Restaurant* restaurant;
    restaurant = *head;
    const char* CestaDatabaze = "..\\..\\..\\databaze.txt";
    FILE* databaze = fopen(CestaDatabaze, "w");
    while (restaurant != NULL) {
        Review* review = restaurant->reviews;
        review = restaurant->reviews; //P�epne na koment��e souvisej�c� s aktu�ln� restaurac�
        fprintf(databaze, "%s\n", restaurant->name);
        while (review != NULL) {
            fprintf(databaze, "\t%x", review->review);
            fprintf(databaze, "\t%s\n", review->comment);
            review = review->next;
        }
        restaurant = restaurant->next; //Ukazatel na dal�� restauraci
    }
    fclose(databaze);
    printf("Databaze ulozena.\n");
}

// Funkce pro ne�ten� datab�ze
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

    // P�ejdeme na konec souboru, abychom zjistili jeho velikost
    fseek(vstup, 0, SEEK_END);
    length = ftell(vstup);
    fseek(vstup, 0, SEEK_SET);  // Vra�me se zp�t na za��tek souboru

    if (length != 0) {
        // Alokov�n� pam�ti pro buffer
        char* databaze = (char*)malloc(length + 1);  // +1 pro nulov� termin�tor

        // �ten� souboru do bufferu
        size_t bytesRead = fread(databaze, 1, length, vstup);
        databaze[bytesRead] = '\0';  // P�id�n� nulov�ho termin�toru na konec p�e�ten�ch dat

        // Funkce pro ukl�d�n�
        // Rozd�len� �et�zce na jednotliv� ��dky
        char* line = strtok(databaze, "\n");
        while (line != NULL) {
            if (line[0] == '\t') {
                int rating = line[1] - 48; // Pro� -48? ��slice se p�ep�ou na ASCII znak, kde 1 se p�ep�e na 49...takto vr�t�me 49 zp�t na 1
                char comment[MAX_COMMENT_LEN];
                strcpy(comment, line + 3);
                addReview(*head, rating, comment, 0); // 0 na konci ��k�, �e funkce nebude tisknout info
                line = strtok(NULL, "\n");  // Z�sk�n� dal��ho ��dku
                pocetHodnoceni += 1;
            }
            else {
                addRestaurant(head, line, 0);  // P�id�n� n�zvu restaurace do seznamu,   0 na konci ��k�, �e funkce nebude tisknout info
                line = strtok(NULL, "\n");  // Z�sk�n� dal��ho ��dku
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