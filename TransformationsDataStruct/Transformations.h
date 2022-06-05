//
// Created by pinto on 07/03/22.
//

#ifndef PARSER_CPP_TRANSFORMATIONS_H
#define PARSER_CPP_TRANSFORMATIONS_H
#include <GL/glew.h>

#include <vector>
#include "../HandlerModel.h"
#include "Transform.h"
using namespace std;

static const int MAX_BUFFERS = 40;

class Transformations {

public:
    inline static GLuint buffers[MAX_BUFFERS] ;
    inline static GLuint buffersNormals[MAX_BUFFERS] ;
    inline static GLuint buffersTexture[MAX_BUFFERS] ;

    inline static int globalCurrentPosition = 0;
    inline static int globalCurrentPositionNormals = 0;
    inline static int globalCurrentPositionTexture = 0;

    //Very important to store a pointer because its going to be need to be derefenced
    vector<Transformations*> allChildrenTransformation;

    vector<const char *> allParentModelsName;

    //This variables exists just because there was not found an apropriatte datastruct to store
    vector<TypeOfMaterial*> arrayTypeOfMaterials;
    vector<int> positionOfMaterial;
    vector<TextureStruct*> arraytextureStruct;
    vector<int> positionOfTexture;

    vector<HandlerModel> allModels;

    //Avoid object slicing by storing pointers and not storing fixed sized structs
    vector<Transform*> parentAllTransforms;

    void StoreNameModels_LoadVBO(){

        for (int i = 0; i < allParentModelsName.size(); ++i) {

            //Read the name of the file and store it in allModelsClass
            //TODO add the texture array here so the model can be drawn properly
            Store(i);
        }

        for (auto anotherT:allChildrenTransformation) {
            anotherT->StoreNameModels_LoadVBO();
        }
    }
    void Store(int iMat);

    Transformations();

private:
    static void PrintInfo(float x,float y,float z){
        printf("x =%f,y =%f,z =%f\n",x,y,z);
    }

    static void PrintInfo(float angle,float x,float y,float z){
        printf("angle =%f,x =%f,y =%f,z =%f\n",angle,x,y,z);
    }

};



#endif //PARSER_CPP_TRANSFORMATIONS_H
