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
<<<<<<< HEAD
#include "TransformationsDataStruct/Transformations.h"

using namespace std;


vector<const char*> Parser::XML_Parse(CameraStatus **cam,Transformations** rootTransformations)
{
    char nameFile[] = "../xml_04_Groups.xml";

=======
#include "Transformations.h"
using namespace std;


vector<const char*> Parser::XML_Parse(CameraStatus **cam)
{
    char nameFile[] = "../xml_syntax.xml";
>>>>>>> 767bf6e6f9c1f1d0463993ca5259d5db06a64718
    TiXmlDocument doc;
    if (!doc.LoadFile(nameFile))
    {
        std::cout << "Error loading file " << nameFile;
    }

<<<<<<< HEAD
    vector<const char*> names;
    TiXmlElement *pRoot, *pCamera,*pGroup,*pModels,*pModel, *pParms;
    pRoot = doc.FirstChildElement( "world" );

    if ( !pRoot )
        return names;

    pCamera= pRoot->FirstChildElement( "camera" );
    //Assign the value so it can be stored in the main class
    if (pCamera)
        *cam = getCameraStatus(pCamera, pParms);

    //Second Phase
    pGroup = pRoot->FirstChildElement("group");
    if (pGroup)
    {

        TransformGroupElement(pGroup,rootTransformations);

        pModels = pGroup->FirstChildElement("models");
        if (pModels)
        {
            pModel = pModels->FirstChildElement();
            while(pModel)
            {
                names.push_back(pModel->Attribute("file"));
                pModel = pModel->NextSiblingElement();
            }

            for(const char* x : names)
                std::cout << x<< std::endl;

            return names;
        }
    }

=======
    TiXmlElement *pRoot, *pCamera,*pGroup,*pModels,*pModel, *pParms;
    pRoot = doc.FirstChildElement( "world" );
    if ( pRoot )
    {
        pCamera= pRoot->FirstChildElement( "camera" );
        if (pCamera) {
            //Assign the value so it can be stored in the main class
            *cam = getCameraStatus(pCamera, pParms);
            std::cout << (*cam)->posX<<"\n";
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

                for(const char* x : names)
                    std::cout << x<< std::endl;

                return names;
            }
        }

    }
>>>>>>> 767bf6e6f9c1f1d0463993ca5259d5db06a64718
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
<<<<<<< HEAD

void Parser::TransformGroupElement(TiXmlElement *pGroup,Transformations** root) {

    auto pTransform = pGroup->FirstChildElement("transform");
    if (pTransform)
    {
        float x,y,z,angle;

        auto pTranslate = pTransform->FirstChildElement("translate");
        if (pTranslate){
            x = atoi( pTranslate->Attribute("x"));
            y = atoi( pTranslate->Attribute("y"));
            z = atoi( pTranslate->Attribute("z"));
            T_Translate t(x,y,z);
            (*root)->parentTranslates.push_back(t);
        }

        auto pScale = pTransform->FirstChildElement("scale");
        if (pScale){
            x = atoi( pScale->Attribute("x"));
            y = atoi( pScale->Attribute("y"));
            z = atoi( pScale->Attribute("z"));
            T_Scale t(x,y,z);
            (*root)->parentScales.push_back(t);
        }

        auto pRotate = pTransform->FirstChildElement("rotate");
        if (pRotate){
            angle = atoi( pRotate->Attribute("angle"));
            x = atoi( pRotate->Attribute("x"));
            y = atoi( pRotate->Attribute("y"));
            z = atoi( pRotate->Attribute("z"));
            T_Rotate t(angle,x,y,z);
            (*root)->parentRotates.push_back(t);
        }

    }
    auto pModels = pGroup->FirstChildElement("group");
    if (pModels)
    {
        printf("There is another Group here!");
        //Create a new Tranformation object and store it in the dataStruct of the parent
        Transformations* anotherTransformation = new Transformations();
        (*root)->allChildrenTransformation.push_back(*anotherTransformation);


        TransformGroupElement(pModels,&anotherTransformation);
    }
}
=======
>>>>>>> 767bf6e6f9c1f1d0463993ca5259d5db06a64718
