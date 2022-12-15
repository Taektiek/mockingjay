#include "SDFObject.h"
#include "VectorMath.h"

SDFObject::SDFObject(Vector3 c, ObjectMaterial mat) {
    center = c;

    material = mat;
}

SDFObject::SDFObject() {
    center = (Vector3){0,0,0};
    material = ObjectMaterial();
}

double SDFObject::SDF(Vector3 P) {
    P = subtract(P, center);
    Vector2 t = (Vector2){1.5, 1};
    Vector2 q = (Vector2){magnitude((Vector2){P.x,P.z})-t.x,P.y};
    return magnitude(q)-t.y;
}