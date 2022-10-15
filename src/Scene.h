#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Viewport.h"
#include "Sphere.h"

class Scene {
    public:
        Viewport vp;

        std::vector<Sphere> spheres;

        Scene(Viewport viewport);

        void AddSphere(Sphere sphere);
};

#endif