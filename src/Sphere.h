#ifndef SPHERE_H
#define SPHERE_H

#include "raylib.h"

class Sphere {
    public:
        Vector3 center;
        float radius;
        Color color;

        Sphere(Vector3 center, float radius, Color color);
        Sphere();
};

#endif