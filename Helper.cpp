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
#include <iostream>


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
    int stack = 4;
    float stepHeight = radius/stack;
    float step = 360.f / (float) slice;

    float partition = (radius*2) / (float)stack;
    float previousRadius=radius;
    //Draws the upper part of the sphere
    for (int j = 0; j < 2; j+=1) {

        float nextRadius = sqrt(pow(radius,2) - pow((j+1)*partition,2));
        std::cout << nextRadius<< " and " << previousRadius <<"\n";

        for (float i = 0; i < 360.f; i+=step) {

            drawSideCilinderTriangle( j,j+1,previousRadius,nextRadius,i,i+step);
        }
        previousRadius = nextRadius;

    }
    previousRadius = radius;

    //Draw the lower Bound of the sphere
    for (int j = 0; j > -2; j-=1) {

        float nextRadius = sqrt(pow(radius,2) - pow((j-1)*partition,2));
        std::cout << "Upper "<<nextRadius<< " and Down"  << previousRadius <<"\n";

        for (float i = 0; i < 360.f; i+=step) {
            drawSideCilinderTriangle( j-1,j,nextRadius,previousRadius,i,i+step);
        }
        previousRadius = nextRadius;
    }
    std::cout << "END\n";
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


