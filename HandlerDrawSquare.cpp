//
// Created by pinto on 10/03/22.
//

#include "Axes.h"
#include "Parser.h"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "HandlerDrawSquare.h"



void HandlerDrawSquare::DrawPlanesZ(float length, float divisions) {
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

void HandlerDrawSquare::DrawPlanesX(float length, float divisions) {
    float startZX = (sqrt(length * length *2.0f) / 2.0f);
    float endZX = startZX - length ;
    float tam = length / divisions;



    for (float i = 0.0f; i < length; i+=tam) {
        for (float j = startZX-tam; j > endZX-tam; j-=tam) {
            DrawSquareAxisX_Forward(startZX -tam, i, j, tam);
        }
    }

    for (float i = 0.0f; i < length; i+=tam) {
        for (float j = startZX-tam; j > endZX-tam; j-=tam) {
            DrawSquareAxisX_Backwards(endZX-tam, i, j, tam);
        }
    }


}

void HandlerDrawSquare::DrawPlanesY(float length, float divisions) {
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

void HandlerDrawSquare::DrawSquareAxisY_Forward(float x, float y, float z, float length) {
    glBegin(GL_TRIANGLES);
    glColor3f(0.f,0.f,1.f);
    glVertex3d(x,y,z);
    glVertex3d(x,y,z-length);
    glVertex3d(x-length,y,z-length);

    glVertex3d(x,y,z);
    glVertex3d(x-length,y,z-length);
    glVertex3d(x-length,y,z);
    glEnd();
}

void HandlerDrawSquare::DrawSquareAxisY_Backwards(float x, float y, float z, float length) {
    glBegin(GL_TRIANGLES);
    glColor3f(0.f,0.f,1.f);
    glVertex3d(x,y,z);
    glVertex3d(x-length,y,z-length);
    glVertex3d(x,y,z-length);

    glVertex3d(x,y,z);
    glVertex3d(x-length,y,z);
    glVertex3d(x-length,y,z-length);
    glEnd();
}

void HandlerDrawSquare::DrawSquareAxisX_Forward(float x, float y, float z, float length) {

    glBegin(GL_TRIANGLES);
    glColor3f(0.f,1.f,0.f);
    glVertex3d(x,y,z);
    glVertex3d(x,y,z-length);
    glVertex3d(x,y+length,z-length);

    glVertex3d(x,y,z);
    glVertex3d(x,y+length,z-length);
    glVertex3d(x,y+length,z);
    glEnd();
}

void HandlerDrawSquare::DrawSquareAxisX_Backwards(float x, float y, float z, float length) {

    glBegin(GL_TRIANGLES);
    glColor3f(0.f,1.f,0.f);
    glVertex3d(x,y,z);
    glVertex3d(x,y+length,z-length);
    glVertex3d(x,y,z-length);

    glVertex3d(x,y,z);
    glVertex3d(x,y+length,z);
    glVertex3d(x,y+length,z-length);
    glEnd();
}

void HandlerDrawSquare::DrawSquareAxisZ_Forward(float x, float y, float z, float length) {

    glBegin(GL_TRIANGLES);
    glColor3f(1.f,0.f,0.f);
    glVertex3d(x,y,z);
    glVertex3d(x-length,y+length,z);
    glVertex3d(x-length,y,z);

    glVertex3d(x,y,z);
    glVertex3d(x,y+length,z);
    glVertex3d(x-length,y+length,z);
    glEnd();
}

void HandlerDrawSquare::DrawSquareAxisZ_Backwards(float x, float y, float z, float length) {

    glBegin(GL_TRIANGLES);
    glColor3f(1.f,0.f,0.f);
    glVertex3d(x,y,z);
    glVertex3d(x-length,y,z);
    glVertex3d(x-length,y+length,z);

    glVertex3d(x,y,z);
    glVertex3d(x-length,y+length,z);
    glVertex3d(x,y+length,z);
    glEnd();
}