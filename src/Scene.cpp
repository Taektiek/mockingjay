#include "Scene.h"

Scene::Scene(Viewport viewport) {
    vp = viewport;
}

void Scene::AddSphere(Sphere sphere) {
    spheres.push_back(sphere);
}

void Scene::AddLight(Light light) {
    lights.push_back(light);
}