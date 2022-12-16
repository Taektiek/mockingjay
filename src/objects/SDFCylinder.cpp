#include "SDFCylinder.h"

SDFCylinder::SDFCylinder(Vector3 c, double h, double r, ObjectMaterial mat) {
    center = c;
    height = h;
    radius = r;

    material = mat;
}

SDFCylinder::SDFCylinder() {
    center = (Vector3){0,0,0};
    height = 1;
    radius = 1;
    material = ObjectMaterial();
}

double SDFCylinder::SDF(Vector3 P) {
    P = subtract(P, center);
    Vector2 d = (Vector2){
        abs(magnitude((Vector2){P.x, P.z}))-radius,
        abs(P.y) - height
    };
    return std::min((double)std::max(d.x, d.y), 0.0) + magnitude(max(d, 0.0));
}