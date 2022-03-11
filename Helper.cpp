//
// Created by pinto on 04/03/22.
//

#include "Helper.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>


float Helper::polar2CartX(float radius,float angle)
{
    return radius * sin(angle * M_PI / 180.f);
}

float Helper::polar2CartZ(float radius, float angle)
{
    return radius * cos(angle *  M_PI / 180.f);
}

void Helper::drawCilinder(float radius , float height, int slice)
{
    int stack = 5;
    float step = 360.f / (float) slice;
    for (int j = 0; j < stack; ++j) {

        for (float i = 0; i < 360.f; i+=step) {
//        drawBaseCilinderTriangle(0, radius, i, i + step);
//        drawBaseCilinderTriangle(height, radius-.5f, i, i + step);
            drawSideCilinderTriangle( height-j-1,height-j,radius,radius-j,i,i+step);
        }
    }

}

void Helper::drawBaseCilinderTriangle(float base, float radius, float angle1, float angle2)
{
    glBegin(GL_TRIANGLES);
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    glVertex3f( 0.0f, base, 0.0f);
    glColor3f(0.0f, angle1, angle2);     // Green
    glVertex3f(polar2CartX(radius,angle1), base, polar2CartZ(radius, angle1));
    glColor3f(angle1, angle2, angle1);     // Green
    glVertex3f(polar2CartX(radius,angle2), base, polar2CartZ(radius, angle2));
    glEnd();

}

void Helper::drawSideCilinderTriangle(float bottomHeight,float topHeight, float bottomRadius,float topRadius, float angle1, float angle2)
{
    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, angle1, angle2);     // Green
    glVertex3f(polar2CartX(bottomRadius, angle1), bottomHeight, polar2CartZ(bottomRadius, angle1));
    glVertex3f(polar2CartX(bottomRadius, angle2), bottomHeight, polar2CartZ(bottomRadius, angle2));
    glVertex3f(polar2CartX(topRadius, angle2), topHeight, polar2CartZ(topRadius, angle2));

    glVertex3f(polar2CartX(bottomRadius, angle1), bottomHeight, polar2CartZ(bottomRadius, angle1));
    glVertex3f(polar2CartX(topRadius, angle2), topHeight, polar2CartZ(topRadius, angle2));
    glVertex3f(polar2CartX(topRadius, angle1), topHeight, polar2CartZ(topRadius, angle1));

    glEnd();
}


