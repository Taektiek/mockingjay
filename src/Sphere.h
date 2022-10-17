#ifndef SPHERE_H
#define SPHERE_H

#include "raylib.h"

class Sphere {
    public:
        Vector3 center;
        double radius;

        //Material
        Color color;
        double specular;
        double reflective;

        Sphere(Vector3 center, double radius, Color color, double specular, double reflective);
        Sphere();
};

#endif