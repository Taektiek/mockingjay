#include "raylib.h"
#include "Canvas.h"
#include "Scene.h"
#include "MeshObject.h"
#include "VectorMath.h"
#include "ObjectMaterial.h"
#include "MeshPrimitives.h"

#include <tuple>
#include <math.h>
#include <iostream>
#include <utility>
#include <chrono>

#define EPSILON 0.001

double triangleArea(Vector3 p1, Vector3 p2, Vector3 p3) {
    double a = magnitude(subtract(p1, p2));
    double b = magnitude(subtract(p2, p3));
    double c = magnitude(subtract(p3, p1));
    double s = 0.5 * (a + b + c);

    return sqrt(s*(s-a)*(s-b)*(s-c));
}

bool pointInTriangle(Vector3 P, Vector3 A, Vector3 B, Vector3 C) {
    return triangleArea(A, B, C) + EPSILON >= triangleArea(P, A, B) + triangleArea(P, A, C) + triangleArea(P, B, C);
}

bool isBackface(Vector3 corner, Vector3 O, Vector3 N) {
    return dot(subtract(corner, O), N) >= 0;
}

double intersectRayTriangle(Vector3 O, Vector3 D, MeshObject* mesh, int faceIndex) {
    Vector3 n = mesh -> FaceNormal(faceIndex);

    Vector3 v1 = mesh -> vertices[mesh -> faces[faceIndex].cornerIndices[0]].pos;
    Vector3 v2 = mesh -> vertices[mesh -> faces[faceIndex].cornerIndices[1]].pos;
    Vector3 v3 = mesh -> vertices[mesh -> faces[faceIndex].cornerIndices[2]].pos;

    double d = n.x * v1.x + n.y * v1.y + n.z * v1.z;
    double t = (d-n.x*O.x-n.y*O.y-n.z*O.z)/(n.x*D.x+n.y*D.y+n.z*D.z);

    Vector3 P = add(O, multiply(D, t));

    if (!pointInTriangle(P, v1, v2, v3) | isBackface(v1, O, mesh -> FaceNormal(faceIndex))) {
        return 1E9;
    }
    return t;
}

std::tuple<MeshObject*, int, double> ClosestIntersection(Vector3 O, Vector3 D, double t_min, double t_max, Scene scene) {
    double closest_t = 1E9;
    MeshObject *closest_object;
    int faceIndex;

    for (MeshObject *object: scene.objects) {
        int i = 0;
        for (Face face: object -> faces) {
            double t = intersectRayTriangle(O, D, object, i);

            if ((t > t_min && t < t_max) && (t < closest_t)) {
                closest_t = t;
                closest_object = object;
                faceIndex = i;
            }
            i++;
        }
    }

    return std::make_tuple(closest_object, faceIndex, closest_t);
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
            auto intersection = ClosestIntersection(P, multiply(normalize(L), 0.1), 0.001, 1E9, scene);
            double shadow_t = std::get<2>(intersection);
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
    auto closest_intersection = ClosestIntersection(O, D, t_min, t_max, scene);
    MeshObject *closest_object = std::get<0>(closest_intersection);
    int faceIndex = std::get<1>(closest_intersection);
    double closest_t = std::get<2>(closest_intersection);

    if (closest_t==1E9) {
        return RAYWHITE;
    }

    Vector3 P = add(O, multiply(D, closest_t));
    Vector3 N = closest_object -> FaceNormal(faceIndex);
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
    // SetTargetFPS(60);

    Viewport vp(1, 1, 1);

    Scene scene(vp);

    MeshObject* obj = new MeshObject(
        ObjectMaterial(
            {255, 0, 0, 255},
            500,
            0.2
        )
    );

    generateBox(obj, {1, 1, 10}, {1, 1, 1});

    scene.AddObject(obj);

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