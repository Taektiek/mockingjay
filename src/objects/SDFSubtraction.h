#ifndef SDFSUBTRACTION_H
#define SDFSUBTRACTION_H

#include "../SDFObject.h"
#include "../ObjectMaterial.h"
#include "../VectorMath.h"
#include<math.h>

class SDFSubtraction: public SDFObject {
    public:
        Vector3 center;

        SDFObject *first_object;
        SDFObject *second_object;

        SDFSubtraction(Vector3 center, SDFObject *first_object, SDFObject *second_object, ObjectMaterial material);
        SDFSubtraction();

        virtual double SDF(Vector3 P);
};

#endif