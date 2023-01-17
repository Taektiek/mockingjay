#include "raylib.h"
#include "Canvas.h"
#include "Scene.h"
#include "MeshObject.h"
#include "VectorMath.h"
#include "ObjectMaterial.h"

#include <math.h>
#include <iostream>
#include <utility>

#define EPSILON 0.01

double intersectRayTriangle(Vector3 O, Vector3 D, MeshObject* mesh) {
    Vector3 n = mesh -> normal;
    double d = n.x * mesh -> p1.x + n.y * mesh -> p1.y + n.z * mesh -> p1.z;
    return (d-n.x*O.x-n.y*O.y-n.z*O.z)/(n.x*D.x+n.y*D.y+n.z*D.z);
}

double triangleArea(Vector2 p1, Vector2 p2, Vector2 p3) {
    double a = magnitude(subtract(p1, p2));
    double b = magnitude(subtract(p2, p3));
    double c = magnitude(subtract(p3, p1));
    double s = 0.5 * (a + b + c);

    return sqrt(s*(s-a)*(s-b)*(s-c));
}

bool pointInTriangle(Vector2 P, Vector2 A, Vector2 B, Vector2 C) {
    return triangleArea(A, B, C) + EPSILON >= triangleArea(P, A, B) + triangleArea(P, A, C) + triangleArea(P, B, C);
}

Vector2 projectToAxis(Vector3 P) {
    return (Vector2){P.x, P.y};
}

std::pair<MeshObject*, double> ClosestIntersection(Vector3 O, Vector3 D, double t_min, double t_max, Scene scene) {
    double closest_t = 1E9;
    MeshObject *closest_object;

    for (MeshObject *object: scene.objects) {
        double t = intersectRayTriangle(O, D, object);

        Vector3 P = add(O, multiply(D, t));

        // Project

        Vector2 Pp = projectToAxis(P);

        Vector2 Ap = projectToAxis(object -> p1);
        Vector2 Bp = projectToAxis(object -> p2);
        Vector2 Cp = projectToAxis(object -> p3);

        if (!pointInTriangle(Pp, Ap, Bp, Cp)) {
            t = 1E9;
        }

        if ((t > t_min && t < t_max) && (t < closest_t)) {
            closest_t = t;
            closest_object = object;
        }
    }

    return std::make_pair(closest_object, closest_t);
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
            double shadow_t = ClosestIntersection(P, multiply(normalize(L), 0.1), 0.001, 1E9, scene).second;
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
    std::pair<MeshObject*, double> closest_intersection = ClosestIntersection(O, D, t_min, t_max, scene);
    MeshObject *closest_object = closest_intersection.first;
    double closest_t = closest_intersection.second;

    if (closest_t==1E9) {
        return RAYWHITE;
    }

    Vector3 P = add(O, multiply(D, closest_t));
    Vector3 N = closest_object -> normal;
    Color local_color = multiply(closest_object->material.color, ComputeLighting(P, N, multiply(D, -1), closest_object->material.specular, scene));

    double r = closest_object->material.reflective;
    if (recursion_depth <=0 || r <= 0) {
        return local_color;
    }

    Vector3 R = ReflectRay(multiply(D, -1), N);
    Color reflected_color = TraceRay(P, R, 0.001, 1E9, scene, recursion_depth - 1);

    return add(multiply(local_color, 1 - r), multiply(reflected_color, r));

}

int main(void) {

    Vector3 O = (Vector3){0, 0, 0};

    Canvas canvas(500, 500);

    InitWindow(canvas.width, canvas.height, "raytracing");
    SetTargetFPS(60);

    Viewport vp(1, 1, 1);

    Scene scene(vp);

    std::cout << "Initialize scene" << std::endl;

    scene.AddObject(new MeshObject(
        {0, 0, 10},
        {0, 2, 10},
        {2, 0, 10},
        ObjectMaterial(
            {255, 0, 0, 255},
            500,
            0.2
        )
    ));

    scene.AddObject(new MeshObject(
        {2, 0, 10},
        {0, 2, 10},
        {2, 2, 10},
        ObjectMaterial(
            {255, 0, 0, 255},
            500,
            0.2
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

    std::cout << "Initialized scene" << std::endl;
    
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        for (int x = -canvas.width/2; x < canvas.width/2; x++) {
            if (x % 5 == 0) {
                std::cout << 100+(double)(x-canvas.width/2)/canvas.width * 100 << "% done" << std::endl;
            }
            for (int y = -canvas.height/2; y < canvas.height/2; y++) {
                Vector3 D = normalize(vp.CanvasToViewport(canvas, x, y));
                Color color = TraceRay(O, D, 1, 1E9, scene, 5);
                canvas.PutPixel(x, y, color);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}