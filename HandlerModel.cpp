//
// Created by pinto on 12/03/22.
//
#include <GL/glew.h>
#include "HandlerModel.h"
#include "TransformationsDataStruct/Transformations.h"

void HandlerModel::Draw() {
    //Draw Materials
    if (materials)
    {
        if (textureStruct != nullptr)
        {
            //TODO
            glBindTexture(GL_TEXTURE_2D, textureStruct->texture_ID);
            glBindBuffer(GL_ARRAY_BUFFER, textureStruct->bufferTexture_ID);
            glTexCoordPointer(2, GL_FLOAT, 0, 0);

        }
        else
        {
            glMaterialfv(GL_FRONT,GL_AMBIENT, materials->arrAmbient);
            glMaterialfv(GL_FRONT,GL_DIFFUSE, materials->arrDifuse);
            glMaterialfv(GL_FRONT,GL_SPECULAR, materials->arrSpecular);
            glMaterialfv(GL_FRONT,GL_EMISSION, materials->arrEmissive);
            glMaterialf(GL_FRONT,GL_SHININESS,materials->shininess);
        }
    }

    if (hasNormals)
    {
        //Bind the buffer of the normals
        glBindBuffer(GL_ARRAY_BUFFER,bufferNormal);
        // normals always have 3 components so there is no need to specify
        glNormalPointer(GL_FLOAT,0,0);
    }

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, numberOfTriangles);

    if (textureStruct!= nullptr)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}
