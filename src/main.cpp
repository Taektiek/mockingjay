#include "raylib.h"
#include "Canvas.h"
#include "Scene.h"
#include "Sphere.h"
#include "VectorMath.h"
#include "ObjectMaterial.h"

#include <math.h>
#include <iostream>
#include <utility>

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

// double IntersectRaySDF(Vector3 O, Vector3 D, SDFObject object) {
//     return 0;
// }

std::pair<Sphere, double> ClosestIntersection(Vector3 O, Vector3 D, double t_min, double t_max, Scene scene) {
    double closest_t = 1E9;
    Sphere closest_sphere;

    for (Sphere sphere: scene.spheres) {
        Vector2 t_points = IntersectRaySphere(O, D, sphere);
        double t1 = t_points.x;
        double t2 = t_points.y;

        if ((t1 > t_min && t1 < t_max)&&(t1<closest_t)) {
            closest_t = t1;
            closest_sphere = sphere;
        }

        if ((t2 > t_min && t2 < t_max)&&(t2<closest_t)) {
            closest_t = t2;
            closest_sphere = sphere;
        }
    }

    return std::make_pair(closest_sphere, closest_t);
}

double ComputeLighting(Vector3 P, Vector3 N, Vector3 V, double s, Scene scene) {
    double i = 0.0;
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

            // Shadow Check
            double shadow_t = ClosestIntersection(P, L, 0.001, 1E9, scene).second;
            if (shadow_t != 1E9) {
                continue;
            } 

            // Diffuse
            double n_dot_l = dot(N, L);
            if (n_dot_l > 0) {
                i += light.intensity * n_dot_l/magnitude(L);
            }

            // Specular
            if (s != -1) {
                Vector3 R = subtract(multiply(N, 2* dot(N, L)), L);
                double r_dot_v = dot(R, V);
                if (r_dot_v > 0) {
                    i += light.intensity * pow(r_dot_v/(magnitude(R)*magnitude(V)), s);
                }
            }
        }
    }
    return i;
}

Vector3 ReflectRay(Vector3 R, Vector3 N) {
    return subtract(multiply(N, 2 * dot(N, R)), R);
}

Color TraceRay(Vector3 O, Vector3 D, double t_min, double t_max, Scene scene, int recursion_depth) {   
    std::pair<Sphere, double> closest_intersection = ClosestIntersection(O, D, t_min, t_max, scene);
    Sphere closest_sphere = closest_intersection.first;
    double closest_t = closest_intersection.second;

    if (closest_t==1E9) {
        return RAYWHITE;
    }

    Vector3 P = add(O, multiply(D, closest_t));
    Vector3 N = subtract(P, closest_sphere.center);
    N = multiply(N, 1/magnitude(N));
    Color local_color = multiply(closest_sphere.material.color, ComputeLighting(P, N, multiply(D, -1), closest_sphere.material.specular, scene));

    double r = closest_sphere.material.reflective;
    if (recursion_depth <=0 || r <= 0) {
        return local_color;
    }

    Vector3 R = ReflectRay(multiply(D, -1), N);
    Color reflected_color = TraceRay(P, R, 0.001, 1E9, scene, recursion_depth - 1);

    return add(multiply(local_color, 1 - r), multiply(reflected_color, r)); 

}

int main(void) {

    Vector3 O = (Vector3){0, 0, 0};

    Canvas canvas(1000, 1000);

    InitWindow(canvas.width, canvas.height, "raytracing");
    SetTargetFPS(60);

    Viewport vp(1, 1, 1);

    Scene scene(vp);

    scene.AddSphere(Sphere(
        (Vector3){0, -1, 3},
        1,
        ObjectMaterial (
            (Color){255, 0, 0, 255},
            500,
            0.2
        )
    ));

    scene.AddSphere(Sphere(
        (Vector3){2, 0, 4},
        1,
        ObjectMaterial (
            (Color){0, 0, 255, 255},
            500,
            0.2
        )
    ));

    scene.AddSphere(Sphere(
        (Vector3){-2, 0, 4},
        1,
        ObjectMaterial (
            (Color){0, 255, 0, 255},
            500,
            0.2
        )
    ));

    scene.AddSphere(Sphere(
        (Vector3){0, -5001, 0},
        5000,
        ObjectMaterial (
            (Color){255, 255, 0, 255},
            500,
            0
        )
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
                Color color = TraceRay(O, D, 1, 1E9, scene, 3);
                canvas.PutPixel(x, y, color);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}