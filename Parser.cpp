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


void Parser::XML_Parse(CameraStatus **cam, Transformations **rootTransformations) {
    char nameFile[] = "../solarsystem_withMeteorite.xml";

    TiXmlDocument doc;
    if (!doc.LoadFile(nameFile)) {
        std::cout << "Error loading file " << nameFile;
    }

    TiXmlElement *pRoot, *pCamera, *pParms;
    pRoot = doc.FirstChildElement("world");

    if (!pRoot)
        return;

    pCamera = pRoot->FirstChildElement("camera");
    //Assign the value so it can be stored in the main class
    if (pCamera)
        *cam = getCameraStatus(pCamera, pParms);

    //Second Phase
    auto pAnotherGroup = pRoot->FirstChildElement("group");
    while (pAnotherGroup) {
        InsertNextChildrenTransformation(rootTransformations, pAnotherGroup);
        pAnotherGroup = pAnotherGroup->NextSiblingElement("group");
    }
}

CameraStatus *Parser::getCameraStatus(TiXmlElement *pBody, TiXmlElement *pParms) {
    pParms = pBody->FirstChildElement("position"); //now params

    float posX = atof(pParms->Attribute("x"));
    float posY = atof(pParms->Attribute("y"));
    float posZ = atof(pParms->Attribute("z"));

    pParms = pParms->NextSiblingElement();
    float lookX = atof(pParms->Attribute("x"));
    float lookY = atof(pParms->Attribute("y"));
    float lookZ = atof(pParms->Attribute("z"));


    pParms = pParms->NextSiblingElement();
    float upX = atof(pParms->Attribute("x"));
    float upY = atof(pParms->Attribute("y"));
    float upZ = atof(pParms->Attribute("z"));


    pParms = pParms->NextSiblingElement();
    float fov = atof(pParms->Attribute("fov"));
    float near = atof(pParms->Attribute("near"));
    float far = atof(pParms->Attribute("far"));

    CameraStatus *cam = new CameraStatus(
            posX, posY, posZ,
            lookX, lookY, lookZ,
            upX, upY, upZ,
            fov, near, far);
    return cam;
}

void Parser::TransformGroupElement(TiXmlElement *pGroup, Transformations **root) {

    auto pTransform = pGroup->FirstChildElement("transform");
    if (pTransform)
        InsertTransformations(root, pTransform);

    auto pModels = pGroup->FirstChildElement("models");
    if (pModels)
        InsertModelsName(root, pModels);

    auto pAnotherGroup = pGroup->FirstChildElement("group");
    while (pAnotherGroup) {
        InsertNextChildrenTransformation(root, pAnotherGroup);
        pAnotherGroup = pAnotherGroup->NextSiblingElement("group");
    }

}

void Parser::InsertModelsName(Transformations *const *root, TiXmlElement *pModels) {
    auto pModel = pModels->FirstChildElement();
    while (pModel) {
        // E necessario duplicar a string por alguma razao estranha
        (*root)->allParentModelsName.push_back(strdup(pModel->Attribute("file")));
        pModel = pModel->NextSiblingElement("model");
    }
    cout << "Inserted these models ->";
    for (auto string: (*root)->allParentModelsName) {
        cout << string << "\n";
    }
}


void Parser::InsertNextChildrenTransformation(Transformations *const *root, TiXmlElement *pAnotherGroup) {
    //Create a new Tranformation object and store it in the dataStruct of the parent
    Transformations *anotherTransformation = new Transformations();
    (*root)->allChildrenTransformation.push_back(anotherTransformation);

    TransformGroupElement(pAnotherGroup, &anotherTransformation);
}


void Parser::InsertTransformations(Transformations *const *root, TiXmlElement *pTransform) {
    float x, y, z, angle;
    TiXmlElement* iterator = pTransform->FirstChildElement();

    while(iterator)
    {
        auto name =iterator->Value();

        //Check if translate can describe catmull-rom Curves
        if (strcmp(name,"translate") == 0)
        {
            auto time=iterator->Attribute("time");
            auto align =iterator->Attribute("align");
            //Check if its the special behaviour of the catmull-rom
            if (time!= nullptr && align != nullptr)
            {
                CreateCatmull(root, x, y, z, iterator, time, align);

                //Skip to next iteration
                iterator = iterator->NextSiblingElement();
                continue;
            }
        }

        x = atof(iterator->Attribute("x"));
        y = atof(iterator->Attribute("y"));
        z = atof(iterator->Attribute("z"));
        if (strcmp(name,"translate") == 0)
        {
            auto t = new T_Translate(x, y, z);
            (*root)->parentAllTransforms.push_back(t);
        }
        else if (strcmp(name,"scale") == 0)
        {
            auto t = new T_Scale (x, y, z);
            (*root)->parentAllTransforms.push_back(t);
        }
        else if (strcmp(name,"rotate") == 0)
        {
            Transform* t;
            const char* timeRotate;
            //Check if exists the special atribute time
            if ( (timeRotate = iterator->Attribute("time")) != nullptr)
            {
                float timeSeconds = atof(timeRotate);
                t = new T_Rotate_Time(timeSeconds,x,y,z);
            }
            else
            {
                angle = atof(iterator->Attribute("angle"));
                t = new T_Rotate (angle,x, y, z);
            }

            (*root)->parentAllTransforms.push_back(t);
        }
        else
        {
            std::cout <<"Error parsing XML in the transform method";
        }

        iterator = iterator->NextSiblingElement();
    }
}

void Parser::CreateCatmull(Transformations *const *root,
                      float x, float y, float z,
                      TiXmlElement *iterator, const char *time,const char *align)
{
    vector<float> all_points;
    auto points = iterator->FirstChildElement();
    while(points)
    {
        x = atof(points->Attribute("x"));
        y = atof(points->Attribute("y"));
        z = atof(points->Attribute("z"));
        all_points.push_back(x);
        all_points.push_back(y);
        all_points.push_back(z);

        points = points->NextSiblingElement();
    }

    bool align_Value = strcmp(align, "True") == 0;
    int numberOfPoints = all_points.size()/3;

    auto arrayPoints = static_cast<float **>(malloc(sizeof(float *) * numberOfPoints ));
    for (int i = 0; i < numberOfPoints; ++i) {
        arrayPoints[i] = static_cast<float *>(malloc(sizeof(float) * 3));
        //Alocate space for the 3 float coordenates
        for (int j = 0; j < 3; ++j) {
            arrayPoints[i][j] = all_points[i*3 + j];
        }
    }

    //Create a catmull struct to store the necessary data
    auto t = new T_Catmull_Rom(arrayPoints,  numberOfPoints, align_Value, atof(time));
    (*root)->parentAllTransforms.push_back(t);

    all_points.clear();
}
