//
// Created by pinto on 12/03/22.
//

#ifndef MAIN_CPP_HANDLERMODEL_H
#define MAIN_CPP_HANDLERMODEL_H


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "Generator/Vector3.h"

class HandlerModel {
public:
    std::vector<Vector3> allVertices;
    void Draw();
};


#endif //MAIN_CPP_HANDLERMODEL_H
