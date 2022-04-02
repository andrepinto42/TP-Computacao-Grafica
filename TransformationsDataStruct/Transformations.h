//
// Created by pinto on 07/03/22.
//

#ifndef PARSER_CPP_TRANSFORMATIONS_H
#define PARSER_CPP_TRANSFORMATIONS_H
#include <vector>
#include "../HandlerModel.h"
#include "Transform.h"
#include "StoreModels.h"

using namespace std;

class Transformations {
public:
    //Very important to store a pointer because its going to be need to be derefenced
    vector<Transformations*> allChildrenTransformation;

    vector<const char *> allParentModelsName;
    vector<HandlerModel> allModels;
    vector<T_Scale> parentScales;
    vector<T_Rotate> parentRotates;
    vector<T_Translate> parentTranslates;

    Transformations();

    void DoSomething(){
        for (int i = 0; i < parentScales.size(); ++i) {
            printf("Scale : ");
            PrintInfo(parentScales[i].x,parentScales[i].y,parentScales[i].z);
        }

        for (int i = 0; i < parentTranslates.size(); ++i) {
            printf("Translate : ");
            PrintInfo(parentTranslates[i].x,parentTranslates[i].y,parentTranslates[i].z);
        }

        for (int i = 0; i < parentRotates.size(); ++i) {
            printf("Rotate : ");
            PrintInfo(parentRotates[i].angle,parentRotates[i].x,parentRotates[i].y,parentRotates[i].z);
        }

        for (int i = 0; i < allParentModelsName.size(); ++i) {

            //Read the name of the file and store it in allModelsClass
            StoreModels::Store(allParentModelsName[i], &(allModels) );
        }

        for (auto anotherT:allChildrenTransformation) {
            anotherT->DoSomething();
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
