#ifndef LIGHT_H
#define LIGHT_H

#include "raylib.h"

class Light {
    public:
        int type; // 0: ambient; 1: point; 2: directional
        double intensity;

        Vector3 position;
        Vector3 direction;

        Light();
        Light(int t, double i);
        Light(int t, double i, Vector3 pos_or_rot);
};

#endif