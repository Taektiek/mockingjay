#ifndef SDFINTERSECTION_H
#define SDFINTERSECTION_H

#include "../SDFObject.h"
#include "../ObjectMaterial.h"
#include "../VectorMath.h"
#include<math.h>

class SDFIntersection: public SDFObject {
    public:
        Vector3 center;

        SDFObject *first_object;
        SDFObject *second_object;

        SDFIntersection(Vector3 center, SDFObject *first_object, SDFObject *second_object, ObjectMaterial material);
        SDFIntersection();

        virtual double SDF(Vector3 P);
};

#endif