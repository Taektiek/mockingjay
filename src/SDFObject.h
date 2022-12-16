#ifndef SDFOBJECT_H
#define SDFOBJECT_H

#include "raylib.h"
#include "ObjectMaterial.h"

class SDFObject {
    public:
        ObjectMaterial material;

        SDFObject(ObjectMaterial material);
        SDFObject();

        virtual double SDF(Vector3 P);
};

#endif