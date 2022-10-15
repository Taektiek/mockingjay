#include "VectorMath.h"
#include <math.h>

double dot(Vector3 v1, Vector3 v2) { // Returns the dot product of two vectors
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}

Vector3 add(Vector3 v1, Vector3 v2) { // Returns the sum of two vectors
    return (Vector3){v1.x+v2.x,v1.y+v2.y+v1.z+v2.z};
}

Vector3 subtract(Vector3 v1, Vector3 v2) { // Returns the difference of two vectors
    return (Vector3){v1.x-v2.x,v1.y-v2.y,v1.z-v2.z};
}

Vector3 multiply(Vector3 v, double n) {
    return (Vector3){v.x*n,v.y*n,v.z*n};
}

double magnitude(Vector3 v) {
    return sqrt(v.x*v.x+v.y*v.y+v.z+v.z);
}