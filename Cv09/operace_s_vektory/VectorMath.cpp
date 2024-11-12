#include "VectorMath.h"
#include <math.h>
#include <stdio.h>

struct vector3d operace(struct vector3d u, struct vector3d v,
	enum typOperace typ) {
	switch (typ)
	{
	case soucet:
		u.x = u.x + v.x;
		u.y = u.y + v.y;
		u.z = u.z + v.z;
		break;
	case vektorovySoucin:
		double a;
		double b;
		a = u.x;
		b = u.y;
		u.x = u.y * v.z - v.y * u.z;
		u.y = u.z * v.x - v.z * a;
		u.z = a * v.y - v.x * b;
		break;
	default: break;
	}
	return u;
}

void tisk(struct vector3d w) {
	printf("Souradnice vysledneho vektoru w jsou: %lf, %lf, %lf\n", w.x, w.y, w.z);
	printf("Velikost vektoru |w| je: %lf\n", sqrt(pow(w.x,2) + pow(w.y,2) + pow(w.z,2)));
}

void rotuj(struct vector3d* u, enum typOsy osa) {
	int a;
	switch (osa) {
	case osaX:
		a = u->y;
		u->y = -u->z;
		u->z = a;
		break;
	case osaY:
		a = u->z;
		u->z = -u->x;
		u->x = a;
		break;
	case osaZ:
		a = u->x;
		u->x = -u->y;
		u->y = a;
		break;
	}
	printf("Souradnice vysledneho vektoru w jsou: %lf, %lf, %lf\n", u->x, u->y, u->z);



}
