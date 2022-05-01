//
// Created by pinto on 12/03/22.
//
#include <GL/glew.h>
#include "HandlerModel.h"
#include "TransformationsDataStruct/Transformations.h"

void HandlerModel::Draw() {
//    glBegin(GL_TRIANGLES);
//
//    for (int i = 0; i < allVertices.size(); ++i) {
//        glVertex3d(allVertices[i].x,allVertices[i].y,allVertices[i].z);
//    }

    glBindBuffer(GL_ARRAY_BUFFER, Transformations::buffers[currentPositionVBO]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, allVertices.size());
//    glEnd();
}
