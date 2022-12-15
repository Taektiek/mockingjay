#include "Scene.h"

Scene::Scene(Viewport viewport) {
    vp = viewport;
}

void Scene::AddObject(SDFObject *object) {
    objects.push_back(object);
}

void Scene::AddLight(Light light) {
    lights.push_back(light);
}