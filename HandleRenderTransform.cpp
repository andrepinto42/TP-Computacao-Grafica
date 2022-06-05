//
// Created by pinto on 02/04/22.
//
#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "TransformationsDataStruct/Transformations.h"
#include "HandleRenderTransform.h"


void HandleRenderTransform::Render(Transformations *transformationStruct) {
    glPushMatrix();

    for(auto transformacao : transformationStruct->parentAllTransforms)
    {
        transformacao->Apply();
    }

    //Chamar instruçoes que desenham todos os vertices
    for (int i = 0; i < transformationStruct->allModels.size(); ++i) {
        transformationStruct->allModels[i].Draw();
    }
    //Invocar de forma recursiva para os filhos desenharem as suas Transformações
    for (int i = 0; i < transformationStruct->allChildrenTransformation.size(); ++i) {
        Render(transformationStruct->allChildrenTransformation[i]);
    }
    //Importante dar pop da matrix desta forma ao fim da chamada recursiva
    //As transformacoes de um filho não afetam os seus irmaos devido ao Pop
    glPopMatrix();
}
