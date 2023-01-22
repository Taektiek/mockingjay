#include "MeshPrimitives.h"

void generateBox(MeshObject* mesh, Vector3 center, Vector3 box) {
    Vector3 base = subtract(center, multiply(box, 0.5));

    int p000 = mesh -> AddVertex(base);
    int p001 = mesh -> AddVertex(add(base, {0, 0, box.z}));
    int p010 = mesh -> AddVertex(add(base, {0, box.y, 0}));
    int p011 = mesh -> AddVertex(add(base, {0, box.y, box.z}));
    int p100 = mesh -> AddVertex(add(base, {box.x, 0, 0}));
    int p101 = mesh -> AddVertex(add(base, {box.x, 0, box.z}));
    int p110 = mesh -> AddVertex(add(base, {box.x, box.y, 0}));
    int p111 = mesh -> AddVertex(add(base, box));

    mesh -> AddFace(p000, p100, p001);
    mesh -> AddFace(p100, p101, p001);
    mesh -> AddFace(p100, p110, p111);
    mesh -> AddFace(p100, p111, p101);
    mesh -> AddFace(p110, p010, p111);
    mesh -> AddFace(p010, p011, p111);
    mesh -> AddFace(p010, p001, p011);
    mesh -> AddFace(p010, p000, p001);
    mesh -> AddFace(p000, p100, p010);
    mesh -> AddFace(p100, p110, p010);
    mesh -> AddFace(p001, p101, p011);
    mesh -> AddFace(p101, p111, p011);
}