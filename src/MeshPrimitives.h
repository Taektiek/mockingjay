#ifndef MESHPRIMITIVES_H
#define MESHPRIMITIVES_H

#include "MeshObject.h"
#include "VectorMath.h"
#include "raylib.h"

#include <math.h>

void generateBox(MeshObject* mesh, Vector3 center, Vector3 box);
void generateSphere(MeshObject* mesh, Vector3 center, double radius, int rings, int detail);

#endif