#ifndef SDFUNION_H
#define SDFUNION_H

#include "../SDFObject.h"
#include "../ObjectMaterial.h"
#include "../VectorMath.h"
#include<math.h>

class SDFUnion: public SDFObject {
    public:
        Vector3 center;
        
        SDFObject *first_object;
        SDFObject *second_object;

        SDFUnion(Vector3 center, SDFObject *first_object, SDFObject *second_object, ObjectMaterial material);
        SDFUnion();

        virtual double SDF(Vector3 P);
};

#endif