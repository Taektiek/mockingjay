#include "Canvas.h"

Canvas::Canvas(int canvas_width, int canvas_height) {
    width = canvas_width;
    height = canvas_height;
}

void Canvas::PutPixel(int Cx, int Cy, Color color) {
    int Sx = width/2 + Cx;
    int Sy = height-(height/2 + Cy);

    DrawPixel(Sx, Sy, color);
};