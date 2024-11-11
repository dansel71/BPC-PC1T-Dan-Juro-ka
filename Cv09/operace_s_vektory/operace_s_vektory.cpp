// operace_s_vektory.cpp: Definuje vstupní bod pro aplikaci.
//

#include "operace_s_vektory.h"
#include "VectorMath.h"
#include <stdio.h>
#include <math.h>


using namespace std;

struct vector3d
{
	double x;
	double y;
	double z;
};

int main()
{
	struct vector3d u;
	struct vector3d v;
	enum typOperace jakaOperace;
	printf ("Zadejte vektor u (hodnoty x, y, z oddelene carkou):");
	scanf_s("%lf, %lf, %lf", &u.x, &u.y, &u.z);
	printf("\nZadejte vektor v (hodnoty x, y, z oddelene carkou):");
	scanf_s("%lf, %lf, %lf", &v.x, &v.y, &v.z);
	printf("\nZadejte operaci (1 = soucet, 2 = vektorovySoucin): ");
	scanf_s("%lf", &jakaOperace);
	struct vector3d operace(struct vector3d u, struct vector3d v, typOperace jakaOperace);
	void tisk(struct vector3d u);
	return 0;
}
