#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <IL/il.h>
#include "Parsing/Parser.h"
#include "Render/Axes.h"
#include "Render/HandleRenderTransform.h"
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

    glPushMatrix();
    glTranslatef(0.f,-2.f,-5.f);
    glRotatef(-90.f,0.f,1.f,0.f);
    glRotatef(-25.f,0.f,0.f,1.f);
    glutSolidTeapot(0.5f);
    glPopMatrix();


    cam->RenderCameraScene();

    //Render lighting after the camera so it doesnt follow everywhere
    SetUpLighting();

    // put drawing instructions here
    Axes::DrawAxes();

    //Render the objects with the respectives transformations
    HandleRenderTransform::Render(t);

    Timer::AdjustTimeBetweenFrame();

    // End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
    // put code to process regular keys in here
    if (c == 'a'){
        cam->MoveCameraLeft();
    }
    if (c == 'd')
    {
        cam->MoveCameraRight();
    }
    if (c == 's')
    {
        cam->MoveCameraBackwards();
    }
    if (c == 'w')
        {
            cam->MoveCameraForward();
        }
    if (c == 'i')
        {
            cam->RotateUpNew();
    }
    if (c == 'k')
    {
        cam->RotateDownNew();
    }
    if (c == 'l')
    {
        cam->RotateRightNew();
    }
    if (c == 'j')
    {
        cam->RotateLeftNew();
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

    //Por quest??es de otimiza????es isto pode ser deixado comentado
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


    // enter GLUT???s main cycle
	glutMainLoop();
	return 1;
}