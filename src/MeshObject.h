#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include "raylib.h"
#include "ObjectMaterial.h"
#include "VectorMath.h"

class MeshObject {
    public:
        ObjectMaterial material;

        Vector3 p1;
        Vector3 p2;
        Vector3 p3;

        Vector3 normal;

        MeshObject(Vector3 p1, Vector3 p2, Vector3 p3, ObjectMaterial material);
        MeshObject();
};

#endif