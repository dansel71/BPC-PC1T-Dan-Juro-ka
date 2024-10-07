// Prvocislo.cpp: Definuje vstupní bod pro aplikaci.
//

#include "Prvocislo.h"
#include "IsPrime.h"

using namespace std;

int main()
{
	int a;
	// Test fce
		for (int i = 0; i <= 100; i + 1) {
			if (IsPrime(i) == 1);
			printf("%d", i);
	}
	return 0;
}
