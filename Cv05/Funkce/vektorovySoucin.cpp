#include "vektorovySoucin.h"

#pragma once

void vektorovySoucin(double a[3], double b[3], double d[3]) {
	d[0] = a[1] * a[2] - b[1] * a[2];
	d[1] = a[2] * a[0] - b[2] * a[0];
	d[2] = a[0] * a[1] - b[0] * a[1];
}