#pragma once 

struct vector3d
{
	double x;
	double y;
	double z;
};

enum typOperace { soucet = 1, vektorovySoucin, rotace };
enum typOsy { osaX = 1, osaY, osaZ };

struct vector3d operace(struct vector3d u, struct vector3d v, enum	typOperace typ);

void tisk(struct vector3d u);

void rotuj(struct vector3d* u, enum typOsy osa);
