#ifndef SPHERE_H
#define SPHERE_H

#include "raylib.h"
#include "ObjectMaterial.h"

class Sphere {
    public:
        Vector3 center;
        double radius;

        ObjectMaterial material;

        Sphere(Vector3 center, double radius, ObjectMaterial material);
        Sphere();
};

#endif