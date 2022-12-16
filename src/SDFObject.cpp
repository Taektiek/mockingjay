#include "SDFObject.h"
#include "VectorMath.h"

SDFObject::SDFObject(ObjectMaterial mat) {
    material = mat;
}

SDFObject::SDFObject() {
    material = ObjectMaterial();
}

double SDFObject::SDF(Vector3 P) {
    return 1;
}