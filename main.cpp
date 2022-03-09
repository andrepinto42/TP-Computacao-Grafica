#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

void DrawSquareAxisY(float x, float y, float z, float length);
void DrawSquareAxisX(float x, float y, float z, float length);

void DrawPlanesY(float length, float divisions);

void DrawPlanesX(float length, float divisions);

#include <math.h>
#include <stdio.h>
#include <iostream>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include <math.h>
#include "Parser.h"
#include "Axes.h"

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
	gluLookAt(10.0f, 10.0f, 10.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 3.0f, 0.0f);

    // put drawing instructions here
    Axes::DrawAxes();
    DrawPlanesY(5.0f,5.0f);
    DrawPlanesX(5.0f,5.0f);

    // End of frame
	glutSwapBuffers();
}

void DrawPlanesX(float length, float divisions) {
    float startZX = (sqrt(length * length *2.0f) / 2.0f);
    float endZX = startZX - length ;
    float tam = length / divisions;

    std::cout << "Start at z ="<<startZX-tam<<" \n";


    for (float i = 0.0f; i < length; i+=tam) {
        for (float j = startZX-tam; j > endZX-tam; j-=tam) {
            std::cout << i << " and " << j << "\n";
            DrawSquareAxisX(startZX-tam, i, j,tam);
        }
    }
    std::cout << "End\n";

}

void DrawPlanesY(float length, float divisions) {
    float tam = length / divisions;
    float startZX = (sqrt(length * length *2.0f) / 2.0f);
    float endZX = startZX - length ;


    for (float i = startZX-tam; i > endZX-tam; i-=tam) {
        for (float j = startZX-tam; j > endZX-tam; j-=tam) {
            DrawSquareAxisY(i, 0.0f, j,tam);
        }
    }

    for (float i = startZX-tam; i > endZX-tam; i-=tam) {
        for (float j = startZX-tam; j > endZX-tam; j-=tam) {
            DrawSquareAxisY(i, length, j,tam);
        }
    }
}

void DrawSquareAxisY(float x, float y, float z, float length) {
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

void DrawSquareAxisX(float x, float y, float z, float length) {

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