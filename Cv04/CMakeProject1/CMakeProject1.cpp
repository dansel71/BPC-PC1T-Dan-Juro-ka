// CMakeProject1.cpp: Definuje vstupní bod pro aplikaci.
//

#include "CMakeProject1.h"
#include "jePrestupny.h"

using namespace std;

int main()
{

    printf("1000 %d\n", jePrestupny(1000));
    printf("2000 %d\n", jePrestupny(2000));
    printf("2002 %d\n", jePrestupny(2002));
    printf("2012 %d\n", jePrestupny(2012));
    printf("2022 %d\n", jePrestupny(2022));
    printf("2200 %d\n", jePrestupny(2200));
	return 0;
}
