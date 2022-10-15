#ifndef VECTORMATH_H
#define VECTORMATH_H

#include "raylib.h"

double dot(Vector3 v1, Vector3 v2);
Vector3 add(Vector3 v1, Vector3 v2);
Vector3 subtract(Vector3 v1, Vector3 v2);
Vector3 multiply(Vector3 v, double n);
double magnitude(Vector3 v);

#endif