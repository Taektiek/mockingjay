#include "sceneContent.h"

void initScene(Scene *scene) {

    scene -> AddObject(new SDFSphere(
        {-1, 1, 10}, //center
        2.5, // radius
        ObjectMaterial(
            {255, 0, 0, 255},
            500,
            0.2
        )
    ));

    scene -> AddObject(new SDFSphere(
        {1, -1, 8}, //center
        1, // radius
        ObjectMaterial(
            {0, 0, 255, 255},
            500,
            0.2
        )
    ));

    scene -> AddObject(new SDFSphere(
        {-1, -2.5, 9}, //center
        0.7, // radius
        ObjectMaterial(
            {0, 255, 0, 255},
            500,
            0.2
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