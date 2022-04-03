//
// Created by pinto on 02/04/22.
//
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "TransformationsDataStruct/Transformations.h"
#include "HandleRenderTransform.h"


void HandleRenderTransform::Render(Transformations *transformationStruct) {
    glPushMatrix();

    //Aplicar translações antes de desenhar
    for (auto translate :transformationStruct->parentTranslates){
        glTranslatef(translate.x,translate.y,translate.z);
    }

    //Aplicar Rotaçoes antes de desenhar
    for (auto rotate :transformationStruct->parentRotates){
        glRotatef(rotate.angle,rotate.x,rotate.y,rotate.z);
    }

    //Aplicar escalas antes de desenhar
    for (auto scale :transformationStruct->parentScales){
        glScalef(scale.x,scale.y,scale.z);
    }

    //Chamar instruçoes que desenham todos os vertices
    for (int i = 0; i < transformationStruct->allModels.size(); ++i) {
        transformationStruct->allModels[i].Draw();
    }

    //Invocar de forma recursiva para os filhos desenharem as suas Transformações
    for (int i = 0; i < transformationStruct->allChildrenTransformation.size(); ++i) {
        Render(transformationStruct->allChildrenTransformation[i]);
    }
    //Importante dar pop da matrix dessa forma
    //Quando um as transformacoes de um filho não afetam os seus irmaos :)
    glPopMatrix();
}
