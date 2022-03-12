//
// Created by pinto on 11/03/22.
//

#ifndef GENERATOR_GENERATECUBE_H
#define GENERATOR_GENERATECUBE_H

#include <vector>
#include <string>

class Vector3{
public:
    float x;
    float y;
    float z;
    Vector3(float x1,float y1,float z1){
        x = x1;
        y = y1;
        z = z1;
    }
    std::basic_string<char> PrintVector()
    {
        const std::string s = "x =" + std::to_string(x) + " y =" + std::to_string(y) + " z=" +std::to_string(z);
        return s;
    }
};

class GenerateCube {
public:
    static void PushVertex(float x,float y,float z);
    static void PrintAllVertices();
    static std::vector<Vector3> GetAllVertices();

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
