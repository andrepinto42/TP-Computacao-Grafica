//
// Created by pinto on 09/03/22.
//

#include "../Parsing/Parser.h"
#include "../tinyxml/tinystr.h"
#include "../tinyxml/tinyxml.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Axes.h"


void Axes::DrawAxes(){
    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-500.0f, 0.0f, 0.0f);
    glVertex3f( 500.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -500.0f, 0.0f);
    glVertex3f(0.0f, 500.0f, 0.0f);
    // Z Axis in White
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -500.0f);
    glVertex3f(0.0f, 0.0f, 500.0f);
    glEnd();
}