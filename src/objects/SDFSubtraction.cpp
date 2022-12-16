#include "SDFSubtraction.h"

SDFSubtraction::SDFSubtraction(Vector3 c, SDFObject *o1, SDFObject *o2, ObjectMaterial mat) {
    center = c;
    first_object = o1;
    second_object = o2;

    material = mat;
}

SDFSubtraction::SDFSubtraction() {
    center = (Vector3){0,0,0};
    first_object = new SDFObject();
    second_object = new SDFObject();
    material = ObjectMaterial();
}

double SDFSubtraction::SDF(Vector3 P) {
    P = subtract(P, center);
    return std::max(first_object -> SDF(P), -1 * second_object -> SDF(P));
}