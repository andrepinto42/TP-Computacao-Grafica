//
// Created by pinto on 11/03/22.
//

#include "GenerateCube.h"
#include <vector>
#include <math.h>
#include <iostream>

static std::vector<Vector3> allVertices;

std::vector<Vector3> GenerateCube::GetAllVertices() {
    return allVertices;
}
void GenerateCube::PushVertex(float x, float y, float z) {
    Vector3 *v1 =  new Vector3(x,y,z);
    allVertices.push_back(*v1);
}

void GenerateCube::PrintAllVertices() {
    for (int i = 0; i < allVertices.size(); ++i) {
        std::cout << allVertices[i].PrintVector()<< "\n";
    }
}

void GenerateCube::DrawPlanesZ(float length, float divisions) {
    float startZX = (sqrt(length * length *2.0f) / 2.0f);
    float endZX = startZX - length ;
    float tam = length / divisions;


    for (float i = 0.0f; i < length; i+=tam) {
        for (float j = startZX-tam; j > endZX-tam; j-=tam) {
            DrawSquareAxisZ_Forward(j, i, startZX- tam, tam);
        }
    }

    for (float i = 0.0f; i < length; i+=tam) {
        for (float j = startZX-tam; j > endZX-tam; j-=tam) {
            DrawSquareAxisZ_Backwards(j, i, -startZX+ tam, tam);
        }
    }
}

void GenerateCube::DrawPlanesX(float length, float divisions) {
    float startZX = (sqrt(length * length *2.0f) / 2.0f);
    float endZX = startZX - length ;
    float tam = length / divisions;



    for (float i = 0.0f; i < length; i+=tam) {
        for (float j = startZX-tam; j > endZX-tam; j-=tam) {
            DrawSquareAxisX_Forward(startZX - tam, i, j, tam);
        }
    }

    for (float i = 0.0f; i < length; i+=tam) {
        for (float j = startZX-tam; j > endZX-tam; j-=tam) {
            DrawSquareAxisX_Backwards(-startZX + tam, i, j, tam);
        }
    }


}

void GenerateCube::DrawPlanesY(float length, float divisions) {
    float tam = length / divisions;
    float startZX = (sqrt(length * length *2.0f) / 2.0f);
    float endZX = startZX - length ;


    for (float i = startZX-tam; i > endZX-tam; i-=tam) {
        for (float j = startZX-tam; j > endZX-tam; j-=tam) {
            DrawSquareAxisY_Backwards(i, 0.0f, j, tam);
        }
    }

    for (float i = startZX-tam; i > endZX-tam; i-=tam) {
        for (float j = startZX-tam; j > endZX-tam; j-=tam) {
            DrawSquareAxisY_Forward(i, length, j, tam);
        }
    }
}

void GenerateCube::DrawPlaneY(float length, float divisions) {
    float tam = length / divisions;
    float startZX = (sqrt(length * length *2.0f) / 2.0f);
    float endZX = startZX - length ;

    for (float i = startZX-tam; i > endZX-tam; i-=tam) {
        for (float j = startZX-tam; j > endZX-tam; j-=tam) {
            DrawSquareAxisY_Forward(i, 0.0f, j, tam);
        }
    }
}
void GenerateCube::DrawSquareAxisY_Forward(float x, float y, float z, float length) {
    PushVertex(x,y,z);
    PushVertex(x,y,z-length);
    PushVertex(x-length,y,z-length);

    PushVertex(x,y,z);
    PushVertex(x-length,y,z-length);
    PushVertex(x-length,y,z);
}

void GenerateCube::DrawSquareAxisY_Backwards(float x, float y, float z, float length) {
    PushVertex(x,y,z);
    PushVertex(x-length,y,z-length);
    PushVertex(x,y,z-length);

    PushVertex(x,y,z);
    PushVertex(x-length,y,z);
    PushVertex(x-length,y,z-length);
}

void GenerateCube::DrawSquareAxisX_Forward(float x, float y, float z, float length) {

    PushVertex(x,y,z);
    PushVertex(x,y,z-length);
    PushVertex(x,y+length,z-length);

    PushVertex(x,y,z);
    PushVertex(x,y+length,z-length);
    PushVertex(x,y+length,z);
}

void GenerateCube::DrawSquareAxisX_Backwards(float x, float y, float z, float length) {

    PushVertex(x,y,z);
    PushVertex(x,y+length,z-length);
    PushVertex(x,y,z-length);

    PushVertex(x,y,z);
    PushVertex(x,y+length,z);
    PushVertex(x,y+length,z-length);
}

void GenerateCube::DrawSquareAxisZ_Forward(float x, float y, float z, float length) {
    PushVertex(x,y,z);
    PushVertex(x-length,y+length,z);
    PushVertex(x-length,y,z);

    PushVertex(x,y,z);
    PushVertex(x,y+length,z);
    PushVertex(x-length,y+length,z);
}

void GenerateCube::DrawSquareAxisZ_Backwards(float x, float y, float z, float length) {
    PushVertex(x,y,z);
    PushVertex(x-length,y,z);
    PushVertex(x-length,y+length,z);

    PushVertex(x,y,z);
    PushVertex(x-length,y+length,z);
    PushVertex(x,y+length,z);
}


