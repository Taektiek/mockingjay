#include "raylib.h"
#include "Canvas.h"
#include "Scene.h"
#include "SDFObject.h"
#include "VectorMath.h"
#include "ObjectMaterial.h"
#include "sceneContent.h"

#include <math.h>
#include <iostream>
#include <utility>
#include <chrono>

double EPSILON = 0.00001;

double marchRay(Vector3 O, Vector3 D, SDFObject *object, double max_distance, int max_marching_steps, double max_depth) {
    double depth = magnitude(D);

    for (int i = 0; i < max_marching_steps; i++) {
        double distance = object->SDF(add(O, multiply(D, depth)));
        if (distance < max_distance) {
            return depth;
        }

        depth += distance;


        if (depth >= max_depth) {
            return 1E9;
        }
    }

    return 1E9;
}

std::pair<SDFObject*, double> ClosestIntersection(Vector3 O, Vector3 D, double t_min, double t_max, Scene scene) {
    double closest_t = 1E9;
    SDFObject *closest_object;

    for (SDFObject *object: scene.objects) {
        double t = marchRay(O, D, object, 0.001, 100000, 1000);

        if ((t > t_min && t < t_max)&&(t<closest_t)) {
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

Vector3 estimateNormal(SDFObject *object, Vector3 P) {
    return normalize((Vector3){
        object->SDF((Vector3){P.x + EPSILON, P.y, P.z}) - object->SDF((Vector3){P.x - EPSILON, P.y, P.z}),
        object->SDF((Vector3){P.x, P.y + EPSILON, P.z}) - object->SDF((Vector3){P.x, P.y - EPSILON, P.z}),
        object->SDF((Vector3){P.x, P.y, P.z  + EPSILON}) - object->SDF((Vector3){P.x, P.y, P.z - EPSILON})
    });
}

Color TraceRay(Vector3 O, Vector3 D, double t_min, double t_max, Scene scene, int recursion_depth) {   
    std::pair<SDFObject*, double> closest_intersection = ClosestIntersection(O, D, t_min, t_max, scene);
    SDFObject *closest_object = closest_intersection.first;
    double closest_t = closest_intersection.second;

    if (closest_t==1E9) {
        return RAYWHITE;
    }

    Vector3 P = add(O, multiply(D, closest_t));
    Vector3 N = estimateNormal(closest_object, P);
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

    initScene(&scene);

    std::cout << "Initialized scene" << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    int x = -canvas.width/2;
    
    while (!WindowShouldClose()) {
        BeginDrawing();

        // if (x % 20 == 0) {
        //     std::cout << 100+(double)(x-canvas.width/2)/canvas.width * 100 << "% done" << std::endl;
        // }
        for (int y = -canvas.height/2; y < canvas.height/2; y++) {
            Vector3 D = normalize(vp.CanvasToViewport(canvas, x, y));
            Color color = TraceRay(O, D, 1, 1E9, scene, 5);
            canvas.PutPixel(x, y, color);
        }

        if (x >= canvas.width/2) {
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << duration.count() << " milliseconds" << std::endl;
            x = -canvas.width/2;
            start = std::chrono::high_resolution_clock::now();
        }

        x++;

        EndDrawing();
    }

    CloseWindow();

    return 0;
}