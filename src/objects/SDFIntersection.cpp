#include "SDFIntersection.h"

SDFIntersection::SDFIntersection(Vector3 c, SDFObject *o1, SDFObject *o2, ObjectMaterial mat) {
    center = c;
    first_object = o1;
    second_object = o2;

    material = mat;
}

SDFIntersection::SDFIntersection() {
    center = (Vector3){0,0,0};
    first_object = new SDFObject();
    second_object = new SDFObject();
    material = ObjectMaterial();
}

double SDFIntersection::SDF(Vector3 P) {
    P = subtract(P, center);
    return std::max(first_object -> SDF(P), second_object -> SDF(P));
}