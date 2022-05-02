//
// Created by pinto on 07/03/22.
//

#ifndef PARSER_CPP_TRANSFORMATIONS_H
#define PARSER_CPP_TRANSFORMATIONS_H
#include <vector>
#include "../HandlerModel.h"
#include "StoreModels.h"
#include "Transform.h"

using namespace std;

class Transformations {
public:
    inline static GLuint buffers[40] ;
    inline static int globalCurrentPosition = 0;

    //Very important to store a pointer because its going to be need to be derefenced
    vector<Transformations*> allChildrenTransformation;

    vector<const char *> allParentModelsName;
    vector<HandlerModel> allModels;

    //Avoid object slicing by storing pointers and not storing fixed sized structs
    vector<Transform*> parentAllTransforms;

    Transformations();

    void StoreNameModels_LoadVBO(){

        for (int i = 0; i < allParentModelsName.size(); ++i) {
            std::cout << "Goint to store this file -> " << allParentModelsName[i]<<"\n";
            //Read the name of the file and store it in allModelsClass
            StoreModels::Store(allParentModelsName[i], &(allModels) );
        }

        for (auto anotherT:allChildrenTransformation) {
            anotherT->StoreNameModels_LoadVBO();
        }
    }

private:
    static void PrintInfo(float x,float y,float z){
        printf("x =%f,y =%f,z =%f\n",x,y,z);
    }

    static void PrintInfo(float angle,float x,float y,float z){
        printf("angle =%f,x =%f,y =%f,z =%f\n",angle,x,y,z);
    }
};


#endif //PARSER_CPP_TRANSFORMATIONS_H
