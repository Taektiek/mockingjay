#include "sceneContent.h"

void initScene(Scene *scene) {

    scene -> AddObject(new SDFIntersection(
        {0, 0, 10},
        new SDFRotate(
            (Vector3){0, 0, 0}, // center
            new SDFTorus(
                (Vector3){0, 0, 0}, // center
                {1, 0.5}, // radii
                ObjectMaterial()
            ),
            45, // x rot
            0, // y rot
            30, // z rot
            ObjectMaterial()
        ),
        new SDFRotate(      
            (Vector3){0, 0, 0}, // center
            new SDFBox(
                (Vector3){0, 0, 0}, // center
                {1, 1, 1}, // box
                ObjectMaterial()
            ),
            -45, // x rot
            90, // y rot
            30, // z rot
            ObjectMaterial()
        ),
        ObjectMaterial(
            {255, 0, 0, 255},
            500,
            0.2
        )

    ));

    scene -> AddObject(new SDFRotate(
        (Vector3){3, 0, 10}, // center
        new SDFCylinder(
            (Vector3){0, 0, 0}, // center
            1,
            0.3,
            ObjectMaterial()
        ),
        -45, // x rot
        90, // y rot
        120, // z rot
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