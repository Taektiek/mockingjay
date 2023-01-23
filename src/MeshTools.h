#ifndef MESHTOOLS_H
#define MESHTOOLS_H

#include <vector>

#include "raylib.h"

struct Vertex {
    Vector3 pos;
    std::vector<int> faceIndices;
};

struct Face {
    int cornerIndices[3];
    Vector3 normal;
};

#endif