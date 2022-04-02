//
// Created by pinto on 11/03/22.
//

#ifndef GENERATOR_GENERATECUBE_H
#define GENERATOR_GENERATECUBE_H

#include <vector>
#include <string>

class GenerateCube {
public:
    static void DrawPlanesZ(float length, float divisions);

    static void DrawPlanesX(float length, float divisions);

    static void DrawPlanesY(float length, float divisions);

    static void DrawPlaneY(float length, float divisions);
private:
    static void DrawSquareAxisY_Forward(float x, float y, float z, float length);

    static void DrawSquareAxisY_Backwards(float x, float y, float z, float length);

    static void DrawSquareAxisX_Forward(float x, float y, float z, float length);

    static void DrawSquareAxisX_Backwards(float x, float y, float z, float length);

    static void DrawSquareAxisZ_Forward(float x, float y, float z, float length);

    static void DrawSquareAxisZ_Backwards(float x, float y, float z, float length);
};


#endif //GENERATOR_GENERATECUBE_H
