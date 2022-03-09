//
// Created by pinto on 04/03/22.
//

#include "Parser.h"
#include <stdio.h>
#include <iostream>
#include <vector>

#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "CameraStatus.h"
#include "Transformations.h"
using namespace std;


void Parser::XML_Parse()
{
    char nameFile[] = "../xml_syntax.xml";
    TiXmlDocument doc;
    if (!doc.LoadFile(nameFile))
    {
        std::cout << "Error loading file " << nameFile;
    }

    TiXmlElement *pRoot, *pCamera,*pGroup,*pModels,*pModel, *pParms;
    pRoot = doc.FirstChildElement( "world" );
    if ( pRoot )
    {
        pCamera= pRoot->FirstChildElement( "camera" );
        if (pCamera) {
            CameraStatus *cam = getCameraStatus(pCamera, pParms);
        }
        pGroup = pRoot->FirstChildElement("group");
        if (pGroup)
        {
            pModels = pGroup->FirstChildElement("models");
            if (pModels)
            {
                pModel = pModels->FirstChildElement();
                vector<const char*> names;
                while(pModel)
                {
                    names.push_back(pModel->Attribute("file"));
                    pModel = pModel->NextSiblingElement();
                }
                Transformations* t = new Transformations(&names);

                for(const char* x : t->allNamesModels)
                    std::cout << x<< std::endl;

            }
        }

    }
}

CameraStatus *Parser::getCameraStatus(TiXmlElement *pBody, TiXmlElement *pParms) {
    pParms= pBody->FirstChildElement("position" ); //now params

    float posX =atof(pParms->Attribute("x"));
    float posY =atof(pParms->Attribute("y"));
    float posZ =atof(pParms->Attribute("z"));

    pParms =pParms->NextSiblingElement();
    float lookX =atof(pParms->Attribute("x"));
    float lookY =atof(pParms->Attribute("y"));
    float lookZ =atof(pParms->Attribute("z"));


    pParms =pParms->NextSiblingElement();
    float upX =atof(pParms->Attribute("x"));
    float upY =atof(pParms->Attribute("y"));
    float upZ =atof(pParms->Attribute("z"));


    pParms =pParms->NextSiblingElement();
    float fov =atof(pParms->Attribute("fov"));
    float near =atof(pParms->Attribute("near"));
    float far =atof(pParms->Attribute("far"));

    CameraStatus* cam = new CameraStatus(
            posX, posY, posZ,
            lookX, lookY, lookZ,
            upX, upY,upZ,
            fov, near, far);
    return cam;
}
