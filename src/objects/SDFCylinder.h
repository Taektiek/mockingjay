#ifndef SDFCYLINDER_H
#define SDFCYLINDER_H

#include "../SDFObject.h"
#include "../ObjectMaterial.h"
#include "../VectorMath.h"
#include<math.h>

class SDFCylinder: public SDFObject {
    public:
        double height;
        double radius;

        SDFCylinder(Vector3 center, double height, double radius, ObjectMaterial material);
        SDFCylinder();

        virtual double SDF(Vector3 P);
};

#endif