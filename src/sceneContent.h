#ifndef SCENECONTENT_H
#define SCENECONTENT_H

#include "Scene.h"
#include "objects/SDFSphere.h"
#include "objects/SDFTorus.h"
#include "objects/SDFBox.h"
#include "objects/SDFPlane.h"
#include "objects/SDFCylinder.h"

#include "objects/SDFUnion.h"
#include "objects/SDFSubtraction.h"
#include "objects/SDFIntersection.h"

#include "objects/SDFRotate.h"

#include <math.h>
#include <vector>

void initScene(Scene *scene);

#endif