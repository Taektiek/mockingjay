#include "MeshObject.h"

int MeshObject::AddVertex(Vector3 P) {
    Vertex V = {P, {}};
    vertices.push_back(V);
    return vertices.size()-1;
}

int MeshObject::AddFace(int p1, int p2, int p3) {
    Vector3 P1 = vertices[p1].pos;
    Vector3 P2 = vertices[p2].pos;
    Vector3 P3 = vertices[p3].pos;

    Face F = {{p1, p2, p3}, normalize(cross(subtract(P1, P2), subtract(P1, P3)))};
    faces.push_back(F);
    int faceIndex = faces.size()-1;
    vertices[p1].faceIndices.push_back(faceIndex);
    vertices[p2].faceIndices.push_back(faceIndex);
    vertices[p3].faceIndices.push_back(faceIndex);
    return faceIndex;
}

Vector3 MeshObject::FaceNormal(int f) {
    return faces[f].normal;
}

MeshObject::MeshObject(ObjectMaterial mat) {
    material = mat;
}

MeshObject::MeshObject() {
    material = ObjectMaterial();
}