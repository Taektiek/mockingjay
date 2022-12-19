#ifndef SDFROTATE_H
#define SDFROTATE_H

#include "../SDFObject.h"
#include "../ObjectMaterial.h"
#include "../VectorMath.h"
#include<math.h>

class SDFRotate: public SDFObject {
    public:
        Vector3 center;
        
        SDFObject *object;

        double x_angle, y_angle, z_angle;

        double cosx;
        double sinx;

        double cosy;
        double siny;

        double cosz;
        double sinz;

        SDFRotate(Vector3 center, SDFObject *object, double x, double y, double z, ObjectMaterial material);
        SDFRotate();

        void initializeTransformations();

        virtual double SDF(Vector3 P);
};

#endif