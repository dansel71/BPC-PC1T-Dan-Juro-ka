// operace_s_vektory.cpp: Definuje vstupní bod pro aplikaci.
//

#include "operace_s_vektory.h"
#include "VectorMath.h"
#include <stdio.h>
#include <math.h>


using namespace std;

int main()
{
	struct vector3d u;
	struct vector3d v;
	enum typOperace jakaOperace;
	enum typOsy osa;
	printf("Zadejte vektor u (hodnoty x, y, z oddelene carkou):");
	scanf_s("%lf, %lf, %lf", &u.x, &u.y, &u.z);
	printf("\nZadejte vektor v (hodnoty x, y, z oddelene carkou):");
	scanf_s("%lf, %lf, %lf", &v.x, &v.y, &v.z);
	printf("\nZadejte operaci (1 = soucet, 2 = vektorovySoucin, 3 = rotace): ");
	scanf_s("%d", &jakaOperace);
	if (jakaOperace == 3) {
		printf("\nZadejte osu, podle ktere bude vektor rotovat (1 = x, 2 = y, 3 = z):");
		scanf_s("%d", &osa);
		rotuj(&u, osa);
	}
	else {// Píšu if, abych mohl oddelit operace soucet a soucin od operace rotuj protoze je nutne zadat hodnoty jinym zpusobem
		u = operace(u, v, jakaOperace);
		tisk(u);
		return 0;
	}
}
