#include "Sphere.h"

Sphere::Sphere(Vector3 c, double r, ObjectMaterial mat) {
    center = c;
    radius = r;

    material = mat;
}

Sphere::Sphere() {
    center = (Vector3){0,0,0};
    radius = 1;
    material = ObjectMaterial();
}