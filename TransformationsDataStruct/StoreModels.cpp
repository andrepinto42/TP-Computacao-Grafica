//
// Created by pinto on 12/03/22.
//

#include <iostream>
#include <GL/glew.h>
#include "Transformations.h"
#include "StoreModels.h"
#include "../HandlerModel.h"

#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinystr.h"


void StoreModels::Store(const char* nameFile,std::vector<HandlerModel> *allModelsClass)
{
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
        std::cout << "Number of vertices ->" <<vertexCount<<" from file"<< nameFile <<"\n";

        std::vector<float> novosPontos;

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

        HandlerModel model;

        //Store it and increment by 1
        model.currentPositionVBO = Transformations::globalCurrentPosition;
        Transformations::globalCurrentPosition +=1;

        model.numberOfTriangles = novosPontos.size()/3;

        model.buffer = Transformations::buffers[/*Increment */model.currentPositionVBO];

        glBindBuffer(GL_ARRAY_BUFFER, model.buffer);
        glBufferData(GL_ARRAY_BUFFER,
                     novosPontos.size() * sizeof(float),
                     &(novosPontos[0]),
                     GL_STATIC_DRAW);

        std::cout <<"Global position of "<< model.currentPositionVBO<<"\n";

        allModelsClass->push_back(model);
    }
    doc.Clear();
}