#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <iostream>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include <math.h>
#include "Parser.h"
#include "Axes.h"
#include "HandlerDrawSquare.h"
#include "Helper.h"

void changeSize(int w, int h)
{
	// prevent a divide by zero, when window is too short
	// (you can not make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;

	// set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// set the perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

	// et the viewport to be the entire window
	glViewport(0, 0, w, h);
}

float moveY = 0.0f;
float moveRotate = 0.0f;
void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// set camera
	glLoadIdentity();
    float xPosition =  15.f*cos(moveRotate);
    float zPosition =  15.f*sin(moveRotate);
	gluLookAt( xPosition,15.f,zPosition,
		0.0f, 0.0f, 0.0f,
		0.0f, 3.0f, 0.0f);

    moveY += 0.01f;
    moveRotate +=0.01f;

    // put drawing instructions here
    Axes::DrawAxes();
//    HandlerDrawSquare::DrawPlanesY(5.0f,5.0f);
//    HandlerDrawSquare::DrawPlanesX(5.0f,5.0f);
//    HandlerDrawSquare::DrawPlanesZ(5.0f,5.0f);
    Helper::DrawSphere(5.0f, 20.0f,5.0f);


    // End of frame
	glutSwapBuffers();
}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}


int main(int argc, char** argv)
{
    Parser::XML_Parse();

	// put GLUT�s init here
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI");

    glPolygonMode(GL_FRONT,GL_LINE);

    // put callback registry here
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);

	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// enter GLUT�s main cycle
	glutMainLoop();
	return 1;
}