#ifndef SDFBOX_H
#define SDFBOX_H

#include "../SDFObject.h"
#include "../ObjectMaterial.h"
#include "../VectorMath.h"

class SDFBox: public SDFObject {
    public:
        Vector3 center;
        Vector3 box;

        SDFBox(Vector3 center, Vector3 box, ObjectMaterial material);
        SDFBox();

        virtual double SDF(Vector3 P);
};

#endif