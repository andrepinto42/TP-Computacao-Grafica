//
// Created by pinto on 10/03/22.
//

#ifndef MAIN_CPP_HANDLERDRAWSQUARE_H
#define MAIN_CPP_HANDLERDRAWSQUARE_H
class HandlerDrawSquare{
public:
    static void DrawPlanesZ(float length, float divisions);

    static void DrawPlanesX(float length, float divisions);

    static void DrawPlanesY(float length, float divisions);

    static void DrawSquareAxisY_Forward(float x, float y, float z, float length);

    static void DrawSquareAxisY_Backwards(float x, float y, float z, float length);

    static void DrawSquareAxisX_Forward(float x, float y, float z, float length);

    static void DrawSquareAxisX_Backwards(float x, float y, float z, float length);

    static void DrawSquareAxisZ_Forward(float x, float y, float z, float length);

    static void DrawSquareAxisZ_Backwards(float x, float y, float z, float length);
};

#endif //MAIN_CPP_HANDLERDRAWSQUARE_H
