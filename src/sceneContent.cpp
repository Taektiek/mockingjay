#include "sceneContent.h"

void initScene(Scene *scene) {

    scene -> AddObject(new SDFCylinder(
        (Vector3){0, 3, 10}, // center
        1, // height
        0.5, // radius
        ObjectMaterial (
            (Color){255, 0, 0, 255}, // color
            500, // specular
            0.2 // reflective
        )
    ));

    scene -> AddObject(new SDFCylinder(
        (Vector3){0, 0, 10}, // center
        1.5, // height
        1, // radius
        ObjectMaterial (
            (Color){0, 255, 0, 255}, // color
            500, // specular
            0.2 // reflective
        )
    ));

    scene -> AddObject(new SDFCylinder(
        (Vector3){0, -3, 10}, // center
        1, // height
        2, // radius
        ObjectMaterial (
            (Color){0, 0, 255, 255}, // color
            500, // specular
            0.2 // reflective
        )
    ));

    scene -> AddLight(Light(
        0, // Ambient
        0.2
    ));

    scene -> AddLight(Light(
        1, // Point
        0.6,
        (Vector3){2, 1, 0}
    ));

    scene -> AddLight(Light(
        2, // Directional
        0.2,
        (Vector3){1, 4, 4}
    ));
}