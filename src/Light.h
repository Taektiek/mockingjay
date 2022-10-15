#ifndef LIGHT_H
#define LIGHT_H

#include "raylib.h"

class Light {
    public:
        int type; // 0: ambient; 1: point; 2: directional
        float intensity;

        Vector3 position;
        Vector3 direction;

        Light();
        Light(int t, float i);
        Light(int t, float i, Vector3 pos_or_rot);
};

#endif