//
// Created by pinto on 04/03/22.
//

#ifndef MAIN_CPP_HANDLEDRAWSPHERE_H
#define MAIN_CPP_HANDLEDRAWSPHERE_H


#include <GL/gl.h>

class HandleDrawSphere {
public:
    static float polar2CartX(float radius, float angle);
    static float polar2CartZ(float radius, float angle);

    static void DrawSphere(float radius , int slices, int stacks);

    static void drawBaseCilinderTriangle(float base, float radius, float angle1, float angle2);


    static void drawSideCilinderTriangle(float bottomHeight,float topHeight, float bottomRadius,float topRadius, float angle1, float angle2);
};


#endif //MAIN_CPP_HANDLEDRAWSPHERE_H
