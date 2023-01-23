#include "sceneContent.h"

void initScene(Scene *scene) {

    scene -> AddObject(new SDFBox(
        {1, 0, 10}, //center
        {1, 2, 3}, // box
        ObjectMaterial(
            {255, 0, 0, 255},
            500,
            0.2
        )
    ));

    scene -> AddObject(new SDFBox(
        {-1, 2, 8}, //center
        {0.5, 2, 3}, // box
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