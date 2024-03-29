#include "VectorMath.h"
#include <math.h>

double dot(Vector3 v1, Vector3 v2) { // Returns the dot product of two vectors
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}

Vector3 add(Vector3 v1, Vector3 v2) { // Returns the sum of two vectors
    return (Vector3){v1.x+v2.x,v1.y+v2.y,v1.z+v2.z};
}

Color add(Color c1, Color c2) { // Returns the sum of two colors
    return (Color){std::min(c1.r + c2.r, 255), std::min(c1.g + c2.g, 255), std::min(c1.b + c2.b, 255), std::min(c1.a + c2.a, 255)};
}

Vector3 subtract(Vector3 v1, Vector3 v2) { // Returns the difference of two vectors
    return (Vector3){v1.x-v2.x,v1.y-v2.y,v1.z-v2.z};
}

Vector3 multiply(Vector3 v, double n) {
    return (Vector3){v.x*n,v.y*n,v.z*n};
}

Color multiply(Color c, double n) {
    return (Color){std::min(c.r*n, 255.0), std::min(c.g*n, 255.0), std::min(c.b*n, 255.0), c.a};
}

double magnitude(Vector3 v) {
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

double magnitude(Vector2 v) {
    return sqrt(v.x*v.x+v.y*v.y);
}

Vector3 normalize(Vector3 v) {
    return multiply(v, pow(magnitude(v),-1));
}

Vector3 abs(Vector3 v) {
    return (Vector3){abs(v.x),abs(v.y),abs(v.z)};
}

Vector3 max(Vector3 v, double n) {
    return (Vector3){std::max((double)v.x, n), std::max((double)v.y, n), std::max((double)v.z, n)};
}

Vector2 max(Vector2 v, double n) {
    return (Vector2){std::max((double)v.x, n), std::max((double)v.y, n)};
}

Vector3 mod(Vector3 v, double n) {
    return (Vector3){std::fmod(v.x, n), std::fmod(v.y, n), std::fmod(v.z, n)};
}

void printVector(Vector3 v) {
    std::cout << v.x << " " << v.y << " " << v.z << std::endl;
}

void printColor(Color c) {
    std::cout << c.r << " " << c.g << " " << c.b << std::endl;
}