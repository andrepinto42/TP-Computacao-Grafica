//
// Created by pinto on 07/03/22.
//
#include <GL/glew.h>
#include "Transformations.h"
#include <iostream>
#include "Transformations.h"
#include "../tinyxml/tinyxml.h"


Transformations::Transformations() {
}


void Transformations::Store(int iMat)
{
    //Initialize
    const char* nameFile = this->allParentModelsName[iMat];
    std::vector<HandlerModel> *allModelsClass = &((this)->allModels);

    TiXmlDocument doc;
    if (!doc.LoadFile(nameFile))
    {
        std::cout << "Error loading file " << nameFile<<"\n";
        doc.Clear();
        return;
    }

    TiXmlElement *pRoot, *pConfig,*pVertex;
    pRoot = doc.FirstChildElement( "Model" );
    if ( pRoot )
    {
        pConfig= pRoot->FirstChildElement("Configuration" ); //now params

        int vertexCount =atoi(pConfig->Attribute("VertexCount"));

        auto normalCount_A = pConfig->Attribute("NormalCount");

        int normalCount = (normalCount_A) ? atoi(normalCount_A) : 0;

        std::vector<float> novosPontos;
        //Start iterating over all the vertex stored in the model.3d file
        pVertex = pConfig->NextSiblingElement();
        for (int j = 0; j < vertexCount; ++j) {
            float xVertex=  atof(pVertex->Attribute("x"));
            float yVertex=  atof(pVertex->Attribute("y"));
            float zVertex=  atof(pVertex->Attribute("z"));

            novosPontos.push_back(xVertex);
            novosPontos.push_back(yVertex);
            novosPontos.push_back(zVertex);

            pVertex = pVertex->NextSiblingElement();
        }

        vector<float> novosNormals;
        //Start iterating over all the normals if they exist stored in the model.3d file
        for (int j = 0; j < normalCount; ++j) {
            float xNormal=  atof(pVertex->Attribute("x"));
            float yNormal=  atof(pVertex->Attribute("y"));
            float zNormal=  atof(pVertex->Attribute("z"));

            novosNormals.push_back(xNormal);
            novosNormals.push_back(yNormal);
            novosNormals.push_back(zNormal);

            pVertex = pVertex->NextSiblingElement();
        }
        HandlerModel model;

        model.numberOfTriangles = novosPontos.size()/3;

        //Get the buffer that is assigned to this specific model and store it
        model.buffer = Transformations::buffers[Transformations::globalCurrentPosition];
        Transformations::globalCurrentPosition +=1;

        glBindBuffer(GL_ARRAY_BUFFER, model.buffer);
        glBufferData(GL_ARRAY_BUFFER,
                     novosPontos.size() * sizeof(float),
                     &(novosPontos[0]),
                     GL_STATIC_DRAW);

        //Check if has information about normals
        if (normalCount>0)
        {
            //Make sure that now it can be drawed the normals
            model.hasNormals = true;

            //Save the global variable in the dataStruct, so it can be drawn later by HandlerModel
            model.bufferNormal = buffersNormals[globalCurrentPositionNormals];
            globalCurrentPositionNormals +=1;

            //Store the normals
            glBindBuffer(GL_ARRAY_BUFFER,model.bufferNormal);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(float)  * novosNormals.size(),
                         &(novosNormals[0]),
                         GL_STATIC_DRAW);
        }

        //Setup the materials
        for (int i = 0; i < positionOfMaterial.size(); ++i) {
            if (iMat == positionOfMaterial[i])
            {
                model.materials =  arrayTypeOfMaterials[iMat];
                break;
            }
        }

        for (int i = 0; i < positionOfTexture.size(); ++i) {
            if (iMat == positionOfTexture[i])
            {
                TextureStruct* modelTextureStruct = arraytextureStruct[i];
                std::cout<< modelTextureStruct->texture_ID<< "<- ID | BUFFER ->"<<modelTextureStruct->bufferTexture_ID<<"\n";



                //TODO get the right index for the buffers texture
                vector<float> texCoord;

                float bottom = 0;
                float top = 1.f;
                for (int j = 0.f; j < model.numberOfTriangles / 2; j++ ) {
                    //Draw triangle first
                    texCoord.push_back(bottom);
                    texCoord.push_back(bottom);

                    texCoord.push_back(top);
                    texCoord.push_back(bottom);

                    texCoord.push_back(top);
                    texCoord.push_back(top);

                    //Second triangle
                    texCoord.push_back(bottom);
                    texCoord.push_back(bottom);

                    texCoord.push_back(top);
                    texCoord.push_back(top);


                    texCoord.push_back(bottom);
                    texCoord.push_back(top);
                }

                glBindBuffer(GL_ARRAY_BUFFER, modelTextureStruct->bufferTexture_ID);
                glBufferData(GL_ARRAY_BUFFER, texCoord.size() * sizeof(float), &(texCoord[0]), GL_STATIC_DRAW);
                //Save it so it can be later used for drawing
                model.textureStruct = modelTextureStruct;

                texCoord.clear();
            }
        }

        novosPontos.clear();
        novosNormals.clear();

        allModelsClass->push_back(model);
    }
    doc.Clear();
}



