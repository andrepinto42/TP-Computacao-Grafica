//
// Created by pinto on 29/04/22.
//

#ifndef MAIN_CPP_BEZIERCURVES_H
#define MAIN_CPP_BEZIERCURVES_H


#include "Generator/Vector3.h"

class BezierCurves {

public:
    static void DrawBezier();

    static void DrawQuadsWith2Curves(std::vector<Vector3> vector1, std::vector<Vector3> vector2);


};


#endif //MAIN_CPP_BEZIERCURVES_H
