#include "raylib.h"
#include "Canvas.h"
#include "Scene.h"
#include "Sphere.h"
#include "VectorMath.h"

#include <math.h>
#include <iostream>

Vector2 IntersectRaySphere(Vector3 O, Vector3 D, Sphere sphere) {
    double r = sphere.radius;
    Vector3 CO = subtract(O, sphere.center);

    double a = dot(D, D);
    double b = 2 * dot(CO, D);
    double c = dot(CO, CO) - r*r;

    double discriminant = b*b-4*a*c;

    if (discriminant < 0) {
        return (Vector2){1E9, 1E9};
    }

    double t1 = (-b + sqrt(discriminant))/(2*a);
    double t2 = (-b - sqrt(discriminant))/(2*a);

    return (Vector2){t1, t2};
}

Color TraceRay(Vector3 O, Vector3 D, float t_min, float t_max, Scene scene) {
    bool found_sphere = false;
    float closest_t = 1E9;
    Sphere closest_sphere;

    for (Sphere sphere: scene.spheres) {
        Vector2 t_points = IntersectRaySphere(O, D, sphere);
        double t1 = t_points.x;
        double t2 = t_points.y;

        // std::cout << t1 << " " << t2 << std::endl;

        if ((t1 > t_min && t1 < t_max)&&(t1<closest_t)) {
            closest_t = t1;
            closest_sphere = sphere;
            found_sphere = true;
        }

        if ((t2 > t_min && t2 < t_max)&&(t2<closest_t)) {
            closest_t = t2;
            closest_sphere = sphere;
            found_sphere = true;
        }
    }
    
    if (!found_sphere) {
        return RAYWHITE;
    }
    return closest_sphere.color;
}

int main(void) {

    Vector3 O = (Vector3){0, 0, 0};

    Canvas canvas(500, 500);

    InitWindow(canvas.width, canvas.height, "raytracing");
    SetTargetFPS(60);

    Viewport vp(1, 1, 1);

    Scene scene(vp);

    scene.AddSphere(Sphere(
        (Vector3){-1,0,5},
        1,
        RED
    ));

    scene.AddSphere(Sphere(
        (Vector3){0.5,0,3},
        1,
        BLUE
    ));
    
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawText("raytracing!", 10, 10, 20, DARKGRAY);

        for (int x = -canvas.width/2; x < canvas.width/2; x++) {
            for (int y = -canvas.height/2; y < canvas.height/2; y++) {
                Vector3 D = vp.CanvasToViewport(canvas, x, y);
                Color color = TraceRay(O, D, 1, 1E9, scene);
                canvas.PutPixel(x, y, color);
            }
        }

        scene.spheres[1].center.z += 0.05;
        scene.spheres[0].center.x += 0.02;
        scene.spheres[0].radius -= 0.005;

        EndDrawing();
    }

    CloseWindow();

    return 0;
}