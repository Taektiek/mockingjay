#ifndef VECTORMATH_H
#define VECTORMATH_H

#include "raylib.h"

#include <iostream>

double dot(Vector3 v1, Vector3 v2);
Vector3 add(Vector3 v1, Vector3 v2);
Color add(Color c1, Color c2);
Vector3 subtract(Vector3 v1, Vector3 v2);
Vector2 subtract(Vector2 v1, Vector2 v2);
Vector3 multiply(Vector3 v, double n);
Color multiply(Color c, double n);
double magnitude(Vector3 v);
double magnitude(Vector2 v);
Vector3 normalize(Vector3 v);
Vector3 abs(Vector3 v);
Vector3 max(Vector3 v, double n);
Vector2 max(Vector2 v, double n);
Vector3 mod(Vector3 v, double n);
Vector3 cross(Vector3 v1, Vector3 v2);

void printVector(Vector3 v);
void printColor(Color c);

#endif