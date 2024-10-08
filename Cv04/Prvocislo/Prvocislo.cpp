// Prvocislo.cpp: Definuje vstupní bod pro aplikaci.
//

#include "Prvocislo.h"

using namespace std;

// Funkce pro kontrolu, zda je číslo prvočíslo
int jePrvocislo(int cislo) {
    if (cislo < 1 or cislo > 100) return -1;
    if (cislo == 1) return false;
    for (int i = 2; i * i <= cislo; i++) {
        if (cislo % i == 0) return false;
    }
    return true;
}


int main() {
    int a;
    printf("Zadej cislo od 1 do 100:");
    scanf("%d", &a);
    printf("Zadane cislo: %d\n", jePrvocislo(a));
    printf("\n");
    return 0;
}
