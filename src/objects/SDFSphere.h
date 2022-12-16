#ifndef SDFSPHERE_H
#define SDFSPHERE_H

#include "../SDFObject.h"
#include "../ObjectMaterial.h"
#include "../VectorMath.h"
#include<math.h>

class SDFSphere: public SDFObject {
    public:
        double radius;

        SDFSphere(Vector3 center, double radius, ObjectMaterial material);
        SDFSphere();

        virtual double SDF(Vector3 P);
};

#endif