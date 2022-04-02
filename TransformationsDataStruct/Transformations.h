//
// Created by pinto on 07/03/22.
//

#ifndef PARSER_CPP_TRANSFORMATIONS_H
#define PARSER_CPP_TRANSFORMATIONS_H
#include <vector>
#include "../HandlerModel.h"
#include "Transform.h"

using namespace std;

class Transformations {
public:
    vector<Transformations> allChildrenTransformation;
    vector<HandlerModel> allParentModels;
    vector<T_Scale> parentScales;
    vector<T_Rotate> parentRotates;
    vector<T_Translate> parentTranslates;

    Transformations();

    void DoSomething(Transformations* t){
        for (int i = 0; i < t->parentScales.size(); ++i) {
            printf("Scale : ");
            PrintInfo(parentScales[i].x,parentScales[i].y,parentScales[i].z);
        }

        for (int i = 0; i < t->parentTranslates.size(); ++i) {
            printf("Translate : ");
            PrintInfo(parentTranslates[i].x,parentTranslates[i].y,parentTranslates[i].z);
        }

        for (int i = 0; i < t->parentRotates.size(); ++i) {
            printf("Rotate : ");
            PrintInfo(parentRotates[i].angle,parentRotates[i].x,parentRotates[i].y,parentRotates[i].z);
        }
        for (auto anotherT:t->allChildrenTransformation) {
            DoSomething(&anotherT);
        }
    }

private:
    void PrintInfo(float x,float y,float z){
        printf("x =%f,y =%f,z =%f\n",x,y,z);
    }

    void PrintInfo(float angle,float x,float y,float z){
        printf("angle =%f,x =%f,y =%f,z =%f\n",angle,x,y,z);
    }
};


#endif //PARSER_CPP_TRANSFORMATIONS_H
