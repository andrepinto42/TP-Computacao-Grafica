//
// Created by pinto on 12/03/22.
//

#include <iostream>
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


        std::vector<Vector3> allVertices;

        pVertex = pConfig->NextSiblingElement();
        for (int j = 0; j < vertexCount; ++j) {
            float xVertex=  atof(pVertex->Attribute("x"));
            float yVertex=  atof(pVertex->Attribute("y"));
            float zVertex=  atof(pVertex->Attribute("z"));

            Vector3 v(xVertex,yVertex,zVertex);
            allVertices.push_back(v);

            pVertex = pVertex->NextSiblingElement();
        }

        HandlerModel model;
        model.allVertices = allVertices;

        allModelsClass->push_back(model);
    }
    doc.Clear();
}