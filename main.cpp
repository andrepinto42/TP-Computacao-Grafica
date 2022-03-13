#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include "Parser.h"
#include "Axes.h"
#include "HandleDrawSphere.h"
#include "Generator/Vector3.h"
#include "HandlerModel.h"
#include "StoreModels.h"
#include "HandlerDrawSquare.h"


using namespace std;

float beta = 0;
float alpha = 0;
float r = 10;
vector<HandlerModel> allModelsClass;

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

    gluLookAt(r*cosf(beta)*sinf(alpha), r*sinf(beta), r*cosf(beta)*cosf(alpha),
              0.0,0.0,0.0,
              0.0,1.0,0.0);

    // put drawing instructions here
    Axes::DrawAxes();

    for (int i = 0; i < allModelsClass.size(); ++i) {
        allModelsClass[i].Draw();
    }


    HandlerDrawSquare::DrawPlanesX(1.f,1.f);
    HandlerDrawSquare::DrawPlanesY(1.f,1.f);
    HandlerDrawSquare::DrawPlanesZ(1.f,1.f);
    //HandleDrawSphere::DrawSphere(5.0f, 10.0f, 20.0f);

    //DrawCone::DrawConeFunc(1,2,30,3);

    // End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
    // put code to process regular keys in here
    switch (c) {
        case 'a':
            alpha-=0.1;
            break;
        case 'd' :
            alpha+=0.1;
            break;
        case 's':
            if((beta-0.1) >= -M_PI/2) {
                beta -= 0.1;
            }
            break;
        case 'w':
            if((beta+0.1) <= M_PI/2) {
                beta += 0.1;
            }
            break;
    }
    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_DOWN:
            if(r-1>0) {
                r--;
            }
            break;
        case GLUT_KEY_UP :
            r++;
            break;
    }
    glutPostRedisplay();
}

void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}

std::vector<const char*> allNameModels;


int main(int argc, char** argv)
{
    allNameModels = Parser::XML_Parse();

    vector<const char*> duplicadoAllNameModels;
    for (int i = 0; i <allNameModels.size() ; ++i) {

        duplicadoAllNameModels.push_back(strdup(allNameModels[i]));
    }

    //ERRO DEMASIADO ESTUPIDO
    //StoreModels::Store(allNameModels[0],&allModelsClass);
    for (int i = 0; i < allNameModels.size(); ++i) {
        StoreModels::Store(duplicadoAllNameModels[i], &allModelsClass);
    }

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

    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// enter GLUT�s main cycle
	glutMainLoop();
	return 1;
}