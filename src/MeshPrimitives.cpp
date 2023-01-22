#include "MeshPrimitives.h"

#define EPSILON 0.001

void generateBox(MeshObject* mesh, Vector3 center, Vector3 box) {
    Vector3 base = subtract(center, multiply(box, 0.5));

    int p000 = mesh -> AddVertex(base);
    int p001 = mesh -> AddVertex(add(base, {EPSILON, EPSILON, box.z}));
    int p010 = mesh -> AddVertex(add(base, {0, box.y, 0}));
    int p011 = mesh -> AddVertex(add(base, {EPSILON, box.y + EPSILON, box.z}));
    int p100 = mesh -> AddVertex(add(base, {box.x, 0, 0}));
    int p101 = mesh -> AddVertex(add(base, {box.x + EPSILON, EPSILON, box.z}));
    int p110 = mesh -> AddVertex(add(base, {box.x, box.y, 0}));
    int p111 = mesh -> AddVertex(add(base, {box.x + EPSILON, box.y + EPSILON, box.z}));

    mesh -> AddFace(p000, p010, p100);
    // mesh -> AddFace(p110, p100, p010);
    mesh -> AddFace(p010, p110, p011);
}