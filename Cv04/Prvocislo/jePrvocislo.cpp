#include "jePrvocislo.h"

#pragma once
// Funkce pro kontrolu, zda je èíslo prvoèíslo
int jePrvocislo(int cislo) {
    if (cislo < 1 or cislo > 100) return -1;
    if (cislo == 1) return false;
    for (int i = 2; i * i <= cislo; i++) {
        if (cislo % i == 0) return false;
    }
    return true;
}