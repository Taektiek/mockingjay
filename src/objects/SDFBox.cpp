#include "SDFBox.h"

SDFBox::SDFBox(Vector3 c, Vector3 b, ObjectMaterial mat) {
    center = c;
    box = b;

    material = mat;
}

SDFBox::SDFBox() {
    center = (Vector3){0,0,0};
    box = (Vector3){1,1,1};
    material = ObjectMaterial();
}

double SDFBox::SDF(Vector3 P) {
    P = subtract(P, center);
    Vector3 b = multiply(box, 0.5);
    Vector3 q = subtract(abs(P), b);
    return magnitude(max(q,0.0)) + std::min((double)std::max(q.x,std::max(q.y,q.z)),0.0);
}