#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Canvas.h"
#include "raylib.h"

class Viewport {
    public:
        double width;
        double height;

        double projection_plane_distance;

        Viewport(double w, double h, double ppd);
        Viewport();

        Vector3 CanvasToViewport(Canvas canvas, int x, int y);
};

#endif