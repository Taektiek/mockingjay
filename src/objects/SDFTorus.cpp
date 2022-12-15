#include "SDFTorus.h"

SDFTorus::SDFTorus(Vector3 c, Vector2 t, ObjectMaterial mat) {
    center = c;
    holes = t;

    material = mat;
}

SDFTorus::SDFTorus() {
    center = (Vector3){0,0,0};
    holes = {1, 1};
    material = ObjectMaterial();
}

double SDFTorus::SDF(Vector3 P) {
    P = subtract(P, center);
    Vector2 q = (Vector2){magnitude((Vector2){P.x,P.z})-holes.x,P.y};
    return magnitude(q)-holes.y;
}