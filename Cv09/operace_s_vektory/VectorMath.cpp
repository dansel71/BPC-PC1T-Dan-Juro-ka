#include "VectorMath.h"
#include <math.h>
#include <stdio.h>
enum typOperace { soucet = 1, vektorovySoucin };

struct vector3d
{
	double x;
	double y;
	double z;
};
struct vector3d operace(struct vector3d u, struct vector3d v,
	enum typOperace typ) {
	switch (typ)
	{
	case soucet: 
		u.x = u.x + v.x;
		u.y = u.y + v.y;
		u.y = u.z + v.z;
		break;
	case vektorovySoucin:
		u.x = u.x * v.x - v.x * u.x;
		u.y = u.y * v.y - v.y * u.y;
		u.z = u.z * v.z - v.z * u.z;
		break;
	}

}
void tisk(struct vector3d w) {
	printf("%lf, %lf, %lf", w.x, w.y, w.z);
	printf("%lf", sqrt(pow(w.x,2) + pow(w.y,2) + pow(w.z,2)));

}