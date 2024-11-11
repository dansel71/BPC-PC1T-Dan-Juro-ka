#pragma once 


enum typOperace { soucet = 1, vektorovySoucin };

struct vector3d operace(struct vector3d u, struct vector3d v, enum
	typOperace typ);

void tisk(struct vector3d u);