#include "Viewport.h"

Viewport::Viewport(float w, float h, float ppd) {
    width = w;
    height = h;

    projection_plane_distance = ppd;
}

Viewport::Viewport() {
    width = 1.0;
    height = 1.0;

    projection_plane_distance = 1.0;
}

Vector3 Viewport::CanvasToViewport(Canvas canvas, int x, int y) {
    return (Vector3){x*width/canvas.width, y*height/canvas.height, projection_plane_distance};
}