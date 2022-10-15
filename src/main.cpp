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

float ComputeLighting(Vector3 P, Vector3 N, Scene scene) {
    float i = 0.0;
    Vector3 L;

    for (Light light: scene.lights) {
        if (light.type == 0) {
            i += light.intensity;
        } else {
            if (light.type == 1) {
                L = subtract(light.position, P);
            } else if (light.type == 2) {
                L = light.direction;
            }
            float n_dot_l = dot(N, L);
            if (n_dot_l > 0) {
                i += light.intensity * n_dot_l/magnitude(L);
            }
        }
    }
    return i;
}

Color TraceRay(Vector3 O, Vector3 D, float t_min, float t_max, Scene scene) {
    bool found_sphere = false;
    float closest_t = 1E9;
    Sphere closest_sphere;

    for (Sphere sphere: scene.spheres) {
        Vector2 t_points = IntersectRaySphere(O, D, sphere);
        double t1 = t_points.x;
        double t2 = t_points.y;

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

    Vector3 P = multiply(D, closest_t);
    Vector3 N = subtract(P, closest_sphere.center);
    N = multiply(N, 1/magnitude(N));
    return (multiply(closest_sphere.color, ComputeLighting(P, N, scene)));
}

int main(void) {

    Vector3 O = (Vector3){0, 0, 0};

    Canvas canvas(1000, 1000);

    InitWindow(canvas.width, canvas.height, "raytracing");
    SetTargetFPS(60);

    Viewport vp(1, 1, 1);

    Scene scene(vp);

    scene.AddSphere(Sphere(
        (Vector3){0, 0, 5},
        1,
        BEIGE
    ));

    scene.AddSphere(Sphere(
        (Vector3){1, 1, 5},
        0.5,
        DARKGRAY
    ));

    scene.AddSphere(Sphere(
        (Vector3){-1, 1, 5},
        0.5,
        DARKGRAY
    ));

    scene.AddSphere(Sphere(
        (Vector3){0, 0, 4},
        0.2,
        DARKGRAY
    ));

    scene.AddSphere(Sphere(
        (Vector3){0.35, 0.3, 4.2},
        0.2,
        RAYWHITE
    ));

    scene.AddSphere(Sphere(
        (Vector3){-0.35, 0.3, 4.2},
        0.2,
        RAYWHITE
    ));

    scene.AddSphere(Sphere(
        (Vector3){0.35, 0.3, 4},
        0.05,
        BLACK
    ));

    scene.AddSphere(Sphere(
        (Vector3){-0.35, 0.3, 4},
        0.05,
        BLACK
    ));

    scene.AddSphere(Sphere(
        (Vector3){0, -0.35, 3},
        0.15,
        (Color){50,50,50}
    ));

    scene.AddLight(Light(
        0, // Ambient
        0.2
    ));

    scene.AddLight(Light(
        1, // Point
        0.6,
        (Vector3){2, 1, 0}
    ));

    scene.AddLight(Light(
        2, // Directional
        0.2,
        (Vector3){1, 4, 4}
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

        EndDrawing();
    }

    CloseWindow();

    return 0;
}