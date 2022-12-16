#include "SDFPlane.h"

SDFPlane::SDFPlane(Vector3 c, ObjectMaterial mat) {
    center = c;

    material = mat;
}

SDFPlane::SDFPlane() {
    center = (Vector3){0,0,0};

    material = ObjectMaterial();
}

double SDFPlane::SDF(Vector3 P) {
    return abs(P.y - center.y);
}