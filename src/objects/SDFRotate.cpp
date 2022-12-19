#include "SDFRotate.h"

SDFRotate::SDFRotate(Vector3 c, SDFObject *o, double x, double y, double z, ObjectMaterial mat) {
    center = c;
    object = o;

    x_angle = x;
    y_angle = y;
    z_angle = z;

    initializeTransformations();

    material = mat;
}

double radian(double n) {
    return n * (180/PI);
}

void SDFRotate::initializeTransformations() {
    double x_rad = radian(x_angle);
    double y_rad = radian(y_angle);
    double z_rad = radian(z_angle);

    cosx = cos(radian(x_angle));
    sinx = sin(radian(x_angle));

    cosy = cos(radian(y_angle));
    siny = sin(radian(y_angle));

    cosz = cos(radian(z_angle));
    sinz = sin(radian(z_angle));

}

SDFRotate::SDFRotate() {
    center = (Vector3){0,0,0};
    object = new SDFObject();

    x_angle = 0;
    y_angle = 0;
    z_angle = 0;

    material = ObjectMaterial();
}

double SDFRotate::SDF(Vector3 P) {
    P = subtract(P, center);

    P = (Vector3){
        P.x,
        P.y * cosx - P.z * sinx,
        P.y * sinx + P.z * cosx,
    }; // X rotation
    P = (Vector3){
        P.x * cosy + P.z * siny,
        P.y,
        - P.x * siny + P.z * cosy,
    }; // Y rotation
    P = (Vector3){
        P.x * cosz - P.y * sinz,
        P.x * sinz + P.y * cosz,
        P.z,
    }; // Z rotation
    return object -> SDF(P);
}