#ifndef SDFTORUS_H
#define SDFTORUS_H

#include "../SDFObject.h"
#include "../ObjectMaterial.h"
#include "../VectorMath.h"

class SDFTorus: public SDFObject {
    public:
        Vector3 center;
        Vector2 holes;

        SDFTorus(Vector3 center, Vector2 t, ObjectMaterial material);
        SDFTorus();

        virtual double SDF(Vector3 P);
};

#endif