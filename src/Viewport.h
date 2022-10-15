#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Canvas.h"
#include "raylib.h"

class Viewport {
    public:
        float width;
        float height;

        float projection_plane_distance;

        Viewport(float w, float h, float ppd);
        Viewport();

        Vector3 CanvasToViewport(Canvas canvas, int x, int y);
};

#endif