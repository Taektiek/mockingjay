#include "MeshObject.h"

MeshObject::MeshObject(Vector3 point1, Vector3 point2, Vector3 point3, ObjectMaterial mat) {
    material = mat;

    p1 = point1;
    p2 = point2;
    p3 = point3;

    normal = normalize(cross(subtract(p1, p2), subtract(p1, p3)));
}

MeshObject::MeshObject() {
    material = ObjectMaterial();

    p1 = (Vector3){0, 0, 0};
    p2 = (Vector3){0, 0, 0};
    p3 = (Vector3){0, 0, 0};

    normal = normalize(cross(subtract(p1, p2), subtract(p1, p3)));
}