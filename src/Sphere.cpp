#include "Sphere.h"

Sphere::Sphere(Vector3 c, double r, Color clr, double spec, double refl) {
    center = c;
    radius = r;

    color = clr;
    specular = spec;
    reflective = refl;
}

Sphere::Sphere() {
    center = (Vector3){0,0,0};
    radius = 1;
    color = (Color){0,0,0};
    specular = 500;
    reflective = 0.0;
}