#include "sceneContent.h"

void initScene(Scene *scene) {

    scene -> AddObject(new SDFSphere(
        (Vector3){0, 0, 10}, // center
        2, //radius
        ObjectMaterial (
            (Color){153,181,210, 255}, // color
            500, // specular
            0.1 // reflective
        )
    ));

    scene -> AddObject(new SDFTorus(
        (Vector3){0, -3, 10}, // center
        (Vector2){2, 0.5}, // radii
        ObjectMaterial (
            (Color){0, 255, 0, 255}, // color
            500, // specular
            0.1 // reflective
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