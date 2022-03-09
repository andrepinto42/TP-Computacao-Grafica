#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

void DrawSquare(float d, float d1, float d2);

void DrawAxes();

#include <math.h>
#include <stdio.h>
#include <iostream>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include <math.h>
#include "Parser.h"

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


void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// set camera
	glLoadIdentity();
	gluLookAt(5.0f, 2.0f, 5.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f);

//    DrawAxes();

    float length = 3.0f;
    float divisions = 3.0f;

	// put drawing instructions here
    float offset = (sqrt(length * length *2.0f) / -2.0f);
    float tam = (offset* (-2.0f))/ divisions;

    for (float i = offset+tam; i < -offset+tam; i+=tam) {
        for (float j = offset+tam; j < -offset+tam; j+=tam) {
            DrawSquare(i, j, tam);
        }
    }

    // End of frame
	glutSwapBuffers();
}

void DrawAxes() {
    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis in White
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
}

void DrawSquare(float x, float z, float length) {
    glBegin(GL_TRIANGLES);
    glColor3f(0.f,0.f,1.f);
    glVertex3d(x,0.0f,z);
    glVertex3d(x,0.0f,z-length);
    glVertex3d(x-length,0.0f,z-length);

    glVertex3d(x,0.0f,z);
    glVertex3d(x-length,0.0f,z-length);
    glVertex3d(x-length,0.0f,z);
    glEnd();
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