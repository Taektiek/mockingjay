#include "ObjectMaterial.h"

ObjectMaterial::ObjectMaterial(Color clr, double spec, double refl) {
    color = clr;
    specular = spec;
    reflective = refl;
}

ObjectMaterial::ObjectMaterial() {
    color = (Color){0,0,0,0};
    specular = 0;
    reflective = 0;
}