#include "MeshPrimitives.h"

#define EPSILON 0.001

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

void generateSphere(MeshObject* mesh, Vector3 center, double radius, int rings, int detail) {
    int pTop = mesh -> AddVertex(add(center, {0, radius, 0}));
    int pBottom = mesh -> AddVertex(subtract(center, {0, radius, 0}));

    int currentVertex;

    for (int ring = 1; ring <= detail; ring ++) {
        double ringHeight = center.y + radius - ring*radius*2/rings;
        double currentRadius = sqrt(1-pow((1-(double)ring/rings)*2-1, 2))*radius;
        std::cout << currentRadius << std::endl;
        for (int i = 0; i < detail; i++) {
            currentVertex = mesh -> AddVertex({
                center.x+currentRadius*sin(2*M_PI*i/detail),
                ringHeight,
                center.z+currentRadius*cos(2*M_PI*i/detail)
            });
            if (ring == 1) {
                mesh -> AddFace(pTop, currentVertex - 1, currentVertex);
            } else if (i != 0) {
                mesh -> AddFace(currentVertex - detail, currentVertex - 1, currentVertex);
                mesh -> AddFace(currentVertex - detail, currentVertex - detail - 1, currentVertex - 1);
                if (ring == detail) {
                    mesh -> AddFace(pBottom, currentVertex - 1, currentVertex);
                }
            }
        }
    }
}

void generateCylinder(MeshObject* mesh, Vector3 center, double height, double radius, int detail) {
    int lastVertex = mesh -> vertices.size()-1;
    int currentVertex;

    for (int i = 0; i < detail; i++) { // TOP RING
        currentVertex = mesh -> AddVertex({
            center.x+radius*sin(2*M_PI*i/detail), 
            center.y+0.5*height, 
            center.z+radius*cos(2*M_PI*i/detail)
        });
        if (i > 1) {
            mesh -> AddFace(lastVertex+1, currentVertex - 1, currentVertex);
        }
    } 
    for (int i = 0; i < detail; i++) { // BOTTOM RING
        currentVertex = mesh -> AddVertex({
            center.x+radius*sin(2*M_PI*i/detail), 
            center.y-0.5*height, 
            center.z+radius*cos(2*M_PI*i/detail)
        });
        if (i != 0) {
            mesh -> AddFace(currentVertex, currentVertex - detail - 1, currentVertex - 1);
            mesh -> AddFace(currentVertex, currentVertex - detail, currentVertex - detail - 1);
            if (i != 1) {
                mesh -> AddFace(lastVertex+1+detail, currentVertex, currentVertex - 1);
            }
        }
    }
}