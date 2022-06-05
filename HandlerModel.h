//
// Created by pinto on 12/03/22.
//

#ifndef MAIN_CPP_HANDLERMODEL_H
#define MAIN_CPP_HANDLERMODEL_H


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "Generator/Vector3.h"

class TypeOfMaterial{
public:
    //White
    float arrSpecular[4] = {1.f,1.f,1.f,1.f};
    //lightGrey
    float arrDifuse[4] = {0.75f,0.75f,0.75f,1.f};
    //DarkGrey
    float arrAmbient[4]={0.1f,0.1f,0.1f,1.f};
    float arrEmissive[4]{0,0,0,1};
    float shininess = 128;

};
struct TextureStruct{
    unsigned int texture_ID;
    unsigned int bufferTexture_ID;
};

class HandlerModel {
public:
    int numberOfTriangles;
    GLuint bufferNormal;
    GLuint buffer = 0;
    bool hasNormals = false;
    TextureStruct* textureStruct = nullptr;
    TypeOfMaterial* materials = new TypeOfMaterial;
    void Draw();
};


#endif //MAIN_CPP_HANDLERMODEL_H
