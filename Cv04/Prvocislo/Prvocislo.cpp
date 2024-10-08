// Prvocislo.cpp: Definuje vstupní bod pro aplikaci.
//

#include "Prvocislo.h"
#include "jePrvocislo.h"

using namespace std;

int main() {
    int a;
    printf("Zadej cislo od 1 do 100:");
    scanf("%d", &a);
    printf("Zadane cislo: %d\n", jePrvocislo(a));
    printf("\n");
    return 0;
}
