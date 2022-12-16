#ifndef SDFPLANE_H
#define SDFPLANE_H

#include "../SDFObject.h"
#include "../ObjectMaterial.h"
#include "../VectorMath.h"
#include<math.h>

class SDFPlane: public SDFObject {
    public:
        Vector3 center;
        SDFPlane(Vector3 center, ObjectMaterial material);
        SDFPlane();

        virtual double SDF(Vector3 P);
};

#endif