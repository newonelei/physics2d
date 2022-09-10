#pragma once

#ifndef _H_MATH_FLOAT_UTILS_
#define _H_MATH_FLOAT_UTILS_

#include <cfloat>
#include <cmath>
/*
The absolute tolerance test fails when the numbers being compared are large. The
relative tolerance test fails when the numbers being compared are small. Because
of this, we implemented a tolerance test with the CMP macro that combines the
two. The logic behind the CMP macro is described by Christer Ericson at
www.realtimecollisiondetection.net/pubs/Tolerances
*/
// Absolute tolerance comparison of x and y
#define ABSOLUTE(x, y) (fabs((x) - (y)) <= FLT_EPSILON)
// Relative tolerance comparison of x and y
#define RELATIVE(x, y) \
  (fabs((x) - (y)) <= FLT_EPSILON * fmaxf(fabs(x), fabs(y)))

#define CMP(x, y) \
  (fabsf((x) - (y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))
#endif