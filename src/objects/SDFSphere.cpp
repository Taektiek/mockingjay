#include "SDFSphere.h"

SDFSphere::SDFSphere(Vector3 c, double r, ObjectMaterial mat) {
    center = c;
    radius = r;

    material = mat;
}

SDFSphere::SDFSphere() {
    center = (Vector3){0,0,0};
    radius = 1;
    material = ObjectMaterial();
}

double SDFSphere::SDF(Vector3 P) {
    return magnitude(subtract(P, center)) - radius;
}