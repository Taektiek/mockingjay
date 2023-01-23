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

    mesh -> AddFace(p000, p010, p100); // FRONT
    mesh -> AddFace(p110, p100, p010); // FRONT
    mesh -> AddFace(p010, p011, p110); // TOP
    mesh -> AddFace(p110, p011, p111); // TOP
    mesh -> AddFace(p100, p110, p111); // RIGHT
    mesh -> AddFace(p100, p111, p101); // RIGHT
    mesh -> AddFace(p000, p100, p001); // BOTTOM
    mesh -> AddFace(p100, p101, p001); // BOTTOM
    mesh -> AddFace(p001, p101, p011); // BACK
    mesh -> AddFace(p111, p011, p101); // BACK
    mesh -> AddFace(p000, p011, p010); // LEFT
    mesh -> AddFace(p000, p001, p011); // LEFT
}