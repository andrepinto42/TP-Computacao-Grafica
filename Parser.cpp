//
// Created by pinto on 04/03/22.
//

#include "Parser.h"
#include <stdio.h>
#include <iostream>

#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "CameraStatus.h"


void Parser::XML_Parse()
{
    char nameFile[] = "../xml_syntax.xml";
    TiXmlDocument doc;
    if (!doc.LoadFile(nameFile))
    {
        std::cout << "Error loading file " << nameFile;
    }

    TiXmlElement *pRoot, *pBody, *pParms;
    pRoot = doc.FirstChildElement( "world" );
    if ( pRoot )
    {
        pBody= pRoot->FirstChildElement( "camera" );
        if (pBody) {
            CameraStatus *cam = getCameraStatus(pBody, pParms);
            std::cout << cam->far;
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
