#include "velikost.h"
#include <math.h>

#pragma once

double velikost(double a[3]) {
	return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}