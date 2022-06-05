#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include "ParseTeapotPatch.h"
#include <math.h>
#include <stdio.h>
#include <IL/il.h>
#include "Parser.h"
#include "Axes.h"
#include "HandleRenderTransform.h"
#include "Timer.h"
#include "TransformationsDataStruct/Transformations.h"
#include "LightComponent.h"

CameraStatus* cam;
Transformations* t;
vector<LightComponent*> lights;

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
    cam->RenderCameraPerspective(ratio);

    // return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

	// et the viewport to be the entire window
	glViewport(0, 0, w, h);
}
void InitLighting()
{
    glEnable(GL_LIGHTING);
    for (int i = 0; i < lights.size(); ++i) {
        lights[i]->SetLight();
    }

}
void SetUpLighting()
{
    for (int i = 0; i < lights.size(); ++i) {
        lights[i]->RenderLight();
    }
}


void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.f,0.f,0.f,0.f);
    // set camera
	glLoadIdentity();

    SetUpLighting();

    cam->RenderCameraScene();

    // put drawing instructions here
    Axes::DrawAxes();

    //Totalmente inutil :)
    //BezierCurves::DrawBezier();
    ParseTeapotPatch::Render();

    //Render the objects with the respectives transformations
    HandleRenderTransform::Render(t);

//    std::cout <<Timer::GetTime()<<"\n";
    Timer::AdjustTimeBetweenFrame();

    // End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
    // put code to process regular keys in here
    switch (c) {
        case 'a':{
            cam->MoveCameraLeft();
            break;
        }
        case 'd' :{
            cam->MoveCameraRight();
            break;
        }
            case 's':{
            cam->MoveCameraBackwards();
            break;
        }
            case 'w': {
                cam->MoveCameraForward();
                break;
            }
            case 'i':{
                cam->CameraLookUp();
                break;
        }
        case 'k':{
            cam->CameraLookDown();
            break;
        }
        case 'l':{
            cam->CameraLookRight();
            break;
        }
        case 'j':{
            cam->CameraLookLeft();
            break;
        }
    }

    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {
    glutPostRedisplay();
}

std::vector<const char*> allNameModels;

int main(int argc, char** argv)
{


	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(800, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI");

    //Renders only lines and doesnt use the material
//        glPolygonMode(GL_FRONT,GL_LINE);

    // put callback registry here
	glutReshapeFunc(changeSize);

    //Por questões de otimizações isto pode ser deixado comentado
    glutIdleFunc(renderScene);
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);





#ifndef __APPLE__
    glewInit();
#endif

    //Load the image Loader
    ilInit();
    //Generate at least 40 buffers to store objects
    glGenBuffers(MAX_BUFFERS,Transformations::buffers);
    glGenBuffers(MAX_BUFFERS,Transformations::buffersNormals);
    glGenBuffers(MAX_BUFFERS,Transformations::buffersTexture);

    //Initialize the global variable
    t = new Transformations();

    Parser::XML_Parse(&cam,&lights,&t);


    t->StoreNameModels_LoadVBO();

    //Initialize the lighting system
    InitLighting();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);


    // enter GLUT�s main cycle
	glutMainLoop();
	return 1;
}