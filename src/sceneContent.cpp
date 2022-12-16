#include "sceneContent.h"

void initScene(Scene *scene) {

    scene -> AddObject(new SDFIntersection(
        {0, 0, 10}, // center
        new SDFSphere(
            (Vector3){1, 0, 0}, // center
            2, // radius
            ObjectMaterial()
        ),
        new SDFSphere(
            (Vector3){-1, 0, 0.5}, // center
            1, // radius
            ObjectMaterial()
        ), 
        ObjectMaterial (
            (Color){255, 0, 0, 255}, // color
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