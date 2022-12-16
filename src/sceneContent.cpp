#include "sceneContent.h"

void initScene(Scene *scene) {

    scene -> AddObject(new SDFSubtraction(
        {0, 0, 10},
        new SDFIntersection(
            {0, 0, 0},
            new SDFSphere(
                {0,0,0},
                1,
                ObjectMaterial()
            ),
            new SDFSphere(
                {0.5,0,-.3},
                1,
                ObjectMaterial()
            ),
            ObjectMaterial()
        ),
        new SDFSphere(
            {0.5, 0.3, -0.1},
            0.7,
            ObjectMaterial()
        ),
        ObjectMaterial(
            {255, 0, 0, 255},
            100,
            0.2
        )
    ));

    scene -> AddObject(new SDFTorus(
        {0, 0, 10},
        {2,0.2},
        ObjectMaterial(
            {255, 255, 0, 255},
            100,
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
        {2, 1, 0}
    ));

    scene -> AddLight(Light(
        2, // Directional
        0.2,
        {0, 4, 4}
    ));
}