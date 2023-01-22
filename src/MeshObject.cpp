#include "MeshObject.h"

int MeshObject::AddVertex(Vector3 P) {
    Vertex V = {P, {}};
    vertices.push_back(V);
    return vertices.size()-1;
}

int MeshObject::AddFace(int p1, int p2, int p3) {
    Face F = {{p1, p2, p3}};
    faces.push_back(F);
    int faceIndex = faces.size()-1;
    vertices[p1].faceIndices.push_back(faceIndex);
    vertices[p2].faceIndices.push_back(faceIndex);
    vertices[p3].faceIndices.push_back(faceIndex);
    return faceIndex;
}

Vector3 MeshObject::FaceNormal(int f) {
    Vector3 p1 = vertices[faces[f].cornerIndices[0]].pos;
    Vector3 p2 = vertices[faces[f].cornerIndices[1]].pos;
    Vector3 p3 = vertices[faces[f].cornerIndices[2]].pos;
    return normalize(cross(subtract(p1, p2), subtract(p1, p3)));
}

MeshObject::MeshObject(ObjectMaterial mat) {
    material = mat;
}

MeshObject::MeshObject() {
    material = ObjectMaterial();
}