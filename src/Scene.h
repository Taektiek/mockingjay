#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Viewport.h"
#include "SDFObject.h"
#include "Light.h"

class Scene {
    public:
        Viewport vp;

        std::vector<SDFObject*> objects;
        std::vector<Light> lights;

        Scene(Viewport viewport);

        void AddObject(SDFObject *object);
        void AddLight(Light light);
};

#endif