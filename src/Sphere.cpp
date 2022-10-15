#include "Sphere.h"

Sphere::Sphere(Vector3 c, float r, Color clr) {
    center = c;
    radius = r;

    color = clr;
}

Sphere::Sphere() {
    center = (Vector3){0,0,0};
    radius = 1;
    color = (Color){0,0,0};
}