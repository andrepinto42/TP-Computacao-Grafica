//
// Created by pinto on 11/03/22.
//

#include "GenerateCube.h"
#include "GenerateSphere.h"
#include <vector>
#include <math.h>
#include <iostream>
#include "main.h"


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
            DrawSquareAxisZ_Backwards(j, i, endZX - tam, tam);
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
            DrawSquareAxisX_Backwards(endZX - tam, i, j, tam);
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

void GenerateCube::DrawSquareAxisY_Forward(float x, float y, float z, float length) {
    main::PushVertex(x,y,z);
    main::PushVertex(x,y,z-length);
    main::PushVertex(x-length,y,z-length);

    main::PushNormal(0.f,1.f,0.f);
    main::PushNormal(0.f,1.f,0.f);
    main::PushNormal(0.f,1.f,0.f);


    main::PushVertex(x,y,z);
    main::PushVertex(x-length,y,z-length);
    main::PushVertex(x-length,y,z);

    main::PushNormal(0.f,1.f,0.f);
    main::PushNormal(0.f,1.f,0.f);
    main::PushNormal(0.f,1.f,0.f);

}

void GenerateCube::DrawSquareAxisY_Backwards(float x, float y, float z, float length) {
    main::PushVertex(x,y,z);
    main::PushVertex(x-length,y,z-length);
    main::PushVertex(x,y,z-length);

    for (int i = 0; i < 3; ++i) {
        main::PushNormal(0.f,-1.f,0.f);
    }

    main::PushVertex(x,y,z);
    main::PushVertex(x-length,y,z);
    main::PushVertex(x-length,y,z-length);
    for (int i = 0; i < 3; ++i) {
        main::PushNormal(0.f,-1.f,0.f);
    }
}

void GenerateCube::DrawSquareAxisX_Forward(float x, float y, float z, float length) {

    main::PushVertex(x,y,z);
    main::PushVertex(x,y,z-length);
    main::PushVertex(x,y+length,z-length);

    for (int i = 0; i < 3; ++i) {
        main::PushNormal(1.f,0.f,0.f);
    }
    main::PushVertex(x,y,z);
    main::PushVertex(x,y+length,z-length);
    main::PushVertex(x,y+length,z);
    for (int i = 0; i < 3; ++i) {
        main::PushNormal(1.f,0.f,0.f);
    }
}

void GenerateCube::DrawSquareAxisX_Backwards(float x, float y, float z, float length) {

    main::PushVertex(x,y,z);
    main::PushVertex(x,y+length,z-length);
    main::PushVertex(x,y,z-length);
    for (int i = 0; i < 3; ++i) {
        main::PushNormal(-1.f,0.f,0.f);
    }
    main::PushVertex(x,y,z);
    main::PushVertex(x,y+length,z);
    main::PushVertex(x,y+length,z-length);
    for (int i = 0; i < 3; ++i) {
        main::PushNormal(-1.f,0.f,0.f);
    }
}

void GenerateCube::DrawSquareAxisZ_Forward(float x, float y, float z, float length) {

    main::PushVertex(x,y,z);
    main::PushVertex(x-length,y+length,z);
    main::PushVertex(x-length,y,z);
    for (int i = 0; i < 3; ++i) {
        main::PushNormal(0.f,0.f,1.f);
    }

    main::PushVertex(x,y,z);
    main::PushVertex(x,y+length,z);
    main::PushVertex(x-length,y+length,z);

    for (int i = 0; i < 3; ++i) {
        main::PushNormal(0.f,0.f,1.f);
    }
}

void GenerateCube::DrawSquareAxisZ_Backwards(float x, float y, float z, float length) {

    main::PushVertex(x,y,z);
    main::PushVertex(x-length,y,z);
    main::PushVertex(x-length,y+length,z);

    for (int i = 0; i < 3; ++i) {
        main::PushNormal(0.f,0.f,-1.f);
    }

    main::PushVertex(x,y,z);
    main::PushVertex(x-length,y+length,z);
    main::PushVertex(x,y+length,z);

    for (int i = 0; i < 3; ++i) {
        main::PushNormal(0.f,0.f,-1.f);
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

