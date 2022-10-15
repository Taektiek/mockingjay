#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Viewport.h"
#include "Sphere.h"
#include "Light.h"

class Scene {
    public:
        Viewport vp;

        std::vector<Sphere> spheres;
        std::vector<Light> lights;

        Scene(Viewport viewport);

        void AddSphere(Sphere sphere);
        void AddLight(Light light);
};

#endif