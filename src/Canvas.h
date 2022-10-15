#ifndef CANVAS_H
#define CANVAS_H

#include "raylib.h"

class Canvas {
    public:
        int width;
        int height;

        Canvas(int canvas_width, int canvas_height);

        void PutPixel(int x, int y, Color color);

};

#endif