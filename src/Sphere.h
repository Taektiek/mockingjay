#ifndef SPHERE_H
#define SPHERE_H

#include "raylib.h"

class Sphere {
    public:
        Vector3 center;
        float radius;

        //Material
        Color color;
        float specular;

        Sphere(Vector3 center, float radius, Color color, float specular);
        Sphere();
};

#endif