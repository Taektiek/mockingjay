#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Viewport.h"
#include "MeshObject.h"
#include "Light.h"

class Scene {
    public:
        Viewport vp;

        std::vector<MeshObject*> objects;
        std::vector<Light> lights;

        Scene(Viewport viewport);

        void AddObject(MeshObject *object);
        void AddLight(Light light);
};

#endif