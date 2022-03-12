//
// Created by pinto on 12/03/22.
//

#include "HandlerModel.h"

void HandlerModel::Draw() {
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < allVertices.size(); ++i) {
        glVertex3d(allVertices[i].x,allVertices[i].y,allVertices[i].z);
    }

    glEnd();
}
