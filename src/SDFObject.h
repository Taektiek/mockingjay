#ifndef SDFOBJECT_H
#define SDFOBJECT_H

#include "raylib.h"
#include "ObjectMaterial.h"

class SDFObject {
    public:
        Vector3 center;

        ObjectMaterial material;

        SDFObject(Vector3 center, ObjectMaterial material);
        SDFObject();

        virtual double SDF(Vector3 P);
};

#endif