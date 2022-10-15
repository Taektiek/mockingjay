#include "Light.h"

Light::Light() {
    type = 0;
    intensity = 1;
    position = (Vector3){0, 0, 0};
    direction = (Vector3){0, 0, 0};
}

Light::Light(int t, float i) {
    type = t;
    intensity = i;
    position = (Vector3){0, 0, 0};
    direction = (Vector3){0, 0, 0};
}

Light::Light(int t, float i, Vector3 pos_or_rot) {
    type = t;
    intensity = i;
    if (type == 1) {
        position = pos_or_rot;
        direction = (Vector3){0, 0, 0};
    } else if (type == 2) {
        position = (Vector3){0, 0, 0};
        direction = pos_or_rot;
    }
}