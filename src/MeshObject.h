#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include <vector>

#include "raylib.h"
#include "ObjectMaterial.h"
#include "VectorMath.h"
#include "MeshTools.h"

class MeshObject {
    public:
        ObjectMaterial material;

        std::vector<Face> faces;
        std::vector<Vertex> vertices;

        int AddVertex(Vector3 P);
        int AddFace(int v1, int v2, int v3);

        Vector3 FaceNormal(int f);

        MeshObject(ObjectMaterial material);
        MeshObject();
};

#endif