#ifndef OBJECTMATERIAL_H
#define OBJECTMATERIAL_H

#include "raylib.h"

class ObjectMaterial {
    public: 
        Color color;
        double specular;
        double reflective;

        ObjectMaterial(Color color, double specular, double reflective);
        ObjectMaterial();
};

#endif