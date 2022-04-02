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
#include "TransformationsDataStruct/Transformations.h"

using namespace std;


void Parser::XML_Parse(CameraStatus **cam,Transformations** rootTransformations)
{
    char nameFile[] = "../xml_04_Groups.xml";

    TiXmlDocument doc;
    if (!doc.LoadFile(nameFile))
    {
        std::cout << "Error loading file " << nameFile;
    }

    TiXmlElement *pRoot, *pCamera,*pGroup,*pModels,*pModel, *pParms;
    pRoot = doc.FirstChildElement( "world" );

    if ( !pRoot )
        return;

    pCamera= pRoot->FirstChildElement( "camera" );
    //Assign the value so it can be stored in the main class
    if (pCamera)
        *cam = getCameraStatus(pCamera, pParms);

    //Second Phase
    pGroup = pRoot->FirstChildElement("group");
    if (pGroup)
        TransformGroupElement(pGroup,rootTransformations);
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

void Parser::TransformGroupElement(TiXmlElement *pGroup,Transformations** root) {

    auto pTransform = pGroup->FirstChildElement("transform");
    if (pTransform)
        InsertTransformations(root, pTransform);

    auto pModels = pGroup->FirstChildElement("models");
    if (pModels)
        InsertModelsName(root, pModels);

    auto pAnotherGroup = pGroup->FirstChildElement("group");
    while (pAnotherGroup){
        InsertNextChildrenTransformation(root, pAnotherGroup);
        pAnotherGroup = pAnotherGroup->NextSiblingElement("group");
    }

}

void Parser::InsertModelsName(Transformations *const *root, TiXmlElement *pModels) {
    auto pModel = pModels->FirstChildElement();
    while(pModel)
    {
        // E necessario duplicar a string por alguma razao estranha
        (*root)->allParentModelsName.push_back(strdup( pModel->Attribute("file")));
        pModel = pModel->NextSiblingElement("model");
    }
    cout << "Inserted these models ->";
    for (auto string:(*root)->allParentModelsName) {
        cout << string<<"\n";
    }
}


void Parser::InsertNextChildrenTransformation(Transformations *const *root, TiXmlElement *pAnotherGroup) {
    //Create a new Tranformation object and store it in the dataStruct of the parent
    Transformations* anotherTransformation = new Transformations();
    (*root)->allChildrenTransformation.push_back(anotherTransformation);

    TransformGroupElement(pAnotherGroup,&anotherTransformation);
}



void Parser::InsertTransformations(Transformations *const *root, TiXmlElement *pTransform) {
    float x,y,z,angle;

    auto pTranslate = pTransform->FirstChildElement("translate");
    while (pTranslate){
        x = atoi( pTranslate->Attribute("x"));
        y = atoi( pTranslate->Attribute("y"));
        z = atoi( pTranslate->Attribute("z"));
        T_Translate t(x,y,z);
        (*root)->parentTranslates.push_back(t);
        pTranslate = pTranslate->NextSiblingElement("translate");
    }

    auto pScale = pTransform->FirstChildElement("scale");
    while (pScale){
        x = atoi( pScale->Attribute("x"));
        y = atoi( pScale->Attribute("y"));
        z = atoi( pScale->Attribute("z"));
        T_Scale t(x,y,z);
        (*root)->parentScales.push_back(t);
        pScale = pScale->NextSiblingElement("scale");
    }

    auto pRotate = pTransform->FirstChildElement("rotate");
    while (pRotate){
        angle = atoi( pRotate->Attribute("angle"));
        x = atoi( pRotate->Attribute("x"));
        y = atoi( pRotate->Attribute("y"));
        z = atoi( pRotate->Attribute("z"));
        T_Rotate t(angle,x,y,z);
        (*root)->parentRotates.push_back(t);
        pRotate = pRotate->NextSiblingElement("rotate");
    }

}
